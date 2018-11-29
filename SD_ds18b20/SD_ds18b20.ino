/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <SimpleTimer.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
SimpleTimer timer;
/********************************************************************/ 
// Define pins for the SD module
const int chipSelect = 10;
// Define vars
float temp = 0;
const int INTERVAL = 1; // in min

void setup(void) 
{ 
 Serial.begin(9600); // start serial port  

 // Intitialize the SD card
 Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
 if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
 Serial.println("card initialized.");
 File dataFile = SD.open("datalog.txt", FILE_WRITE);
  // if the file is available, write to it:
 if (dataFile) {
  String init_text = "*************NEW SESSION****************";
    dataFile.println(init_text);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
 else {
    Serial.println("error opening datalog.txt"); 
    }

 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
 sensors.begin(); 

 timer.setInterval(INTERVAL*60*1000, read_write);
}

void read_write() 
{   
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
  /********************************************************************/
  Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  temp = sensors.getTempCByIndex(0);
  
  Serial.println("DONE"); 
  /********************************************************************/
  Serial.print("Temperature is: "); 
  Serial.println(temp);
   
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(temp);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt"); 
    }
} 

void loop() {
    timer.run();
}
