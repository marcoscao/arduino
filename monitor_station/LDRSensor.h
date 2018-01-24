/**
 * LDR Light Sensor
 *
 */

#ifndef LDRSENSOR_H__
#define LDRSENSOR_H__

#include "ILcd.h"
#include "ISensor.h"
#include <math.h>

class LiquidCrystal;

namespace ms
{

class LDRSensor : public ISensor
{
	public:

	LDRSensor( int pin )
	: ISensor(pin, INPUT, 300 ),
	  _light(0)
	{
	}

   String name() const
	{
   	return "LDR Sensor";
   }

	float light()
	{
		return _light;
	}

	private:
		float _light;

   	void _do_update()
   	{
      	int val = analogRead( getPin() );
  			_light = val;
   	}

		void _do_debug_print() const
		{
        Serial.print( "  Light: " );
        Serial.print( _light );
		}

		void _do_lcd_print( ILcd & lcd )
		{
      	lcd.print( _light );
			lcd.print( " lms" );
		}

};

} // end namespace

#endif


