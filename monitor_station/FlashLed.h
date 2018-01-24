#ifndef MS_FLASHLED_H__
#define MS_FLASHLED_H__

#include "ILed.h"
#include "Timer.h"

namespace ms 
{
	class FlashLed : public ILed
	{
	public:
		FlashLed( int pin, const Timer & flash_time = Timer( 500, Timer::TIMER_ONCE ) )
		: 	ILed(pin, Timer( 50, Timer::TIMER_ONCE), flash_time )
		{
		}

		String name() const 
		{
			return "Flash LED";
		}

		void sendFlash()
		{
			activate();
			updateTimer().start();
		}



	private:

		void _do_update()
		{
			// if( not _flash_timer.isTime() )
				// return;

			deactivate();
		}

	};

}

#endif


