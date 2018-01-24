/**
 * TMP36 Analog Temperature Sensor
 *
 */

#ifndef TMP36_SENSOR_H__
#define TMP36_SENSOR_H__

#include "Sensor.h"
#include <math.h>

class LiquidCrystal;

namespace ms
{

class TMP36Sensor : public ISensor
{
	public:

	TMP36Sensor( int pin )
	: ISensor(pin)
	{
	}

  	String name() const
  	{
      return "TMP36 Sensor";
  	}

	void initialize()
	{
	}

	void uninitialize()
	{
	}

   void update()
   {
      int val = analogRead( pin );
      float volt = (val / 1024.0) * 5.0;
      _temp = ( volt - .5) * 100;
  
		delay(5);
   }

	float temperature()
	{
		return _temp;
	}

	void debugPrint()
	{
        Serial.print( name() );
        Serial.print( " " );
        Serial.print( "  Temp: " );
        Serial.print( _temp );
        Serial.println();     
	}

	void lcdPrint( LiquidCrystal & lcd )
	{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print( name() );

      lcd.setCursor(0, 1);
      lcd.print( _temp );
		lcd.print( " deg" );
	}

	private:
		int _pin;
		int _err;
		float _temp;
};

} // end namespace

#endif


