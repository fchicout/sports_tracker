#include <SPI.h>
#include <SD.h>

#include <SoftwareSerial.h>

const int chipSelect = 4;

// The serial connection to the GPS module
SoftwareSerial gps(4, 3);

void setup(){
  Serial.begin(9600);
  gps.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop(){
  String dataString = "";
    
  

  while (gps.available() > 0){
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    // get the byte data from the GPS
    byte gpsData = gps.read();
    Serial.write(gpsData);
    dataString += String(gpsData);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
  }


}