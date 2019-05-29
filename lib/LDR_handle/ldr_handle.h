//https://portal.vidadesilicio.com.br/sensor-de-luz-com-ldr/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#define LDR_PIN A0
void inicializaLDR();
int leLDR();
void imprimeDadosLDR(uint8_t luminosidade);