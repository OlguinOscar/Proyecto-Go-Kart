#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16,2);
#define Sensor A0
float vOUT =0.0;
float vIN=0.0;
float R1=30000.0;//30kohms resistencia
float R2=7500.0;//7.5kohms resistencia
void setup() {
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();
 
 for (int i= 3; i<14 ; i++)
 pinMode(i, OUTPUT);
}
void loop() {
 int valor=analogRead (Sensor);
 vOUT=(valor *5.0) / 1024.0;
 vIN=vOUT / (R2/(R1 + R2));
 int k = map ( vIN, 0, 24, 3 , 13);
 for ( int j=3 ; j < 14 ; j++)
 {
 if (j <= k)
 digitalWrite(j, HIGH);
 else
 digitalWrite(j, LOW);
 }
 lcd.setCursor (0,0);
 lcd.print("Voltaje:");
 Serial.println(vIN);
 
 lcd.print(vIN);
 lcd.print("v");
}
