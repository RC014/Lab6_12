#include "dd_led.h"

static dd_led_t s_defaultLed;

static uint8_t toDigitalLevel(const dd_led_t *led, dd_led_state_t state)
{
    if (state == DD_LED_ON)
    {
        return led->config.active_level;
    }
    return (led->config.active_level == HIGH) ? LOW : HIGH;
}

bool ddLedCreate(dd_led_t *led, const dd_led_config_t *config)
{
    if (!led || !config)
    {
        return false;
    }

    led->config = *config;
    led->state = config->initial_state;
    led->initialized = true;

    pinMode(led->config.pin, OUTPUT);
    digitalWrite(led->config.pin, toDigitalLevel(led, led->state));
    return true;
}

void ddLedInit(void)
{
    const dd_led_config_t config = {
        DD_LED_DEFAULT_PIN,
        DD_LED_DEFAULT_ACTIVE_LEVEL,
        DD_LED_OFF};
    (void)ddLedCreate(&s_defaultLed, &config);
}

void ddLedSetState(dd_led_t *led, dd_led_state_t state)
{
    if (!led || !led->initialized)
    {
        return;
    }

    led->state = state;
    digitalWrite(led->config.pin, toDigitalLevel(led, state));
}

void ddLedSet(dd_led_state_t state)
{
    ddLedSetState(&s_defaultLed, state);
}

void ddLedToggleState(dd_led_t *led)
{
    if (!led || !led->initialized)
    {
        return;
    }
    ddLedSetState(led, (led->state == DD_LED_ON) ? DD_LED_OFF : DD_LED_ON);
}

void ddLedToggle(void)
{
    ddLedToggleState(&s_defaultLed);
}

dd_led_state_t ddLedReadState(const dd_led_t *led)
{
    if (!led || !led->initialized)
    {
        return DD_LED_OFF;
    }
    return led->state;
}

dd_led_state_t ddLedGetState(void)
{
    return ddLedReadState(&s_defaultLed);
}
