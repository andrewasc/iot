

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

void togglePortao () {
  if (aberto == 0)
  {
    for (pos = 0; pos < 90; pos++)
    {
      sMotor.write(pos);
    }
    delay(1000);
    digitalWrite(led, HIGH);
    aberto = 1;
  }
  else
  {
    for (pos = 90; pos > 0; pos--)
    {
      sMotor.write(pos);
    }
    delay(1000);
    digitalWrite(led, LOW);
    aberto = 0;
  }
}

void loop()
{
  estadoBotao = digitalRead(botao);
  Serial.println(estadoBotao);
  if (estadoBotao && !estadoPrev )
  {

  }
  estadoPrev = estadoBotao;
}
