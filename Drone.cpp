#include <ArduinoJson.h>
#include <SD.h>

const int analogPin = A0; // pH sensor Analog pin
const int chipSelect = 10; // SD Card Module Analog pin
const unsigned long interval = 10000; // Data logged every 10000 milliseconds
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card failed to load.");
    return;
  }
  
  Serial.println("SD card loaded.");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    float pHValue = readPHValue(); // Returns sensor pH value
    
    StaticJsonDocument<200> doc;
    doc["pH"] = pHValue;
    
    File file = SD.open("ph.json", FILE_WRITE);
    if (!file) {
      Serial.println("Failed to open file for writing.");
      return;
    }
    if (serializeJson(doc, file) == 0) {
      Serial.println("Failed to write to file.");
    }
    
    file.close();
    
    Serial.println("Data saved to ph.json"); //Writes data to the JSON file from the pH Sensor
  }
}

float readPHValue() {
  
  int sensorValue = analogRead(analogPin);
  float pHValue = map(sensorValue, 0, 1023, 0, 14);
  
  return pHValue;
}
