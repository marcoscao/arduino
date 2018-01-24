#ifndef BLINKLED_H__
#define BLINKLED_H__

#include "ILed.h"

namespace ms 
{

class BlinkLed : public ILed
{
	public:
		BlinkLed(int pin, unsigned long blink_t = 300 )
		: 	ILed(pin),
	  		_prev_t(0),
  	  		_blink_t(blink_t),
	  		_blinking_on(false),
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
		unsigned long _blink_t;
		bool _blinking_on;
		bool _blink;

		void _do_update()
		{
			if( not _blink )
				return;

			if( not _blinking_on )
			{
				activate();
				_blinking_on = true;
			}

			unsigned long curr_t = millis();

			if( not _prev_t )
				_prev_t = curr_t;

			if( _blinking_on && ( curr_t - _prev_t ) > _blink_t )
			{
				deactivate();
				_blinking_on=false;
				_blink=false;
				_prev_t =0;
			}

		}


};

}

#endif


