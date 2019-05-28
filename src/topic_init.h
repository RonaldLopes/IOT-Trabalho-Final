
#define TOPICOSENSORIN "/medidores/input"
#define TOPICOOUT "/medidores/output"

//
//Funcao: Trata o valor do Topico
//Parametros: nenhum
//Retorno: nenhum
void trataTopico(char* topic,String msg)
{
    if (strcmp(topic,TOPICOOUT)==0)
    {
        if(msg.equals("true"))
            atuaRele(true);
        if(msg.equals("false"))
            atuaRele(false);
    }
    Serial.print(msg);
    Serial.println();
    Serial.println(topic);
}
