// Global Declarations
//----------------------------------------------------------------------------------------------------------------------

#include <SoftwareSerial.h>
int TxD;
int RxD;
int data;

SoftwareSerial bluetooth(TxD , RxD);
//----------------------------------------------------------------------------------------------------------------------
void setup() 
{
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);

}
//----------------------------------------------------------------------------------------------------------------------
void loop() 
{
  // put your main code here, to run repeatedly:

  if(bluetooth.available() > 0)
  {
    data = bluetooth.read();
    Serial.print(data);
    Serial.print("\n");
  }
  
  if(data == '2')
  {
    for (int i = 0; i < 5; i++)
    {
    
    digitalWrite(LED_BUILTIN , HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN , LOW);
    delay(500);
    }
    data = '0';
  }
  
  if(data == '1') digitalWrite(LED_BUILTIN , HIGH);
  
  if(data == '0') digitalWrite(LED_BUILTIN , LOW);
    
}
