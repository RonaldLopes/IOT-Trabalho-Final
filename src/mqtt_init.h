#include <PubSubClient.h> //Importa biblioteca MQTT
#include "topic_init.h"

//constantes e variÃ¡veis globais
PubSubClient MQTTClient(wifiClient);


//prototypes

void connectaClienteMQTT(void);
void iniciaMQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
String mensagem(byte* payload, unsigned int length);
void trataTopico(char* topic, String msg);

//
//FunÃ§Ã£o: conectando ao servidor por MQTT
//ParÃ¢metros: nenhum
//Retorno: nenhum
void connectaClienteMQTT(void) {
  // Espera atÃ© estar conectado ao servidor
  while (!MQTTClient.connected()) {
    Serial.println("Tentando MQTT connection...");

    // Tentativa de conexÃ£o
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if( MQTTClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS )) {
      Serial.println("connected: "+clientId);
      // MQTTClient.subscribe(TOPICOLAMP1);
      // MQTTClient.subscribe(TOPICOLAMP2);
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTTClient.state());
      Serial.println(" try again in 5 seconds");
      // Espera 2 segundo e tenta novamente
      delay(5000);
    }
  }
}

//FunÃ§Ã£o: inicializa parÃ¢metros de conexÃ£o clienteMQTT(endereÃ§o do
//        broker, porta e seta funÃ§Ã£o de callback)
//ParÃ¢metros: nenhum
//Retorno: nenhum
void publicaMensagem(const char* topico, const char* mensagem ){
  MQTTClient.publish(topico,mensagem);
  Serial.println("ENVIEI PARA O SERVIDOR");
}
void iniciaMQTT(void){
  MQTTClient.setServer(MQTT_SERVER, PORTA);
  MQTTClient.setCallback(mqtt_callback);
}
// Funcao para o envio dos dados


String mensagem(byte* payload, unsigned int length){

  String msg;

  //obtem a string do payload recebido
  for(int i = 0; i < length; i++)
  {
     char c = (char)payload[i];
     msg += c;
  }
  return msg;
}


//FunÃ§Ã£o: funÃ§Ã£o de callback
//        esta funÃ§Ã£o Ã© chamada toda vez que uma informaÃ§Ã£o de
//        um dos tÃ³picos subescritos chega)
//ParÃ¢metros: nenhum
//Retorno: nenhum
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
    String msg = mensagem(payload,length);

    trataTopico(topic,msg);

}
