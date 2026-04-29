#include "dd_button.h"

static uint8_t s_lastRawState = HIGH;
static uint8_t s_stableState = HIGH;
static unsigned long s_lastTransitionMs = 0;

void ddButtonInit(void)
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    s_lastRawState = (uint8_t)digitalRead(BUTTON_PIN);
    s_stableState = s_lastRawState;
    s_lastTransitionMs = millis();
}

bool ddButtonWasPressed(void)
{
    const uint8_t rawState = (uint8_t)digitalRead(BUTTON_PIN);
    const unsigned long nowMs = millis();

    if (rawState != s_lastRawState)
    {
        s_lastRawState = rawState;
        s_lastTransitionMs = nowMs;
    }

    if ((nowMs - s_lastTransitionMs) >= BUTTON_DEBOUNCE_MS && s_stableState != s_lastRawState)
    {
        s_stableState = s_lastRawState;
        return (s_stableState == BUTTON_ACTIVE_STATE);
    }

    return false;
}
