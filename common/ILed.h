#ifndef MS_ILED_H__
#define MS_ILED_H__

#include "IDevice.h"

namespace ms 
{

class ILed : public IDevice
{
	public:
		ILed(	int pin, 
				Timer wait_ready_timer = Timer(50, Timer::TIMER_ONCE ),
				Timer update_timer = Timer() )
		: IDevice(pin,	OUTPUT,  
				wait_ready_timer , update_timer  )
		{
		}

	private:

		virtual bool _do_initialize() 
		{
	   	if(isDigitalPin() )
				digitalWrite( getPin(), LOW );

			return true;
		}

		virtual bool _do_uninitialize() 
		{
	   	if(isDigitalPin() )
				digitalWrite( getPin(), LOW );

			return true;
		}

		virtual bool _do_activate()
		{
			if(isDigitalPin() )
				digitalWrite( getPin(), HIGH );

			return true;
		}

		virtual bool _do_deactivate()
		{
			if(isDigitalPin() )
				digitalWrite( getPin(), LOW );

			return true;
		}

		virtual void _do_update() = 0;

};

}

#endif


