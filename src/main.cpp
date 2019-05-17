#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"
#include "wifi_init.h"
#include "mqtt_init.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <string.h>
char* createJson(float temperatura, float umidade);

DHT dht(DHTPIN, DHTTYPE);

OneWire pino(D4);

// DallasTemperature barramento(&pino);
DeviceAddress sensor;

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);
  // iniciaGPIO();
  if (conectaWiFi()){
     iniciaMQTT();
     Serial.println("Conectou com sucesso!!!");
  }
  // barramento.begin();
  // barramento.getAddress(sensor, 0);


}

void loop() {
  // barramento.requestTemperatures();
  // float temperatura = barramento.getTempC(sensor);
  // Serial.println(temperatura);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.println(" %");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");

  }
  delay(1000);
  if (WiFi.status() == WL_CONNECTED){
      if (!MQTTClient.connected()) {
        connectaClienteMQTT();
      }
      char temp[8];
      char* jsonTemHum  = createJson(t,h);
      publicaMensagem(TOPICOSENSORIN,jsonTemHum );

      // dtostrf(t,1,2,temp);


  }else{
     if (conectaWiFi()){
     iniciaMQTT();
     }
     delay(500);
  }


}

char* createJson(float temperatura, float umidade){
    StaticJsonDocument<500> doc;
    doc["sensor"] = "DHT11";
    doc["typeSensor"]="TempHum";
    doc["time"]="1234567890";
    JsonArray values = doc.createNestedArray("data");
    values.add(temperatura);
    values.add(umidade);
    char json[256];
    serializeJson(doc, json);;
    return json;
  }
