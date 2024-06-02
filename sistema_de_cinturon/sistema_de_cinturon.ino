///MAESTRO
31
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include <SoftwareSerial.h> //incluimos SoftwareSerial
#include <TinyGPS.h> //incluimos TinyGPS
#include <LiquidCrystal_I2C.h>
ezButton limitSwitch(10);

//Crear el objeto lcd dirección 0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2); //
TinyGPS gps; //Declaramos el objeto GPS
 SoftwareSerial serialgps(11,12); //Declaramos el pin 4 (Tx del GPS) y 3 (Rx del GPS)
 
 //Declaramos la variables para la obtención de datos
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
int BUZZERCINTURON = 6;
int LEDCINTURON = 7;
int LUCESLED = 9;
int LUZAVERIADA = 8;
int CINTURON = 10;
int IN1 = 2; //luz B
int IN2 = 3; //luz B
int IN3 = 4; //luz A
int IN4 = 5; //luz A
int potonof = A0; // analog pin used to connect the potentiometer
int perilla; 
int LDR = A1;
void setup() {
     Serial.begin(115200); //Iniciamos el puerto serie
     serialgps.begin(9600); //Iniciamos el puerto serie del gps
     Wire.begin();
     Serial.begin(9600); 
     limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
    // Inicializar el LCD
     lcd.init();
     
     //Encender la luz de fondo.
     lcd.backlight();
     // Escribimos el Mensaje en el LCD.
    pinMode (IN1, OUTPUT); // Input1 conectada al pin 2 motor B
    pinMode (IN2, OUTPUT); // Input2 conectada al pin 3 motor B
    pinMode (IN4, OUTPUT); // Input4 conectada al pin 4 motor A
    pinMode (IN3, OUTPUT); // Input3 conectada al pin 5 motor A
    pinMode (LUCESLED,OUTPUT);
    pinMode (BUZZERCINTURON,OUTPUT);
    pinMode (LEDCINTURON, OUTPUT);
    pinMode (LUZAVERIADA, OUTPUT);
    pinMode(11,INPUT); //REVERSA
    pinMode(12,OUTPUT); // BUZZERREV
}
void loop() {
   digitalRead(11);
   Wire.requestFrom(2, 16); /////BITS
   while(Wire.available()) // slave may send less than requested
   { 
   char c = Wire.read(); // Recibe byte a byte
   Serial.print(c); // Presenta los caracteres en el Serial Monitor
   }
   Serial.println();
  if(digitalRead(11)==1){
   digitalWrite(12,1);
   delay(1000);
   digitalWrite(12,0);
   delay(1000);
  }
  else{
   digitalWrite(12,0);
  }
  Serial.println(digitalRead(11));
  delay(100);
   limitSwitch.loop(); // MUST call the loop() function first
   if(limitSwitch.isPressed())
   Serial.println("The limit switch: UNTOUCHED -> TOUCHED");
   if(limitSwitch.isReleased())
   Serial.println("The limit switch: TOUCHED -> UNTOUCHED");
   int state = limitSwitch.getState();
   if(state == HIGH){
   
   digitalWrite (LEDCINTURON, HIGH);
   delay(1000);
   digitalWrite (LEDCINTURON, LOW);
   delay(1000);
   digitalWrite (BUZZERCINTURON, HIGH);
   delay(500); 
   digitalWrite (BUZZERCINTURON, LOW);
   delay(500);
   }
   else{
   
   digitalWrite (LEDCINTURON, LOW);
   digitalWrite (BUZZERCINTURON, LOW);
   }

   perilla = analogRead(potonof); // reads the value of the potentiometer (value between 0 and 1023)
   LDR = analogRead(A1);
  delay(50);
  if(perilla>1000){
   digitalWrite (IN1,LOW);
   digitalWrite (IN2,LOW); 
   digitalWrite (IN3,LOW);
   digitalWrite (IN4,LOW); 
   //lcd.setCursor(1,0);
  //lcd.print("LUCES APAGADAS ");
   digitalWrite (LUCESLED, LOW);
  }else if (perilla> 900 && perilla<955){
  Serial.println("LUCES OOONNNNN");
   digitalWrite (IN1,HIGH);
   digitalWrite (IN2,LOW); 
   digitalWrite (IN3,LOW);
   digitalWrite (IN4,HIGH);
   // lcd.setCursor(1,0); 
   //lcd.print("LUCES ENCENDIDAS ");
   digitalWrite (LUCESLED, HIGH);
  }else if (perilla>750 && perilla<800){
   Serial.println("LUCES AUTOMATICAS");
   if (LDR>900){
   digitalWrite (IN1,HIGH);
   digitalWrite (IN2,LOW); 
   digitalWrite (IN3,LOW);
   digitalWrite (IN4,HIGH);
   digitalWrite (LUCESLED, HIGH);
   //lcd.setCursor(1,0); 
  //lcd.print("LUCES ENCENDIDAS ");
   }else {
   digitalWrite (IN1,LOW);
   digitalWrite (IN2,LOW); 
   digitalWrite (IN3,LOW);
   digitalWrite (IN4,LOW); 
   digitalWrite (LUCESLED, LOW);
   //lcd.setCursor(1,0);
  //lcd.print("LUCES APAGADAS ");
   }
  }
}
