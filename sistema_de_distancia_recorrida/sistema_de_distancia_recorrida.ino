double distancia_acumulada = 0;
const double diametro = 0.89;// cambiar de acuerdo al valor 
volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceInterval = 200;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();
 pinMode(3, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(2), interrupcion0, FALLING);
}
void loop() {
 
 int boton = digitalRead(3);
 if (not boton) {
 distancia_acumulada = 0;
 lcd.clear();
 }
 lcd.setCursor(0, 0);
 lcd.print("dist: ");
 Serial.println(distancia_acumulada, 2); 
 lcd.print(distancia_acumulada, 2); // Imprime la distancia con dos decimales
 lcd.print(" m");
}
void interrupcion0() {
 unsigned long currentMillis = millis();
 if (currentMillis - lastInterruptTime >= debounceInterval) {
 distancia_acumulada += diametro;
 lastInterruptTime = currentMillis;
 }
}
