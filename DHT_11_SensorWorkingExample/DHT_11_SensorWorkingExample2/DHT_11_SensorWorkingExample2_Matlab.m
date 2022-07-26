clc, clear, close all

%{
Author: Johnathan Branch
Date: 11/21/2021
Purpose: This code covers the basics of reading data using Serial Communication in Matlab.
Scope: This code opens the COM port at the specified baud rate and reads data
from an Arduino board that interfaces with a DHT11 temperature and humidity sensor.
Arduino Code provided below at the end.
%}

%% Simple Serial Communication - DHT11 example

% Prepare MATLAB to handle COM port
if ~isempty(instrfind);
    fclose(instrfind);
    delete(instrfind);
end

% Specify COM settings and open port
x = serial('COM3' , 'BaudRate', 9600);
fopen(x);

TempArr = []; % array to buffer temp data coming from Arduino
HumidArr = []; % array to buffer humidity data coming from Arduino

go = true;

while go % Start continous loop that ends if user input for variable a is set to '2'

clc; % Clear cmd window
SData = fscanf(x) % Get serial data and unsupress cmd window
delimiter_idx = strfind(SData , ':'); % Parse SData for data delimiter (:)
payload = SData( (delimiter_idx + 1) : (length(SData) - 1) ); % Packet data only
NumericData = str2num(payload) % Convert payload string to numeric type

if SData(1) == 'T'
    TempArr = [TempArr NumericData]; % append data to temp data array
    TempArrSize = length(TempArr) % return temp array length
end

if SData(1) == 'H'
    HumidArr = [HumidArr NumericData];  % append data to humidity data array
    HumidArrSize = length(HumidArr) % return humidity array length
end

% Get user input in cmd window here
    a = input('Enter 2 to exit the program, or just press enter to continue: ');
    
% Break from loop and end program if user input is '2'
    if(a == 2) 
        go = false;
        fclose(x);
        clc;
        TempArr ;
        HumidArr;
        UserMsg = 'Stopping program, plot of data will display now.' % Display message on cmd window to alert user 

        subplot(211);
        plot(TempArr , 'b' , 'LineWidth' , 1.5 , 'Marker' , 'h');
        title('DHT11 Temperature');
        xlabel('Samples');
        ylabel('Temperature (deg C)');
        grid

        subplot(212);
        plot(HumidArr , 'g', 'LineWidth' , 1.5 , 'Marker' , 'p');
        title('DHT11 Humidty');
        xlabel('Samples');
        ylabel('Humidity (%)');
        grid
    end

end

%{
ARDUINO CODE 

// Global Declarations
//----------------------------------------------------------------------------------------------------------------------
#include <DHT.h>

#define DHTPIN 4
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
  
  delay(2000);
}

%}