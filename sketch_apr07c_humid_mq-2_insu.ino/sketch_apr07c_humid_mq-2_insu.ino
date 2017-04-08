
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22   
#include <Wire.h>
#include <BH1750.h>


//humidity temperature sensor DHT 22:
//DHT22 http://www.2150692.ru/faq/73-dht22-arduino
//pins: 2nd pin to D2

//BH1750 lightMeter:
//pins: SCL to A5, SDA to A4
//https://lesson.iarduino.ru/page/podklyuchaem-bh1750-datchik-osveschennosti-gy-30-gy-302-k-arduino/

//MQ-2 gas sensor
//AO to A0

BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);

int redLed = 13;
int greenLed = 11;
int buzzer = 10;
int smoke = A0;
int sensorThres = 400;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smoke, INPUT);
  lightMeter.begin();
  dht.begin();
  Serial.println("Running...");
  
}

void loop() {
  delay(500);

  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  
  int analogSensor = analogRead(smoke);

  Serial.print("Methane, Butane, LPG, smoke: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
}
