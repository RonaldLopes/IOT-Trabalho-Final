#include <ldr_handle.h>
//R1 = amarelo, violeta, vermelho, dourado 4700 ohms +- 5%
//R2 = LDR

void inicializaLDR()
{
    pinMode(LDR_PIN, INPUT);
}

uint8_t leLDR()
{
    uint16_t valor;
    valor = analogRead(LDR_PIN);
    return transformaLuminosidade(valor);
}

uint8_t transformaLuminosidade(uint16_t valor)// Precisa ser implementada
{
    uint8_t porcentagem = valor;
    return porcentagem;
}

void imprimeDadosLDR(uint8_t luminosidade)
{
    Serial.print("Luminosidade   ");
    Serial.print(luminosidade);
    Serial.println();
}