#ifndef DD_BUTTON_H_
#define DD_BUTTON_H_

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef DD_BUTTON_DEFAULT_PIN
#define DD_BUTTON_DEFAULT_PIN 3
#endif

#ifndef DD_BUTTON_DEFAULT_ACTIVE_STATE
#define DD_BUTTON_DEFAULT_ACTIVE_STATE LOW
#endif

#ifndef DD_BUTTON_DEFAULT_DEBOUNCE_MS
#define DD_BUTTON_DEFAULT_DEBOUNCE_MS 50UL
#endif

#ifndef DD_BUTTON_DEFAULT_PIN_MODE
#define DD_BUTTON_DEFAULT_PIN_MODE INPUT_PULLUP
#endif

typedef struct
{
    uint8_t pin;
    uint8_t active_state;
    unsigned long debounce_ms;
    uint8_t pin_mode;
} dd_button_config_t;

typedef struct
{
    dd_button_config_t config;
    uint8_t last_raw_state;
    uint8_t stable_state;
    unsigned long last_transition_ms;
    bool initialized;
} dd_button_t;

bool ddButtonCreate(dd_button_t *button, const dd_button_config_t *config);
bool ddButtonPollPressed(dd_button_t *button);

/* Legacy single-instance API (kept for backwards compatibility). */
void ddButtonInit(void);
bool ddButtonWasPressed(void);

#endif
