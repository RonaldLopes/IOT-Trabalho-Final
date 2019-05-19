#include "json_handle.h"

char* createJson(float temperatura, float umidade)
{
    StaticJsonDocument<500> doc;
    doc["sensor"] = "DHT11";
    doc["typeSensor"]="TempHum";
    doc["time"]="1234567890";
    JsonArray values = doc.createNestedArray("data");
    values.add(temperatura);
    values.add(umidade);
    char serialized_json[256];
    serializeJson(doc, serialized_json);;
    return serialized_json;
}