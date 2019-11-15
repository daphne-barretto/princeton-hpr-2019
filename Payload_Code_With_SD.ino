//  for SD writing
#include <SD.h>
#include <SPI.h>

//  for sensor reading
#include <Wire.h>
#include "SparkFunMPL3115A2.h"

const int ledPin = 13;  //  built in LED pin
const int chipSelect = BUILTIN_SDCARD;  //  built in micro SD card

MPL3115A2 sensor; //  sensor object
File myFile;  //  file object

void setup()
{
  
  pinMode(ledPin, OUTPUT);      //  set up LED
  digitalWrite(ledPin, HIGH);   // set the LED on for entire program
  
  Wire.begin();        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  //  Initialize the SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  // Note: only works with "test.txt" as file name for some reason
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to file...");
    myFile.println();
    myFile.println("L1 11/16/19 Launch Data");
  // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  sensor.begin(); // Get sensor online

  //Configure the sensor
  sensor.setModeAltimeter(); // Measure altitude above sea level in meters
  sensor.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa

  sensor.setOversampleRate(7); // Set Oversample to the recommended 128
  sensor.enableEventFlags(); // Enable all three pressure and temp event flags 
}

void loop(){

  //  read sensor values

  float altitude = sensor.readAltitudeFt();
  float pressure = sensor.readPressure();
  float temperature = sensor.readTempF();

  //  write sensor values to serial
  
  Serial.print(" Altitude(ft):");
  Serial.print(altitude, 2);

  Serial.print(" Pressure(Pa):");
  Serial.print(pressure, 2);
  
  Serial.print(" Temp(f):");
  Serial.print(temperature, 2);

  Serial.println();

  //  write sensor values to SD

  myFile = SD.open("test.txt", FILE_WRITE);
  
  if (myFile) {
    
    myFile.print(" Altitude(ft):");
    myFile.print(altitude, 2);

    myFile.print(" Pressure(Pa):");
    myFile.print(pressure, 2);
    
    myFile.print(" Temp(f):");
    myFile.print(temperature, 2);
    
    myFile.println();
    myFile.close();
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}
