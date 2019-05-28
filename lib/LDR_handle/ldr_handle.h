//https://portal.vidadesilicio.com.br/sensor-de-luz-com-ldr/
//#include <Arduino.h>
#include <ESP8266WiFi.h>
#define LDR_PIN A0
void inicializaLDR();
uint8_t leLDR();
uint8_t transformaLuminosidade(uint16_t);
void imprimeDadosLDR(uint8_t luminosidade);