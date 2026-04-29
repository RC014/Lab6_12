#ifndef DD_LED_H_
#define DD_LED_H_

#include <Arduino.h>

typedef enum
{
    DD_LED_OFF = 0,
    DD_LED_ON = 1
} dd_led_state_t;

void ddLedInit(void);
void ddLedSet(dd_led_state_t state);
void ddLedToggle(void);
dd_led_state_t ddLedGetState(void);

#endif
