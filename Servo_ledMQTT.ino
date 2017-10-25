

}#include <Servo.h>

int SERVO = 6;  // definição do pino 6 para o servo
Servo sMotor;  // declaração do servo como objeto
int pos;  // posição do servo
int botao = 2;  // definição do pino 2 para o botão
int led = 3;   // definição do pino 3 para o led
int estadoBotao = LOW;   // variável para colher o estado atual do botão
int estadoPrev = LOW;   // variável para armazenar o último estado do botão
int aberto = 0;   // variável para verificar se o portão está aberto ou fechado

void setup ()
{
  Serial.begin(9600);
  while (!Serial) {}
  sMotor.attach(SERVO);
  Serial.begin(9600);
  sMotor.write(0); // Inicia motor posição zero
  pinMode(botao, INPUT);
  pinMode(led, OUTPUT);
}

void quandoVierMensagemMQTT(char* topic, byte* payload, int length) {
  int payloadComoInt = payload[0] - '0';
  if (String(topic) == "portao") {
    settarPortao(payloadComoInt);
  }
}

void togglePortao () {
  settarPortao(!aberto);
}


void settarPortao(int estado) {
  if (estado) {
    sMotor.write(90);
    delay(1000);
    digitalWrite(led, HIGH);
    aberto = 1;
  } else {
    sMotor.write(0);
    delay(1000);
    digitalWrite(led, LOW);
    aberto = 0;
  }

  //enviar mensagem de update
  client.publish("portao", "1");
}
void abrirPortao() {
  settarPortao(0);
  for (pos = 0; pos < 90; pos++)
  {
    sMotor.write(pos);
  }
  delay(1000);
  digitalWrite(led, HIGH);
  aberto = 1;
}

void fecharPortao() {
  settarPortao(1);
  for (pos = 90; pos > 0; pos--)
  {
    sMotor.write(pos);
    delay(20);
  }
  delay(1000);
  digitalWrite(led, LOW);
  aberto = 0;
}


void verificarBotaoPortao() {
  estadoBotao = digitalRead(botao);
  Serial.println(estadoBotao);
  if (estadoBotao && !estadoPrev)
  {
    togglePortao();
  }
  estadoPrev = estadoBotao;
}

void loop()
{
  verificarBotaoPortao();
}
