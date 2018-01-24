/**
 * KY013 Analog Temperature Sensor
 *
 */

#ifndef KY013SENSOR_H__
#define KY013SENSOR_H__

#include "ISensor.h"
#include "ILcd.h"
#include <math.h>

class LiquidCrystal;

namespace ms
{

class KY013Sensor : public ISensor
{
	public:

	KY013Sensor( int pin )
	: ISensor(pin, INPUT, 110 )
	{
	}

   String name() const
	{
   	return "KY013 Sensor";
   }

	float temperature()
	{
		return _temp;
	}

	private:
		float _temp;

   	void _do_update()
   	{
      	int val = analogRead( getPin() );

  			_temp = log(((10240000/val) - 10000));
  			_temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * _temp * _temp ))* _temp );
  			_temp = _temp - 273.15;

      	//int RawADC = val;
      	//double temp = val;
      	//double Vo;
      	//Vo=float(RawADC)*(3.3/4095);
      	//temp = log(10000*(3.3/Vo-1));
      	////Temp = log(((10240000/RawADC) - 10000));
      	//temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
      	//temp = temp - 273.15;// Convert Kelvin to Celcius
   	}

		void _do_debug_print() const
		{
        Serial.print( "  Temp: " );
        Serial.print( _temp );
		}

		void _do_lcd_print( ILcd & lcd )
		{
      	lcd.print( _temp );
			lcd.print( " deg" );
		}

};

} // end namespace

#endif


