#include "app_lab_6_1.h"

typedef enum
{
    FSM_STATE_OFF = 0,
    FSM_STATE_ON = 1
} fsm_state_t;

static fsm_state_t s_state = FSM_STATE_OFF;

static const char *fsmStateToStr(fsm_state_t state)
{
    return (state == FSM_STATE_ON) ? "ON" : "OFF";
}

static void applyStateToLed(fsm_state_t state)
{
    ddLedSet((state == FSM_STATE_ON) ? DD_LED_ON : DD_LED_OFF);
}

static void fsmToggleState(void)
{
    s_state = (s_state == FSM_STATE_OFF) ? FSM_STATE_ON : FSM_STATE_OFF;
    applyStateToLed(s_state);
    printf("FSM state -> %s\r\n", fsmStateToStr(s_state));
}

void app_lab_6_1_setup(void)
{
    ddSerialStdioSetup();
    ddButtonInit();
    ddLedInit();

    s_state = FSM_STATE_OFF;
    applyStateToLed(s_state);

    printf("\r\nLab 6.1 ready.\r\n");
    printf("FSM initial state: %s\r\n", fsmStateToStr(s_state));
    printf("Press button to toggle LED state.\r\n");
}

void app_lab_6_1_loop(void)
{
    if (ddButtonWasPressed())
    {
        fsmToggleState();
    }

    delay(5);
}
