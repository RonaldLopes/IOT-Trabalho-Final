#include <higrometro_handle.h>

void inicializaHigrometro(){
  pinMode(PINO_HIGROMETRO,INPUT);
}
bool leituraHigrometro(){
  return digitalRead(PINO_HIGROMETRO);
}
