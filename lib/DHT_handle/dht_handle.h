#include <DHT.h>
#include <Adafruit_Sensor.h>
//DHT
#define DHTPIN D6 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

extern DHT dht;

void inicializaDHT();
boolean leDHT(float*, float*);
void imprimeDadosDHT(float*, float*);