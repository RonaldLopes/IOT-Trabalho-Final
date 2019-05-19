#include <PubSubClient.h> //Importa biblioteca MQTT
#include "topic_init.h"

#define MQTT_SERVER "iotsaeg.nc2.iff.edu.br"
#define MQTT_USER   "saeg"
#define MQTT_PASS   "semsenha"
#define PORTA   1883

//constantes e variaveis globais
PubSubClient MQTTClient(wifiClient);

//assinaturas
void connectaClienteMQTT(void);
void iniciaMQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
String mensagem(byte* payload, unsigned int length);
void trataTopico(char* topic, String msg);

//Funcao: conectando ao servidor por MQTT
//Parametros: nenhum
//Retorno: nenhum
void connectaClienteMQTT(void) {
  // Espera ate estar conectado ao servidor
  while (!MQTTClient.connected()) 
  {
    Serial.println("Tentando MQTT connection...");
    // Tentativa de conexao
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if( MQTTClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS )) 
    {
      Serial.println("Cliente MQTT conectado: "+clientId);
    }else
    {
      Serial.print("Falha, rc=");
      Serial.print(MQTTClient.state());
      Serial.println("Nova tentativa em 5 segundos ...");
      // Espera 5 segundo e tenta novamente
      delay(5000);
    }
  }
}

//Funcaoo: inicializa parametros de conexao clienteMQTT(endereco do
//        broker, porta e seta funcao de callback)
//Parametros: nenhum
//Retorno: nenhum
void publicaMensagem(const char* topico, const char* mensagem )
{
  MQTTClient.publish(topico,mensagem);
  Serial.println("Conteudo publicado no servidor!");
}

void iniciaMQTT(void)
{
  MQTTClient.setServer(MQTT_SERVER, PORTA);
  MQTTClient.setCallback(mqtt_callback);
}

String mensagem(byte* payload, unsigned int length)
{
  String msg;
  //obtem a string do payload recebido
  unsigned int i;
  for(i = 0; i < length; i++)
  {
     char c = (char)payload[i];
     msg += c;
  }
  return msg;
}

//Funcao: funcao de callback
//        esta funcao e chamada toda vez que uma informacao de
//        um dos topicos subescritos chega
//Parametros: nenhum
//Retorno: nenhum
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
    String msg = mensagem(payload,length);
    trataTopico(topic,msg);
}
