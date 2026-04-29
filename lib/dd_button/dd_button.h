#ifndef DD_BUTTON_H_
#define DD_BUTTON_H_

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>

void ddButtonInit(void);
bool ddButtonWasPressed(void);

#endif
