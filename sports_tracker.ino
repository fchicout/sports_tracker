#include <SPI.h>
#include <SD.h>

#include <SoftwareSerial.h>

// Pinning
int thermistorPin = A0; // Thermistor Pin
int GPSRX = A4;
int GPSTX = A3;
int GPS_Serial_Baud = 9600;

// Global Variables
File logData; // Log File Pointer

int Vo; // Thermistor voltage read
float R1 = 10000; // Fix with own thermistor resistance;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

SoftwareSerial gpsSerial(GPSRX, GPSTX);

void setup() {
  // Initialize SD Card
  Serial.begin(115200); // Serial Monitor!
  while (!Serial) {
    ;
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // Initialize GPS
 gpsSerial.begin(GPS_Serial_Baud);
}

void loop() {
  logData = SD.open("logdata.csv", FILE_WRITE);

  Vo = analogRead(thermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  while(gpsSerial.available() > 0){
    
    if (logData) {
      logData.print(T);
      logData.print(",");
      logData.println(gpsSerial.read());
      logData.close();
    }
  }
}

