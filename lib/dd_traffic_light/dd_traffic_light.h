#ifndef DD_TRAFFIC_LIGHT_H_
#define DD_TRAFFIC_LIGHT_H_

#include <stdint.h>
#include <stdbool.h>

#include <Arduino.h>

#ifndef DD_TL_DEFAULT_EW_RED_PIN
#define DD_TL_DEFAULT_EW_RED_PIN 2
#endif

#ifndef DD_TL_DEFAULT_EW_YELLOW_PIN
#define DD_TL_DEFAULT_EW_YELLOW_PIN 4
#endif

#ifndef DD_TL_DEFAULT_EW_GREEN_PIN
#define DD_TL_DEFAULT_EW_GREEN_PIN 5
#endif

#ifndef DD_TL_DEFAULT_NS_RED_PIN
#define DD_TL_DEFAULT_NS_RED_PIN 8
#endif

#ifndef DD_TL_DEFAULT_NS_YELLOW_PIN
#define DD_TL_DEFAULT_NS_YELLOW_PIN 7
#endif

#ifndef DD_TL_DEFAULT_NS_GREEN_PIN
#define DD_TL_DEFAULT_NS_GREEN_PIN 6
#endif

#ifndef DD_TL_DEFAULT_ACTIVE_LEVEL
#define DD_TL_DEFAULT_ACTIVE_LEVEL HIGH
#endif

typedef enum
{
    DD_TL_DIR_EW = 0,
    DD_TL_DIR_NS = 1
} dd_tl_direction_t;

typedef enum
{
    DD_TL_COLOR_RED = 0,
    DD_TL_COLOR_YELLOW = 1,
    DD_TL_COLOR_GREEN = 2
} dd_tl_color_t;

typedef struct
{
    uint8_t red_pin;
    uint8_t yellow_pin;
    uint8_t green_pin;
    uint8_t active_level;
} dd_tl_direction_config_t;

typedef struct
{
    dd_tl_direction_config_t ew;
    dd_tl_direction_config_t ns;
} dd_traffic_light_config_t;

typedef struct
{
    dd_traffic_light_config_t config;
    dd_tl_color_t ew_color;
    dd_tl_color_t ns_color;
    bool initialized;
} dd_traffic_light_t;

bool ddTrafficLightCreate(dd_traffic_light_t *tl, const dd_traffic_light_config_t *config);
void ddTrafficLightSetState(dd_traffic_light_t *tl, dd_tl_direction_t direction, dd_tl_color_t color);
dd_tl_color_t ddTrafficLightReadState(const dd_traffic_light_t *tl, dd_tl_direction_t direction);

/* Legacy single-instance API (kept for backwards compatibility). */
void ddTrafficLightInit(void);
void ddTrafficLightSet(dd_tl_direction_t direction, dd_tl_color_t color);
dd_tl_color_t ddTrafficLightGet(dd_tl_direction_t direction);

#endif
