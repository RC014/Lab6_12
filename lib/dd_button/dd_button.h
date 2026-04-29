#ifndef DD_BUTTON_H_
#define DD_BUTTON_H_

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../include/config.h"

void ddButtonInit(void);
bool ddButtonWasPressed(void);

#endif
