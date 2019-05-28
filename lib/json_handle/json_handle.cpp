#include "json_handle.h"

char* createJson(float temperatura, float umidadeAr, uint8_t luminosidade, bool umidadeSolo)
{
    StaticJsonDocument<500> doc;
    doc["Temperatura"] = temperatura;
    doc["UmidadeAr"]= umidadeAr;
    doc["Luminosidade"] = luminosidade;
    doc["UmidadeSolo"] = umidadeSolo;
    char serialized_json[256];
    serializeJson(doc, serialized_json);;
    return serialized_json;
}