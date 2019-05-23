#include <higrometro.h>

void inicializaHigrometro(){
  pinMode(PINO_HIGROMETRO,INPUT);
}
boolean leituraHigrometro(){
  return digitalRead(PINO_HIGROMETRO);
}
