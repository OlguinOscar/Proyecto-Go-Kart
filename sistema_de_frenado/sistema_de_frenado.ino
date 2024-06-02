#include <Arduino.h>
#include <Wire.h>
#include <TFLI2C.h>
#include <Servo.h>
Servo servoMotor;
int Rele = 2;
TFLI2C tflI2C;
int16_t tfDist;
int16_t tfAddr = TFL_DEF_ADR;
12
void setup(){
 Serial.begin(115200);
 Wire.begin(2); // Este Esclavo es el número 2
 // Cuando el Maestro le hace una petición,
 pinMode(Rele, OUTPUT); 
 servoMotor.attach(7);
 servoMotor.write(100);
}
void loop(){
 if(tflI2C.getData(tfDist, tfAddr)){
 Serial.println(String(tfDist)+ "cm/ " + String(tfDist/2.4)+" inches");
 }
 delay(100);
 if (tfDist<=200){
 digitalWrite(2,LOW);
 }else {
 digitalWrite(2, HIGH);
 }
}
