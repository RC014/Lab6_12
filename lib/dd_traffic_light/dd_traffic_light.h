#ifndef DD_TRAFFIC_LIGHT_H_
#define DD_TRAFFIC_LIGHT_H_

#include <stdint.h>

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

void ddTrafficLightInit(void);
void ddTrafficLightSet(dd_tl_direction_t direction, dd_tl_color_t color);
dd_tl_color_t ddTrafficLightGet(dd_tl_direction_t direction);

#endif
