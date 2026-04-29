#include <Arduino.h>
#include "../include/config.h"

#if ACTIVE_APP_LAB == 61
#include "../lib/app_lab_6_1/app_lab_6_1.h"
#elif ACTIVE_APP_LAB == 62
#include "../lib/app_lab_6_2/app_lab_6_2.h"
#endif

void setup(void)
{
#if ACTIVE_APP_LAB == 61
  app_lab_6_1_setup();
#elif ACTIVE_APP_LAB == 62
  app_lab_6_2_setup();
#endif
}

void loop(void)
{
#if ACTIVE_APP_LAB == 61
  app_lab_6_1_loop();
#elif ACTIVE_APP_LAB == 62
  app_lab_6_2_loop();
#endif
}
