#include <dht.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
#include <Adafruit_CCS811.h>

dht DHT;
#define DHT11_PIN 10
int eCO2;
int TVOC;

Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(9600);
  pinMode(2,1);
  Serial.println("CCS811 test");
  lcd.begin(16,2);
  lcd.clear();
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      eCO2 = ccs.geteCO2();
      TVOC = ccs.getTVOC();
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      lcd.setCursor(0,0);
      lcd.print("CO2:");
      lcd.setCursor(4,0);
      lcd.print(eCO2);
      lcd.setCursor(9,0);
      lcd.print("TVOC:");
      lcd.setCursor(14,0);
      lcd.print(TVOC);
      Serial.print("ppm, TVOC: ");
      Serial.print(ccs.getTVOC());
      Serial.print("ppb");
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  
  int chk = DHT.read11(DHT11_PIN);
  int humidity= DHT.humidity;
  int temp_2 = DHT.temperature;
  int gas_data = analogRead(A0);
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.setCursor(2,1);
  lcd.print(temp_2);
  lcd.setCursor(5,1);
  lcd.print("Hd:");
  lcd.setCursor(8,1);
  lcd.print(humidity);
  lcd.setCursor(11,1);
  lcd.print("O3:");
  lcd.setCursor(14,1);
  lcd.print(gas_data);
  Serial.print('\t');
  Serial.print(humidity);
  Serial.print('\t');
  Serial.print(temp_2);
  Serial.print('\t');
  Serial.println(gas_data);
  delay(2000);
  
     if(eCO2 >= 10000)
        {
          digitalWrite(2,1);
        }
           else
             {
               digitalWrite(2,0);
              }
}
