#include "dd_led.h"

static dd_led_state_t s_ledState = DD_LED_OFF;

void ddLedInit(void)
{
    pinMode(LED_PIN, OUTPUT);
    ddLedSet(DD_LED_OFF);
}

void ddLedSet(dd_led_state_t state)
{
    s_ledState = state;
    digitalWrite(LED_PIN, (state == DD_LED_ON) ? HIGH : LOW);
}

void ddLedToggle(void)
{
    ddLedSet((s_ledState == DD_LED_ON) ? DD_LED_OFF : DD_LED_ON);
}

dd_led_state_t ddLedGetState(void)
{
    return s_ledState;
}
