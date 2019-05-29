#include <ldr_handle.h>
//R1 = amarelo, violeta, vermelho, dourado 4700 ohms +- 5%
//R2 = LDR

void inicializaLDR()
{
    pinMode(LDR_PIN, INPUT);
}

int leLDR()
{
    int valor;
    valor = analogRead(LDR_PIN);
    return valor;
}

void imprimeDadosLDR(uint8_t luminosidade)
{
    Serial.print("Luminosidade   ");
    Serial.print(luminosidade);
    Serial.println();
}
