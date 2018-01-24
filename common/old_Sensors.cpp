#ifndef ISENSOR_H__
#define ISENSOR_H__

#include "IDevice.h"

namespace ms
{

class ISensor : public IDevice
{
  public:
	 ISensor( int pin )
	 : IDevice( pin )
	 {
	 }

    virtual const char * name() const = 0;

    virtual void update() = 0;

    virtual void printSerial() const = 0;

    // virtual void printLCD( LiquidCrystal & lcd ) = 0;

};

}

#endif
