#include "app_lab_6_2.h"

typedef enum
{
    FSM_LIGHT_RED = 0,
    FSM_LIGHT_YELLOW = 1,
    FSM_LIGHT_GREEN = 2
} fsm_light_state_t;

typedef struct
{
    fsm_light_state_t state;
} direction_fsm_t;

static direction_fsm_t s_ewFsm = {FSM_LIGHT_RED};
static direction_fsm_t s_nsFsm = {FSM_LIGHT_RED};
static dd_traffic_light_t s_trafficLight;
static dd_button_t s_requestButton;

static bool s_nsRequestActive = false;

static TickType_t s_ewGreenStartTick = 0;
static TickType_t s_nsGreenStartTick = 0;

static const char *stateToStr(fsm_light_state_t state)
{
    if (state == FSM_LIGHT_GREEN) return "GREEN";
    if (state == FSM_LIGHT_YELLOW) return "YELLOW";
    return "RED";
}

static dd_tl_color_t toTlColor(fsm_light_state_t state)
{
    if (state == FSM_LIGHT_GREEN) return DD_TL_COLOR_GREEN;
    if (state == FSM_LIGHT_YELLOW) return DD_TL_COLOR_YELLOW;
    return DD_TL_COLOR_RED;
}

static void applyCurrentStates(void)
{
    ddTrafficLightSetState(&s_trafficLight, DD_TL_DIR_EW, toTlColor(s_ewFsm.state));
    ddTrafficLightSetState(&s_trafficLight, DD_TL_DIR_NS, toTlColor(s_nsFsm.state));
}

static void printIntersectionState(const char *prefix)
{
    printf("%s | EW=%s | NS=%s | NS_REQ=%s\r\n",
           prefix,
           stateToStr(s_ewFsm.state),
           stateToStr(s_nsFsm.state),
           s_nsRequestActive ? "ON" : "OFF");
}

static void setDirectionState(direction_fsm_t *fsm, fsm_light_state_t nextState)
{
    if (!fsm) return;
    fsm->state = nextState;
}

static bool readRequestButtonPressedEvent(void)
{
    return ddButtonPollPressed(&s_requestButton);
}

static void transitionEwToNs(void)
{
    setDirectionState(&s_ewFsm, FSM_LIGHT_YELLOW);
    setDirectionState(&s_nsFsm, FSM_LIGHT_RED);
    applyCurrentStates();
    printIntersectionState("Transition EW->NS step 1");
    vTaskDelay(pdMS_TO_TICKS(TL_YELLOW_MS));

    setDirectionState(&s_ewFsm, FSM_LIGHT_RED);
    setDirectionState(&s_nsFsm, FSM_LIGHT_GREEN);
    applyCurrentStates();
    s_nsGreenStartTick = xTaskGetTickCount();
    printIntersectionState("Transition EW->NS step 2");
}

static void transitionNsToEw(void)
{
    setDirectionState(&s_nsFsm, FSM_LIGHT_YELLOW);
    setDirectionState(&s_ewFsm, FSM_LIGHT_RED);
    applyCurrentStates();
    printIntersectionState("Transition NS->EW step 1");
    vTaskDelay(pdMS_TO_TICKS(TL_YELLOW_MS));

    setDirectionState(&s_nsFsm, FSM_LIGHT_RED);
    setDirectionState(&s_ewFsm, FSM_LIGHT_GREEN);
    applyCurrentStates();
    s_ewGreenStartTick = xTaskGetTickCount();
    printIntersectionState("Transition NS->EW step 2");
}

static void trafficLightTask(void *pvParameters)
{
    (void)pvParameters;

    TickType_t lastWakeTick = xTaskGetTickCount();
    s_ewGreenStartTick = lastWakeTick;

    for (;;)
    {
        if (readRequestButtonPressedEvent())
        {
            s_nsRequestActive = true;
            printIntersectionState("NS request button pressed");
        }

        if (s_ewFsm.state == FSM_LIGHT_GREEN && s_nsFsm.state == FSM_LIGHT_RED)
        {
            const TickType_t elapsed = xTaskGetTickCount() - s_ewGreenStartTick;
            if (s_nsRequestActive && elapsed >= pdMS_TO_TICKS(TL_EW_GREEN_MS))
            {
                transitionEwToNs();
                s_nsRequestActive = false;
            }
        }
        else if (s_nsFsm.state == FSM_LIGHT_GREEN && s_ewFsm.state == FSM_LIGHT_RED)
        {
            const TickType_t elapsed = xTaskGetTickCount() - s_nsGreenStartTick;
            if (elapsed >= pdMS_TO_TICKS(TL_NS_GREEN_MS))
            {
                transitionNsToEw();
            }
        }

        vTaskDelayUntil(&lastWakeTick, pdMS_TO_TICKS(TL_LOOP_PERIOD_MS));
    }
}

void app_lab_6_2_setup(void)
{
    const dd_serial_stdio_config_t serialConfig = {
        &Serial,
        SERIAL_BAUDRATE,
        true};
    const dd_traffic_light_config_t tlConfig = {
        {TL_EW_RED_PIN, TL_EW_YELLOW_PIN, TL_EW_GREEN_PIN, HIGH},
        {TL_NS_RED_PIN, TL_NS_YELLOW_PIN, TL_NS_GREEN_PIN, HIGH}};
    const dd_button_config_t buttonConfig = {
        TL_REQUEST_BUTTON_PIN,
        TL_REQUEST_ACTIVE_STATE,
        TL_REQUEST_DEBOUNCE_MS,
        INPUT_PULLUP};

    (void)ddSerialStdioSetupWithConfig(&serialConfig);
    (void)ddTrafficLightCreate(&s_trafficLight, &tlConfig);
    (void)ddButtonCreate(&s_requestButton, &buttonConfig);

    setDirectionState(&s_ewFsm, FSM_LIGHT_GREEN);
    setDirectionState(&s_nsFsm, FSM_LIGHT_RED);
    applyCurrentStates();

    s_nsRequestActive = false;

    printf("\r\nLab 6.2 - Smart Traffic Light ready.\r\n");
    printf("Priority: EW stays GREEN while no NS request exists.\r\n");
    printIntersectionState("Initial");

    xTaskCreate(trafficLightTask, "tl_fsm", 512, NULL, 1, NULL);
    vTaskStartScheduler();
}

void app_lab_6_2_loop(void)
{
}
