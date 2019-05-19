#include <ESP8266WiFi.h>  //essa biblioteca ja vem com a IDE. Portanto, nao e preciso baixar nenhuma biblioteca adicional
//defines
#define SSID_REDE     "RAtemAP"  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "eyhv6822"  //coloque aqui a senha da rede que se deseja conectar
//constantes e variaveis globais
WiFiClient wifiClient;
//assinatura
boolean conectaWiFi(void);
//Funcaoo: faz a conexao WiFI
//Parametros: nenhum
//Retorno: nenhum
boolean conectaWiFi(void)
{
    
    wifiClient.stop();
    
    delay(500);
    Serial.println("Conectando-se a rede WiFi...");
    WiFi.begin(SSID_REDE, SENHA_REDE);
    int contDelay = 0;
    while ((WiFi.status() != WL_CONNECTED) && (contDelay < 60) ) 
    {
        delay(1000);
        Serial.print(".");
        contDelay++;
    }
    if(WiFi.status() != WL_CONNECTED)
    {
       Serial.println("");
       Serial.println("WiFi não connectado.");
       return false;
    }
    Serial.println();
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
    return true;
}
