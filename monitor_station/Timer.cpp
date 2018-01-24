#include "Timer.h"
#include <Arduino.h>

namespace ms
{
	Timer::Timer( unsigned long total_t, TimerMode tm  )
		: 	_active(false),
			_mode( tm ),
			_total_t(total_t),
			_prev_t(0)
		{
		}

		void Timer::start()
		{
			_active = true;
		}

		void Timer::stop()
		{
			_active = false;
		}

		bool Timer::isTime()
		{
			if( not _active )
				return false;

			unsigned long curr_t = millis();
				
			if( not _prev_t)
				_prev_t = curr_t;

			if( ( curr_t - _prev_t ) > _total_t )
			{
				_prev_t = 0;
			
				if( _mode == TIMER_ONCE )
					_active = false;

				return true;
			}

			return false;
		}

}


