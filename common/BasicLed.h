#ifndef BASICLED_H__
#define BASICLED_H__

#include "ILed.h"

namespace ms 
{

class BasicLed : public ILed
{
  public:
	BasicLed(int pin, int blink_t = 500 )
	: ILed(pin)
	{
	}

  private:
	String name() const 
	{
		return "Basic LED";
	}


	virtual void _do_update()
	{

	}


};

}

#endif


