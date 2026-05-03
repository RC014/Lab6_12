#ifndef CONFIG_H
#define CONFIG_H

// Aplicație activă:
// 61 = Lab 6.1 (automat finit LED + buton)
// 62 = Lab 6.2 (rezervat/extensii)
#define ACTIVE_APP_LAB 62

// Serial communication
#define SERIAL_BAUDRATE 9600

// ---------- Lab 6.1: LED FSM controlat de buton ----------
#define LED_PIN 13
#define BUTTON_PIN 3

// Buton pe INPUT_PULLUP => apăsat când pinul este LOW.
#define BUTTON_ACTIVE_STATE LOW
#define BUTTON_DEBOUNCE_MS 50

// ---------- Lab 6.2: Semafor inteligent ----------
// Mapare conform diagram.json (Wokwi): fiecare axa foloseste EXACT reteaua R+Y+G cu acelasi sufix
// (altfel pe un stâlp vezi rosu de pe o axa si verde de pe cealalta).
//
// Axa A (retea "A" din schema): ROSU pin 2 (led7+led12), GALBEN pin 4 (led2+led4), VERDE pin 5 (led9+led11)
// Axa B: ROSU pin 8 (led6+led8), GALBEN pin 7 (led1+led3), VERDE pin 6 (led10+led5)
//
// Legare logica: Nord-Sud = axa A | Est-Vest = axa B (schimba doar daca pe masa e invers).
#define TL_EW_RED_PIN 2
#define TL_EW_YELLOW_PIN 4
#define TL_EW_GREEN_PIN 5
#define TL_NS_RED_PIN 8
#define TL_NS_YELLOW_PIN 7
#define TL_NS_GREEN_PIN 6

// Buton cerere NS: in diagram.json = mega:3 (D3). Daca folosesti A3 pe Mega, pune A3.
#define TL_REQUEST_BUTTON_PIN 3
#define TL_REQUEST_ACTIVE_STATE LOW
#define TL_REQUEST_DEBOUNCE_MS 50

// Timpi semafor (ms)
#define TL_EW_GREEN_MS 4000
#define TL_NS_GREEN_MS 3000
#define TL_YELLOW_MS 1000
#define TL_LOOP_PERIOD_MS 20

#endif
