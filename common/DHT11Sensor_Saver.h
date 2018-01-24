/**
 * DHT11 Temperature and Humidity Sensor
 *
 */

#ifndef MS_DHT11_SAVER_H__
#define MS_DHT11_SAVER_H__

#include "DHT11Sensor.h"
#include "Saver.h"
// #include "sensor_values.h"

#include <Time.h>

namespace ms
{

class DHT11_Saver : public Saver
{
	public:
		DHT11_Saver( DHT11Sensor & dht11 )
		: _dht11( dht11 )
		 {
		 }

		void save( )
		{
			write( "Temperatura: " );
		}

	private:
		 DHT11Sensor & _dht11;
};


} // end namespace

#endif


