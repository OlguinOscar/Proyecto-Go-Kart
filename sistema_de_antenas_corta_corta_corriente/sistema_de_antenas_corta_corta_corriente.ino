//////// RECEPTOR////////////////////
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SoftwareSerial.h>
#define rele 12
SoftwareSerial hc12Serial(10, 11); // TX, RX
//// teclado matricial
#include <Keypad.h>
const int ROW_NUM = 4; // número de filas
const int COLUMN_NUM = 4; // número de columnas
char keys[ROW_NUM][COLUMN_NUM] = {
  
 { '1', '2', '3', 'A' },
 { '4', '5', '6', 'B' },
 { '7', '8', '9', 'C' },
 { '*', '0', '#', 'D' }
};

byte pin_rows[ROW_NUM] = {5, 4, 3, 2}; // conecta las filas del teclado a estos pines 5, 4, 3, 2

byte pin_column[COLUMN_NUM] = { 9, 8, 7, 6 }; // conecta las columnas del teclado a estos pines 9, 8, 7, 6
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
String password = "2468"; // define tu contraseña
String enteredPassword = "";
bool emergencia = false;
void setup() {
 pinMode(rele, OUTPUT);
 Serial.begin(9600);
 hc12Serial.begin(9600);
 digitalWrite(rele, HIGH); // Encender el RELE
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("INICIANDO");
 delay(2000);
 lcd.clear();
}
void loop() {
 mostrarMensajesLCD("NORMAL","", true);
 if (hc12Serial.available() > 0) {
 // Si hay datos disponibles en el módulo HC-12
 String message = hc12Serial.readString();
 // Comprobar si el mensaje recibido es "HOLA"
 if (message == "ALERTA") {
 mostrarMensajesLCD("Corta corriente","Activado", false);
 emergencia = true;
 }
 }
 if (emergencia == true) {
 mostrarMensajesLCD("Ingresa password","y presiona # ", true);
 digitalWrite(rele, LOW); 
 while (1) {
 if (checkPassword()) {
 lcd.clear();
 mostrarMensajesLCD("SISTEMA","RESTABLECIDO", false);
 digitalWrite(rele, HIGH); // Encender el LED
 emergencia = false;
 } 
 else {
  lcd.clear();
  mostrarMensajesLCD("PASSWORD","INCORRECTO", false);
 }
 enteredPassword ="";
 break;
 }
 }
}
bool checkPassword() {
 // Lee la contraseña ingresada
 while (1) {
 char key = keypad.getKey();
 if (key) {
 if (key == '#') {
 break; // Sal del bucle al presionar el botón de confirmar
 }
 
 enteredPassword += key;
 lcd.clear();
 mostrarMensajesLCD("PASSWORD",enteredPassword, true);
 }
 }
 // Compara la contraseña ingresada con la contraseña correcta
 return enteredPassword == password;
}
void mostrarMensajesLCD(String primerMensaje, String segundoMensaje, bool saltarPausa){
 lcd.setCursor(0, 0);
 lcd.print(primerMensaje);
 lcd.setCursor(0,1); 
 lcd.print(segundoMensaje);
 if(!saltarPausa){
 delay(1500);
 lcd.clear();
 }
}
//////// EMISOR///////////////////
#include <SoftwareSerial.h>
#define buttonPin 3 // Pin donde está conectado el botón
#define ledPin 13 // Pin donde está conectado el LED integrado en Arduino
SoftwareSerial hc12Serial(10, 11); // TX, RX
int estadoBoton = 0;
void setup() {
 Serial.begin(9600);
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(ledPin, OUTPUT);
 hc12Serial.begin(9600);
}

void loop() {
 estadoBoton= digitalRead(buttonPin);
 Serial.println(estadoBoton);
 if (digitalRead(buttonPin) == HIGH) {
 // Botón presionado, enviar señal al receptor
 hc12Serial.write("ALERTA");
 digitalWrite(ledPin, HIGH);
 delay(500); // Debouncing
 }else
 digitalWrite(ledPin, LOW);
}
