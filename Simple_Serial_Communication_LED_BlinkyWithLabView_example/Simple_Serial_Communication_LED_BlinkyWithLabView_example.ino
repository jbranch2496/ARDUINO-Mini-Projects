// Global Declarations
char buffer; // variable to store data from serial port
String str;  // variable to contain concatenated chars from serial port
//----------------------------------------------------------------------------------------------------------------------
 
 // the setup function runs once when you press reset or power the board 
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // setup serial port
  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() 
{

  while(Serial.available() > 0)
    {
      buffer = ((byte)Serial.read());
      str += buffer;
      //Serial.println(str);
      //Serial.write(buffer);

      delay(1);
      
      if(str.indexOf("LED_ON") > -1) 
      {
        digitalWrite(13 , HIGH);
        Serial.println("ON");
        Serial.flush();
        str = "";
      }

      if(str.indexOf("LED_OFF") > -1)  
      {
        digitalWrite(13, LOW);
        Serial.println("OFF");
        Serial.flush();
        str = "";
      }
    }
}
