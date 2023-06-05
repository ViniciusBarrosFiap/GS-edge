#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//Inicializa o display no endereco 0x20
LiquidCrystal_I2C lcd(0x20,16,2);
const int sensorPin = A0;
const int sensorTempPino = A2;// pino do Sensor Temperatura
const int SensorUmidPino = A3; // pino sensor de umidade
const int greenLedPin = 6; // pino do LED verde
const int yellowLedPin = 7; // pino do LED amarelo
const int redLedPin = 8; // pino do LED vermelho
const int buzzerPin = 9; // pino da buzina
const int buzzerDuration = 3000; // tempo de duração da buzina

bool buzzerAtivo = false; //definindo buzzer ativo como falso
int porcem = 0;//porcentagem da umidade

float rLDR;
float vOut;
const float newtonsToKg = 1 / 9.81;

void setup()
{
 // definindo os pinos dos leds e da buzina como saídas
 pinMode(greenLedPin, OUTPUT);
 pinMode(yellowLedPin, OUTPUT);
 pinMode(redLedPin, OUTPUT);
 pinMode(buzzerPin, OUTPUT); 

 // inicializando display 16x2
 lcd.init();

 // exibindo mensagem inicial
 lcd.setBacklight(HIGH);
 lcd.print("Fresh Track");
 delay(2000);
 lcd.clear();
}

void loop()
{
  
  //leitura da força e conversão para kg
  int sensorValue = analogRead(sensorPin);
  float forceNewtons = sensorValue;
  float forceKg = forceNewtons * newtonsToKg;

  // Faz a leitura da tensão no Sensor de Temperatura
  int sensorTempTensao = analogRead(sensorTempPino);

  // converte a tensão lida
  float tensao = sensorTempTensao * 5;
  tensao /= 1024; // resultado da tensao

  // converte a tensão lida em Graus Celsius
  float temperaturaC = (tensao - 0.5) * 100;

  // Faz a leitura da tensao no Sensor de Umidade 
  int SensorUmidTensao=analogRead(SensorUmidPino);

  // Converte a tensao lida em porcentagem
  float porcem=map(SensorUmidTensao,0,1023,0,100);
	
  //Calcula media de 5 leituras da temperatura
  int leiturasTemp = 0;
  int mediaTemp = 0;
  for (int i = 0; i < 5; i++) {
  	leiturasTemp += temperaturaC;
    delay(400); //delay a cada leitura para maior precisão
  }
  mediaTemp = leiturasTemp / 5; //resultado média de 5 leituras da temperatura
  
  //calcula média de 5 leituras da umidade
  int leiturasUmi = 0;
  int mediaUmi = 0;
  for (int x = 0; x < 5; x++) {
  	leiturasUmi += porcem;
    delay(400); //delay a cada leitura para maior precisão
  }
  mediaUmi = leiturasUmi / 5; //resultado média de 5 leituras da umidade
  
  //Atualizando peso do estoque
  if (forceKg > 10 and forceKg < 40){
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("Estoque OK");
    lcd.setCursor(0,1);
    lcd.print(forceKg);
    lcd.print(" kg  ");
    delay(3000);
  }
  else if (forceKg > 40){
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("Estoque CHEIO");
    lcd.setCursor(0,1);
    lcd.print(forceKg);
    lcd.print(" kg  ");
    delay(3000);
  }
  
  else{
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("Estoque VAZIO");
    lcd.setCursor(0,1);
    lcd.print(forceKg);
    lcd.print(" kg  ");
    delay(3000);
  }
 
  
  //Temperatura boa
  if (mediaTemp > 15 and mediaTemp < 25){
  	digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp. = ");
    lcd.setCursor(8,1);
    lcd.print(mediaTemp);
    lcd.setCursor(10,1);
    lcd.print("C");
   	delay(1000);
  }
  //Condição para a temperatura acima de 25 graus
  else if(mediaTemp > 25){
  	digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp. ALTA");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.setCursor(8,1);
    lcd.print(mediaTemp);
    lcd.setCursor(10,1);
    lcd.print("C");
    delay(1000);
    
    // faz com que a buzina toque sem parar enquanto estiver acima de 15 graus
    if (!buzzerAtivo) {
      buzzerAtivo = true;
      while (temperaturaC > 15) {
        tone(buzzerPin, 1000);
        delay(buzzerDuration);
        noTone(buzzerPin);
        sensorTempTensao = analogRead(sensorTempPino);
    	tensao = sensorTempTensao * 5.0 / 1024.0;
    	temperaturaC = (tensao - 0.5) * 100.0;
      }
      buzzerAtivo = false;
    }
    else {
    	digitalWrite(greenLedPin, HIGH);
    	digitalWrite(yellowLedPin, LOW);
    	digitalWrite(redLedPin, LOW);
    	noTone(buzzerPin);
    	buzzerAtivo = false;
  }
    
  }
  //temperatura baixa menos que 10 graus  
  else {
    digitalWrite(greenLedPin, LOW);
  	digitalWrite(yellowLedPin, LOW);
 	digitalWrite(redLedPin, HIGH);
    
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp. BAIXA");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.setCursor(8,1);
    lcd.print(mediaTemp);
    lcd.setCursor(10,1);
    lcd.print("C");
    delay(1000);
   	// faz com que a buzina toque sem parar enquanto estiver abaixo de 10 graus
    if (!buzzerAtivo) {
      buzzerAtivo = true;
      while (temperaturaC < 10) {
        tone(buzzerPin, 1000);
        delay(buzzerDuration);
        noTone(buzzerPin);
        sensorTempTensao = analogRead(sensorTempPino);
    	tensao = sensorTempTensao * 5.0 / 1024.0;
    	temperaturaC = (tensao - 0.5) * 100.0;
      }
      buzzerAtivo = false;
    }
   	else {
    	digitalWrite(greenLedPin, HIGH);
    	digitalWrite(yellowLedPin, LOW);
    	digitalWrite(redLedPin, LOW);
    	noTone(buzzerPin);
    	buzzerAtivo = false;
  }
  }
  
  //Atualiza estado da umidade
  if (porcem > 50 and porcem < 70) {
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK");
    lcd.setCursor(0, 1);
    lcd.print("Umidade =");
    lcd.setCursor(10,1);
    lcd.print(mediaUmi);
    lcd.setCursor(12,1);
    lcd.print("%");
    delay(1000);
  }
  else if (porcem > 70) {
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade ALTA");
    lcd.setCursor(0, 1);
    lcd.print("Umidade =");
    lcd.setCursor(10,1);
    lcd.print(mediaUmi);
    lcd.setCursor(12,1);
    lcd.print("%");
    delay(1000);
  }
  
  else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade BAIXA");
    lcd.setCursor(0, 1);
    lcd.print("Umidade =");
    lcd.setCursor(10,1);
    lcd.print(mediaUmi);
    lcd.setCursor(12,1);
    lcd.print("%");
    delay(1000);
    
    if (!buzzerAtivo) {
     buzzerAtivo = true;
      while (porcem < 50) {
        tone(buzzerPin, 1000);
        delay(buzzerDuration);
        noTone(buzzerPin);
        int SensorUmidTensao=analogRead(SensorUmidPino);
        porcem=map(SensorUmidTensao,0,1023,0,100);
        
      }
      buzzerAtivo = false;
    }
   	else {
    	digitalWrite(greenLedPin, HIGH);
    	digitalWrite(yellowLedPin, LOW);
    	digitalWrite(redLedPin, LOW);
    	noTone(buzzerPin);
    	buzzerAtivo = false;
  }
  }
}