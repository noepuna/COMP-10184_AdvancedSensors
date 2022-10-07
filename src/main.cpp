//I, Noe Puna, 000781646, I acknowledge that this my own work and no other
// person's work has been copied without acknowledgement.

// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

DeviceAddress tempDeviceAddress;
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  int deviceID = DS18B20.getAddress(tempDeviceAddress, 0);

  if (deviceID){
    Serial.println("DEVICE ID: " + String(deviceID));
  } else {
    Serial.println("DISCONNECTED");
    Serial.end();
    
  }
  
} 
 
void loop() { 
  float fTemp; 
  String judgement;
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
 
  // print the temp to the USB serial monitor 
  
  if (fTemp < 10){
    judgement = ", which is Too Cold!";
  }else if(fTemp > 9 && fTemp < 16){
    judgement = ", which is Cool!";
  }else if(fTemp > 14 && fTemp < 26){
    judgement = ", which is Perfect!";
  }else if(fTemp > 24 && fTemp < 31){
    judgement = ", which is Warm!";
  }else if(fTemp > 29 && fTemp < 36){
    judgement = ", which is Hot!";
  }else if(fTemp > 35){
    judgement = ", which is Too Hot!";
  }
  
  // print value to the USB port 
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + judgement); 
 
  // wait 2s (5000ms) before doing this again 
  delay(5000); 
} 

