#include "app_lab_6_1.h"


typedef enum
{
    FSM_STATE_OFF = 0,
    FSM_STATE_ON = 1
} fsm_state_t;

static fsm_state_t s_state = FSM_STATE_OFF;
static dd_led_t s_led;
static dd_button_t s_button;

static const char *fsmStateToStr(fsm_state_t state)
{
    return (state == FSM_STATE_ON) ? "ON" : "OFF";
}

static void applyStateToLed(fsm_state_t state)
{
    ddLedSetState(&s_led, (state == FSM_STATE_ON) ? DD_LED_ON : DD_LED_OFF);
}

static void fsmToggleState(void)
{
    s_state = (s_state == FSM_STATE_OFF) ? FSM_STATE_ON : FSM_STATE_OFF;
    applyStateToLed(s_state);
    printf("FSM state -> %s\r\n", fsmStateToStr(s_state));
}

void app_lab_6_1_setup(void)
{
    const dd_serial_stdio_config_t serialConfig = {
        &Serial,
        SERIAL_BAUDRATE,
        true};
    const dd_button_config_t buttonConfig = {
        BUTTON_PIN,
        BUTTON_ACTIVE_STATE,
        BUTTON_DEBOUNCE_MS,
        INPUT_PULLUP};
    const dd_led_config_t ledConfig = {
        LED_PIN,
        HIGH,
        DD_LED_OFF};

    (void)ddSerialStdioSetupWithConfig(&serialConfig);
    (void)ddButtonCreate(&s_button, &buttonConfig);
    (void)ddLedCreate(&s_led, &ledConfig);

    s_state = FSM_STATE_OFF;
    applyStateToLed(s_state);

    printf("\r\nLab 6.1 ready.\r\n");
    printf("FSM initial state: %s\r\n", fsmStateToStr(s_state));
    printf("Press button to toggle LED state.\r\n");
}

void app_lab_6_1_loop(void)
{
    if (ddButtonPollPressed(&s_button))
    {
        fsmToggleState();
    }

    delay(5);
}
