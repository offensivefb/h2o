#include <DHT.h>
#include <Wire.h> //libreria che consente la comunicazione con i2c                
#include <LiquidCrystal_I2C.h>  //libreria display i2c 
#include "DHT.h"
#define DHTPIN 7
// 7 è il pin di Arduino a cui collego il sensore di temperatura
#define DHTTYPE DHT11
// dht11 è il tipo di sensore che uso
DHT dht(DHTPIN, DHTTYPE);
//////////////////////addr, en,rw,rs,d4,d5,d6,d7,bl, blpol 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //impostazione indirizzo del display e pin del display LCD collegati all'i2c

 

int sensorPin = A0;
int sensorValues = 0;
const int Relay=3;
int pulsante = 8;
int bottone=0;
int statobottone=0;
                  
void setup() {

lcd.begin(20, 4);


Serial.begin( 9600 );
  pinMode(sensorPin, INPUT);
  pinMode(Relay, OUTPUT);

pinMode(pulsante, INPUT);
  
}

void loop() {
//sensore temp and lcd

float t = dht.readTemperature();
float h = dht.readHumidity();
// posiziono il cursore alla colonna 12 e riga 0
lcd.setCursor(13, 0);
lcd.print(t);
lcd.print(" C");

lcd.setCursor(13, 1);
lcd.print(h);
lcd.print(" %");

lcd.setCursor(0,0);
lcd.print("Temperatura");
lcd.setCursor(0,1);
lcd.print("Umidita'");

bottone = digitalRead(pulsante);  //Lettura del pulsante  

if (digitalRead(pulsante) ==1 && statobottone ==0) // viene eseguito la prima volta che vede il pulsante premuto
{
statobottone =1;
lcd.clear(),lcd.setCursor(6,1),lcd.print("LCD OFF"),delay(3000),lcd.off();
}

if (digitalRead(pulsante) ==1 && statobottone ==1){ statobottone =0;
lcd.clear(),delay(250),lcd.on();
}

//sensore terreno

Serial.print("Valore: ");
  Serial.println (analogRead(A0));
  delay(250);

    if (analogRead(A0)>700) {
    digitalWrite (Relay, HIGH),lcd.setCursor(4,3),lcd.print("TerrenoSecco");
    delay(2000);
    if (analogRead(A0)<450)
    digitalWrite(Relay, LOW),lcd.setCursor(4,3),lcd.print("TerrenoUmido");
}

}
