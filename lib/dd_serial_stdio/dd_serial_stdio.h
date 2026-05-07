#ifndef DD_SERIAL_STDIO_H_
#define DD_SERIAL_STDIO_H_

#include <stdio.h>
#include <Arduino.h>
#include <stdbool.h>

#ifndef DD_SERIAL_STDIO_DEFAULT_BAUDRATE
#define DD_SERIAL_STDIO_DEFAULT_BAUDRATE 9600UL
#endif

typedef struct
{
    HardwareSerial *serial;
    unsigned long baudrate;
    bool map_cr_to_lf;
} dd_serial_stdio_config_t;

int ddSerialPutChar(char ch, FILE *f);
int ddSerialGetChar(FILE *f);
bool ddSerialStdioSetupWithConfig(const dd_serial_stdio_config_t *config);
void ddSerialStdioSetup();
#endif // SRV_SERIAL_STDIO_H_