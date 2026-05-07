#include "dd_serial_stdio.h"

static dd_serial_stdio_config_t s_activeConfig = {
    &Serial,
    DD_SERIAL_STDIO_DEFAULT_BAUDRATE,
    true};

int ddSerialGetChar(FILE *f)
{
    (void)f;
    if (!s_activeConfig.serial)
    {
        return -1;
    }

    while (!s_activeConfig.serial->available()) // asteptam pana cand sunt date disponibile
    {
        // Evită busy-wait agresiv; pe FreeRTOS va ceda CPU-ul către alte task-uri.
        delay(1);
    }

    int c = s_activeConfig.serial->read();

    // Unele terminale trimit doar CR la Enter; stdio (fgets) așteaptă LF.
    if (s_activeConfig.map_cr_to_lf && c == '\r')
        c = '\n';

    return c; // returnam caracterul citit
}
int ddSerialPutChar(char ch, FILE *f)

{
    (void)f;
    if (!s_activeConfig.serial)
    {
        return -1;
    }
    return s_activeConfig.serial->write(ch); // scriem caracterul pe seriala
}

bool ddSerialStdioSetupWithConfig(const dd_serial_stdio_config_t *config)
{
    if (!config || !config->serial)
    {
        return false;
    }

    s_activeConfig = *config;
    s_activeConfig.serial->begin(s_activeConfig.baudrate);
    FILE *srv_serial_stream = fdevopen(ddSerialPutChar,
                                       ddSerialGetChar); // asociem functiile de citire/scriere cu un flux
    if (!srv_serial_stream)
    {
        return false;
    }
    stdin = srv_serial_stream;                           // redirectionam intrarea standard
    stdout = srv_serial_stream;                          // redirectionam iesirea standard
    printf("\r\nSerial STDIO ready.\r\n");
    return true;
}

void ddSerialStdioSetup()
{
    const dd_serial_stdio_config_t config = {
        &Serial,
        DD_SERIAL_STDIO_DEFAULT_BAUDRATE,
        true};
    (void)ddSerialStdioSetupWithConfig(&config);
}