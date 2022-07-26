clc, clear, close all

%{
Author: Johnathan Branch
Date: 11/24/2021
Purpose: This code covers the basics of sending data using Bluetooth Low Energy(BLE) in Matlab.
Scope: This code initiates communication between the computer's bluetooth (wins 10 laptop) and
an Arduino board that uses a HC-08 BLE device to convert the received BLE data to serial data to blink an on board LED.
Arduino Code provided below at the end.
%}

%% Simple BLE Communication - HC-08 example

clear all;
devlist = blelist;
dev_indexes = strfind(devlist.Name , 'SH-HC-08');
for i = 1:size(dev_indexes)
    if dev_indexes{i} == 1
        ble_idx = i;
        break
    end
end

bt = ble(devlist.Address(ble_idx));
c = characteristic(bt , "FFE0" , "FFE1");


go = true; % Set loop to run continously

while go

    a = input(['Enter 0 to turn OFF the LED, or enter 1 to turn ON LED, ' ...
        'enter 2 to blink the LED, or enter 5 to exit the program: ']);

    if (a == 0)
         write(c, "0" , "withoutresponse");
    end

    if (a == 1)
        write(c, "1" , "withoutresponse");
    end

    if (a == 2)
        write(c, "2" , "withoutresponse");
    end
    
% Break from loop and end program if user input is '5'
    if (a == 5) 
        go = false;
        "Stopping program."
    end

end

%{
ARDUINO CODE
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
%}