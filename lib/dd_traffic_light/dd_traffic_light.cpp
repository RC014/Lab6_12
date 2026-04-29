#include "dd_traffic_light.h"

#include <Arduino.h>

#include "../../include/config.h"

static dd_tl_color_t s_ewColor = DD_TL_COLOR_RED;
static dd_tl_color_t s_nsColor = DD_TL_COLOR_RED;

static void writeDirectionPins(dd_tl_direction_t direction, dd_tl_color_t color)
{
    uint8_t redPin = TL_EW_RED_PIN;
    uint8_t yellowPin = TL_EW_YELLOW_PIN;
    uint8_t greenPin = TL_EW_GREEN_PIN;

    if (direction == DD_TL_DIR_NS)
    {
        redPin = TL_NS_RED_PIN;
        yellowPin = TL_NS_YELLOW_PIN;
        greenPin = TL_NS_GREEN_PIN;
    }

    digitalWrite(redPin, (color == DD_TL_COLOR_RED) ? HIGH : LOW);
    digitalWrite(yellowPin, (color == DD_TL_COLOR_YELLOW) ? HIGH : LOW);
    digitalWrite(greenPin, (color == DD_TL_COLOR_GREEN) ? HIGH : LOW);
}

void ddTrafficLightInit(void)
{
    pinMode(TL_EW_RED_PIN, OUTPUT);
    pinMode(TL_EW_YELLOW_PIN, OUTPUT);
    pinMode(TL_EW_GREEN_PIN, OUTPUT);

    pinMode(TL_NS_RED_PIN, OUTPUT);
    pinMode(TL_NS_YELLOW_PIN, OUTPUT);
    pinMode(TL_NS_GREEN_PIN, OUTPUT);

    ddTrafficLightSet(DD_TL_DIR_EW, DD_TL_COLOR_RED);
    ddTrafficLightSet(DD_TL_DIR_NS, DD_TL_COLOR_RED);
}

void ddTrafficLightSet(dd_tl_direction_t direction, dd_tl_color_t color)
{
    writeDirectionPins(direction, color);
    if (direction == DD_TL_DIR_EW)
    {
        s_ewColor = color;
    }
    else
    {
        s_nsColor = color;
    }
}

dd_tl_color_t ddTrafficLightGet(dd_tl_direction_t direction)
{
    return (direction == DD_TL_DIR_EW) ? s_ewColor : s_nsColor;
}
