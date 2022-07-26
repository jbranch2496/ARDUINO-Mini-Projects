#include <SoftwareSerial.h>

SoftwareSerial hc08(2,3); // RX pin, TX pin

void setup()
{
  //Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("ENTER AT Commands:");
  //Initialize Bluetooth Serial Port
  hc08.begin(9600);
}

void loop()
{
  //Write data from HC08 to Serial Monitor
  if (hc08.available()){
    Serial.println("Reading from bluetooth");
    Serial.write(hc08.read());
  }
  
  //Write from Serial Monitor to HC08
  if (Serial.available()){
    Serial.println("Writing to bluetooth");
    hc08.write(Serial.read());
  }  
}
