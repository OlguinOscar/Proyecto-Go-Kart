#include <SoftwareSerial.h> // Incluimos SoftwareSerial
#include <TinyGPS.h> // Incluimos TinyGPS
#include <LiquidCrystal_I2C.h> // Incluimos la biblioteca para el LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Configuramos el LCD

TinyGPS gps; // Declaramos el objeto GPS
SoftwareSerial serialgps(12, 13); // Declaramos el pin 12 (Rx del GPS) y 13 (Tx del GPS)

// Declaramos las variables para la obtención de datos
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;

void setup() {
    Serial.begin(115200); // Iniciamos el puerto serie
    serialgps.begin(9600); // Iniciamos el puerto serie del GPS
    lcd.init(); // Inicializamos el LCD
    lcd.backlight(); // Encendemos la retroiluminación
    lcd.setCursor(0, 0);
    lcd.print("LOADING GPS");
    delay(3000);
    lcd.clear();
  
    // Imprimimos en el monitor serial:
    Serial.println("");
    Serial.println("GPS GY-GPS6MV2 Leantec");
    Serial.println(" ---Buscando señal--- "); 
    Serial.println("");
}

void loop() {
    while (serialgps.available()) {
        int c = serialgps.read(); 
        if (gps.encode(c)) {
            float latitude, longitude;
            gps.f_get_position(&latitude, &longitude);
            lcd.setCursor(0, 0);
            lcd.print("Lat:");
            lcd.print(latitude, 5);
            lcd.setCursor(0, 1);
            lcd.print("Lon:");
            lcd.print(longitude, 5);

            Serial.print("Latitud/Longitud: "); 
            Serial.print(latitude, 5); 
            Serial.print(", "); 
            Serial.println(longitude, 5);

            gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths);
            Serial.print("Fecha: "); Serial.print(day, DEC); Serial.print("/"); 
            Serial.print(month, DEC); Serial.print("/"); Serial.print(year);
            Serial.print(" Hora: "); Serial.print(hour - 5, DEC); Serial.print(":"); 
            Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC); 
            Serial.print("."); Serial.println(hundredths, DEC);

            Serial.print("Altitud (metros): "); Serial.println(gps.f_altitude()); 
            Serial.print("Rumbo (grados): "); Serial.println(gps.f_course()); 
            Serial.print("Velocidad (kmph): "); Serial.println(gps.f_speed_kmph());
            Serial.print("Satélites: "); Serial.println(gps.satellites());
            Serial.println();

            gps.stats(&chars, &sentences, &failed_checksum);
        }
    }
}
