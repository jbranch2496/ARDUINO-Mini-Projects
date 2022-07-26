/*
Example sketch using a DHT_11 temperature and humidity sensor and 16x2 Liquid Crystal Display. Uses the LCD setup as default but can be easily modified by uncommenting
the code in the setup and main function to use the Serial Port.
Developer: J. Branch
Date: 07/12/2020

 The circuit:
 * DHT_11 senosr data pin to digital pin 2
 
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * 5.1K OHM resistor to LCD VO pin (pin 3)

- Derived in part from the Display example from the Arduino LCD library[public domain]
- Derived in part from the DHT_nonblocking example from the ELEGOO sensor v2 kit[free SW under the GNU public license] <http://www.gnu.org/licenses/>
*/

// include the library code:
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* Uncomment according to your sensortype. */
#define DHT_SENSOR_TYPE DHT_TYPE_11
//#define DHT_SENSOR_TYPE DHT_TYPE_21
//#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // set up the Serial Port
  // Serial.begin(9600);
}

/*
 * Main program loop.
 */
void loop( )
{
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    temperature = (temperature*1.8)+32; // convert C to F
    lcd.setCursor(0,0);
    lcd.print(F( "Temp= " ));
    lcd.print( temperature, 1 );
    lcd.print(F( " deg.F"));
    lcd.setCursor(0,1);
    lcd.print(F( "Hum = " ));
    lcd.print( humidity, 1 );
    lcd.print(F( "%" ));
   
    /*
     *     Serial.print( "Temp = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg.F, Humidity = ");
    Serial.print( humidity, 1 );
    Serial.print( "%" );
    Serial.println();
     */
  }
}
