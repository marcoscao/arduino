/**
 * DHT11 Temperature and Humidity Sensor
 *
 */

#ifndef MS_DHT11SENSOR_DECORATOR20x4H__
#define MS_DHT11SENSOR_DECORATOR20x4H__

#include "DHT11Sensor.h"
#include "Decorator.h"

namespace ms
{
  
class DHT11Sensor_Decorator20x4 : public ms::Decorator
{
	public:
		DHT11Sensor_Decorator20x4( DHT11Sensor & dht11 )
		: _dht11( dht11 )
		 {
		 }

		void render( int frame )
		{
			print( 0, 0, _dht11.name() );

			if( frame == 0 || frame == 1 )
				print( 0, 2, "Temperatura: ", _dht11.temperature().current );
			else
				print( 0, 2, "Humedad: ", _dht11.humidity().current );

			switch( frame )
			{
				case 0 : print( 0, 3, "MAX: ", _dht11.temperature().hist_max ); break;
				case 1 : print( 0, 3, "MIN: ", _dht11.temperature().hist_min ); break;
				case 2 : print( 0, 3, "MAX: ", _dht11.humidity().hist_max ); break;
				case 3 : print( 0, 3, "MIN: ", _dht11.humidity().hist_min ); break;
			}					
		}

	private:
		 DHT11Sensor & _dht11;
};



} // end namespace

#endif


