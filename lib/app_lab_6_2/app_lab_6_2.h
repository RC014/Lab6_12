#ifndef APP_LAB_6_2_H
#define APP_LAB_6_2_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../include/config.h"
#include "../dd_button/dd_button.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "../dd_traffic_light/dd_traffic_light.h"

void app_lab_6_2_setup(void);
void app_lab_6_2_loop(void);

#endif
