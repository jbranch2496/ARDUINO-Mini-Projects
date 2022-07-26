// Global Declarations
int value; // variable to store data from serial port
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

  if(Serial.available() > 0)
    {
      value = Serial.read();
    }

  if(value == 1) digitalWrite(13 , HIGH);

  if(value == 0) digitalWrite(13, LOW);
}
