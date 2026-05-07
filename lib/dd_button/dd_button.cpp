#include "dd_button.h"

static dd_button_t s_defaultButton;

bool ddButtonCreate(dd_button_t *button, const dd_button_config_t *config)
{
    if (!button || !config)
    {
        return false;
    }

    button->config = *config;
    pinMode(button->config.pin, button->config.pin_mode);
    button->last_raw_state = (uint8_t)digitalRead(button->config.pin);
    button->stable_state = button->last_raw_state;
    button->last_transition_ms = millis();
    button->initialized = true;

    return true;
}

void ddButtonInit(void)
{
    const dd_button_config_t config = {
        DD_BUTTON_DEFAULT_PIN,
        DD_BUTTON_DEFAULT_ACTIVE_STATE,
        DD_BUTTON_DEFAULT_DEBOUNCE_MS,
        DD_BUTTON_DEFAULT_PIN_MODE};
    (void)ddButtonCreate(&s_defaultButton, &config);
}

bool ddButtonPollPressed(dd_button_t *button)
{
    if (!button || !button->initialized)
    {
        return false;
    }

    const uint8_t rawState = (uint8_t)digitalRead(button->config.pin);
    const unsigned long nowMs = millis();

    if (rawState != button->last_raw_state)
    {
        button->last_raw_state = rawState;
        button->last_transition_ms = nowMs;
    }

    if ((nowMs - button->last_transition_ms) >= button->config.debounce_ms &&
        button->stable_state != button->last_raw_state)
    {
        button->stable_state = button->last_raw_state;
        return (button->stable_state == button->config.active_state);
    }

    return false;
}

bool ddButtonWasPressed(void)
{
    return ddButtonPollPressed(&s_defaultButton);
}
