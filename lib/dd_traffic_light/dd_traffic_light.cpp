#include "dd_traffic_light.h"

static dd_traffic_light_t s_defaultTrafficLight;

static const dd_tl_direction_config_t *selectDirectionConfig(const dd_traffic_light_t *tl, dd_tl_direction_t direction)
{
    return (direction == DD_TL_DIR_NS) ? &tl->config.ns : &tl->config.ew;
}

static uint8_t toInactiveLevel(uint8_t activeLevel)
{
    return (activeLevel == HIGH) ? LOW : HIGH;
}

static void writeDirectionPins(const dd_traffic_light_t *tl, dd_tl_direction_t direction, dd_tl_color_t color)
{
    const dd_tl_direction_config_t *cfg = selectDirectionConfig(tl, direction);
    const uint8_t inactive = toInactiveLevel(cfg->active_level);

    digitalWrite(cfg->red_pin, inactive);
    digitalWrite(cfg->yellow_pin, inactive);
    digitalWrite(cfg->green_pin, inactive);

    if (color == DD_TL_COLOR_RED)
    {
        digitalWrite(cfg->red_pin, cfg->active_level);
    }
    else if (color == DD_TL_COLOR_YELLOW)
    {
        digitalWrite(cfg->yellow_pin, cfg->active_level);
    }
    else
    {
        digitalWrite(cfg->green_pin, cfg->active_level);
    }
}

bool ddTrafficLightCreate(dd_traffic_light_t *tl, const dd_traffic_light_config_t *config)
{
    if (!tl || !config)
    {
        return false;
    }

    tl->config = *config;
    tl->ew_color = DD_TL_COLOR_RED;
    tl->ns_color = DD_TL_COLOR_RED;
    tl->initialized = true;

    pinMode(tl->config.ew.red_pin, OUTPUT);
    pinMode(tl->config.ew.yellow_pin, OUTPUT);
    pinMode(tl->config.ew.green_pin, OUTPUT);

    pinMode(tl->config.ns.red_pin, OUTPUT);
    pinMode(tl->config.ns.yellow_pin, OUTPUT);
    pinMode(tl->config.ns.green_pin, OUTPUT);

    writeDirectionPins(tl, DD_TL_DIR_EW, DD_TL_COLOR_RED);
    writeDirectionPins(tl, DD_TL_DIR_NS, DD_TL_COLOR_RED);
    return true;
}

void ddTrafficLightInit(void)
{
    const dd_traffic_light_config_t config = {
        {DD_TL_DEFAULT_EW_RED_PIN, DD_TL_DEFAULT_EW_YELLOW_PIN, DD_TL_DEFAULT_EW_GREEN_PIN, DD_TL_DEFAULT_ACTIVE_LEVEL},
        {DD_TL_DEFAULT_NS_RED_PIN, DD_TL_DEFAULT_NS_YELLOW_PIN, DD_TL_DEFAULT_NS_GREEN_PIN, DD_TL_DEFAULT_ACTIVE_LEVEL}};
    (void)ddTrafficLightCreate(&s_defaultTrafficLight, &config);
}

void ddTrafficLightSetState(dd_traffic_light_t *tl, dd_tl_direction_t direction, dd_tl_color_t color)
{
    if (!tl || !tl->initialized)
    {
        return;
    }

    writeDirectionPins(tl, direction, color);
    if (direction == DD_TL_DIR_EW)
    {
        tl->ew_color = color;
    }
    else
    {
        tl->ns_color = color;
    }
}

void ddTrafficLightSet(dd_tl_direction_t direction, dd_tl_color_t color)
{
    ddTrafficLightSetState(&s_defaultTrafficLight, direction, color);
}

dd_tl_color_t ddTrafficLightReadState(const dd_traffic_light_t *tl, dd_tl_direction_t direction)
{
    if (!tl || !tl->initialized)
    {
        return DD_TL_COLOR_RED;
    }
    return (direction == DD_TL_DIR_EW) ? tl->ew_color : tl->ns_color;
}

dd_tl_color_t ddTrafficLightGet(dd_tl_direction_t direction)
{
    return ddTrafficLightReadState(&s_defaultTrafficLight, direction);
}
