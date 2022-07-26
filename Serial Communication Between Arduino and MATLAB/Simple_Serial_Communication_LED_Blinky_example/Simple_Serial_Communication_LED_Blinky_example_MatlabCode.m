clc, clear, close all

%{
Author: Johnathan Branch
Date: 11/20/2021
Purpose: This code covers the basics of initiating Serial Communication in Matlab.
Scope: This code opens the COM port at the specified baud rate and sends data
to an Arduino board to change the status of the on board LED.
%}


%% Simple Serial Communication - LED Blinky example

% Prepare MATLAB to handle COM port
if ~isempty(instrfind);
    fclose(instrfind);
    delete(instrfind);
end

% Specify COM settings and open port
x = serial('COM3' , 'BaudRate', 9600);
fopen(x);

go = true; % Set loop to run continously

while go

    a = input(['Enter 0 to turn OFF the LED, or enter 1 to turn ON LED, ' ...
        'or enter 2 to exit the program: ']);

    fprintf(x , a);

% Break from loop and end program if user input is '2'
    if(a == 2) 
        go = false;
        fclose(x);
        "Stopping program."
    end

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%{
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
%}