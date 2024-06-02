#include <LoRa.h>
#include "boards.h"
int counter = 0;
unsigned long ultimoTiempo = 0; 
const int portPin=25;
int valorSensor=0;
void setup()
{
 initBoard();
 // When the power is turned on, a delay is required.
 delay(1500);
 Serial.println("LoRa Sender");
 LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
 if (!LoRa.begin(LoRa_frequency)) {
 Serial.println("Starting LoRa failed!");
 while (1);
15
// attachInterrupt(digitalPinToInterrupt(2), interrupcion0, FALLING);
 }
 
}
void loop()
{
 
 valorSensor=analogRead(portPin);
Serial.println(valorSensor);
//delay(1000);
 if (valorSensor>4000){
 counter++;
 }
 Serial.print("Contador: ");
 Serial.println(counter);
 
 // send packet
 LoRa.beginPacket();
 LoRa.print("Valor Sensor: ");
 LoRa.print(valorSensor);//counter);
 LoRa.println("Contador: ");
16
 LoRa.print(counter);
 LoRa.endPacket();
#ifdef HAS_DISPLAY
 if (u8g2) {
 char buf[256];
 u8g2->clearBuffer();
 u8g2->drawStr(0, 12, "Transmitting: OK!");
 snprintf(buf, sizeof(buf), "Sending: %d", valorSensor);//counter);
 u8g2->drawStr(0, 30, buf);
 snprintf(buf, sizeof(buf), "Contador: %d", counter);
 u8g2->drawStr(0, 48, buf);
 u8g2->sendBuffer();
 }
#endif
 // counter++;
 //delay(5000);
}
