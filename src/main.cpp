#include <Arduino.h>
#include <string.h>
#include <dht_handle.h>
#include <json_handle.h>
#include <ldr_handle.h>
#include <rele_handle.h>
#include <higrometro_handle.h>
#include "wifi_init.h"
#include "mqtt_init.h"

void setup()
{
    Serial.begin(115200);
    inicializaDHT();
    inicializaLDR();
    inicializaHigrometro();
    inicializaRele();
    delay(1000);
    if (conectaWiFi())
    {
        iniciaMQTT();
        Serial.println("Wifi conectada com sucesso, MQTT inicializado!!!");
    }
    else
    {
        Serial.println("WiFi não conectou!");
    }
    atuaRele(false);
}

void loop()
{
    uint8_t luminosidade;
    float umidade_dht11;
    float temperatura_dht11;
    bool umidadeSolo;
    float * p_umidade_dht11 = &umidade_dht11, *p_temperatura_dht11 = &temperatura_dht11;
    //DHT
    boolean flagLeituraDHT;
    flagLeituraDHT = leDHT(p_umidade_dht11,p_temperatura_dht11);
    if(flagLeituraDHT)
        imprimeDadosDHT(p_umidade_dht11, p_temperatura_dht11);
    else
        Serial.println("Falha na leitura de DHT");
    //LDR
    luminosidade = leLDR();
    imprimeDadosLDR(luminosidade);
    //Higrometro
    umidadeSolo = leituraHigrometro();
    //Rele
    if(WiFi.status() == WL_CONNECTED)
    {
        if (!MQTTClient.connected())
            connectaClienteMQTT();
        if(flagLeituraDHT)
            publicaMensagem(TOPICOSENSORIN,createJson(temperatura_dht11,umidade_dht11, luminosidade, umidadeSolo));
        MQTTClient.loop();
    }
    else
    {
        if(conectaWiFi())
            iniciaMQTT();
        delay(500);
    }
    delay(100);
}
