#include "dht_handle.h"

DHT dht(DHTPIN, DHTTYPE);

void inicializaDHT()
{
    dht.begin();
}

boolean leDHT(float* p_umidade, float* p_temperatura)
{   
    *p_umidade = dht.readHumidity();
    *p_temperatura = dht.readTemperature();
    if(isnan(*p_temperatura) || isnan(*p_umidade))
        return false;
    else
        return true;
}

void imprimeDadosDHT(float* p_umidade, float* p_temperatura)
{
    Serial.print("Umidade: ");
    Serial.print(*p_umidade);
    Serial.println(" %");
    Serial.print("Temperatura: ");
    Serial.print(*p_temperatura);
    Serial.println(" *C");
}
