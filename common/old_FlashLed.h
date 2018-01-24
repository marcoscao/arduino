#ifndef BLINKLED_H__
#define BLINKLED_H__

#include "ILed.h"

namespace ms 
{

class BlinkLed : public ILed
{
	public:
		BlinkLed(int pin, unsigned long blink_on_t = 300, unsigned long blink_off_t = 1500 )
		: 	ILed(pin),
	  		_prev_t(0),
  	  		_blink_on_t(blink_on_t),
  	  		_blink_off_t(blink_off_t),
	  		_blinking_on(false),
	  		_blinking_off(false),
			_blink(false)
		{
		}

		String name() const 
		{
			return "Blink LED";
		}

		void blink()
		{
			_blink = true;
		}

	private:
		unsigned long _prev_t;
		unsigned long _blink_on_t;
		unsigned long _blink_off_t;
		bool _blinking_on;
		bool _blinking_off;
		bool _blink;

		void _do_update()
		{
			if( not _blink )
				return;

			if( not _blinking_on && not _blinking_off )
			{
				activate();
				_blinking_on = true;
			}

			unsigned long curr_t = millis();

			if( not _prev_t )
				_prev_t = curr_t;

			if( _blinking_on && ( curr_t - _prev_t ) > _blink_on_t )
			{
				deactivate();
				_prev_t = curr_t;
				_blinking_off = true;
				_blinking_on=false;
			}

			if( _blinking_off && ( curr_t - _prev_t ) > _blink_off_t )
			{
				_prev_t = 0;
				_blinking_off = false;
				_blinking_on = false;
				_blink = false;
			}

		}


};

}

#endif


