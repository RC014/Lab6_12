#ifndef DD_LED_H_
#define DD_LED_H_

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef DD_LED_DEFAULT_PIN
#define DD_LED_DEFAULT_PIN 13
#endif

#ifndef DD_LED_DEFAULT_ACTIVE_LEVEL
#define DD_LED_DEFAULT_ACTIVE_LEVEL HIGH
#endif

typedef enum
{
    DD_LED_OFF = 0,
    DD_LED_ON = 1
} dd_led_state_t;

typedef struct
{
    uint8_t pin;
    uint8_t active_level;
    dd_led_state_t initial_state;
} dd_led_config_t;

typedef struct
{
    dd_led_config_t config;
    dd_led_state_t state;
    bool initialized;
} dd_led_t;

bool ddLedCreate(dd_led_t *led, const dd_led_config_t *config);
void ddLedSetState(dd_led_t *led, dd_led_state_t state);
void ddLedToggleState(dd_led_t *led);
dd_led_state_t ddLedReadState(const dd_led_t *led);

/* Legacy single-instance API (kept for backwards compatibility). */
void ddLedInit(void);
void ddLedSet(dd_led_state_t state);
void ddLedToggle(void);
dd_led_state_t ddLedGetState(void);

#endif
