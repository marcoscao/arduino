#ifndef SENSORSMANAGER_H__
#define SENSORSMANAGER_H__

#include "ISensor.h"
#include "IManager.h"
#include "BasicLed.h"

namespace ms
{

class SensorsManager : public IManager
{
	public:
   	SensorsManager( IDevice** sensors_list, int total )
		: 	IManager( sensors_list, total )
    	{
    	}

		bool setSensorBlinkLed( unsigned int sensor_index, BlinkLed* p )
		{
			if( sensor_index >= getTotalObjects() )
				return false;

			ISensor * ps = static_cast<ISensor*>( getObject(sensor_index) );
			ps->setBlinkLed( p );

			return true;
		}

	private:

		virtual void _do_initialize( IDevice* p )
		{
			p->enable();
			p->activate();
		}

		virtual void _do_uninitialize( IDevice* p )
		{
			p->disable();
			p->deactivate();
		}

		virtual void _do_update( IDevice* p )
		{
			if(not p )
			{
				return;
			}

			p->update();

		}

		virtual void _do_debug_print( IDevice* p )
		{
			p->debugPrint();
		}

};

}

#endif


