#include <SPI.h>
#include <SD.h>

#include <SoftwareSerial.h>

File logData;

void setup(){
  Serial.begin(9600); // Serial Monitor!
  while(!Serial){
    ;
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
}

void loop(){
  logData = SD.open("logdata.csv", FILE_WRITE);

  if(logData) {
    logData.print("bodyTemperature");
    logData.println("GPS DATA");
    logData.close();
  }
}

