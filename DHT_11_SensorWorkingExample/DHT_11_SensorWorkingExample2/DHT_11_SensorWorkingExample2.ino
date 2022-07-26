// Global Declarations
//----------------------------------------------------------------------------------------------------------------------
#include <DHT.h>

// DHT-PWR --> tied to 5V on the Arduino , DHT-GND --> tied to GND on the Arduino
#define DHTPIN 4 // The data pin for the DHT sensor should be connected to this pin of the Arduino
#define DHTTYPE DHT11

DHT dht(DHTPIN , DHTTYPE);

//----------------------------------------------------------------------------------------------------------------------

void setup()
{
  // put your setup code here, to run once:

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(2000);
  dht.begin(); // initialize DHT11 sensor

}

//----------------------------------------------------------------------------------------------------------------------

void loop() 
{
  // put your main code here, to run repeatedly:
  
  float temp = dht.readTemperature(); // read temperature data from sensor
  float humi = dht.readHumidity(); // read humidity data from sensor
  

  Serial.print("TEMPERATURE:");
  Serial.print(temp); // print humidity data from sensor to serial port
  Serial.println("");
  Serial.print("HUMIDITY:");
  Serial.print(humi); // print read humidity data from sensor to serial port
  Serial.println("");

  // toggle on board LED state for every packet of serial data transmitted
  digitalWrite(13 , !digitalRead(13) );
  
  delay(1000);
}
