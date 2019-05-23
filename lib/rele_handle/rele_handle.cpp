#include <rele_handle.h>
#define ACENDE true
#define APAGA false

void inicializaRele()
{
  pinMode(PINO_RELE,OUTPUT);
  digitalWrite(PINO_RELE,HIGH);
}

void atuaRele(boolean estado)
{
    if(estado == ACENDE)
      digitalWrite(PINO_RELE,LOW);
    else
      digitalWrite(PINO_RELE,HIGH);
}
