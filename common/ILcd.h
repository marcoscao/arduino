#ifndef MS_ILCD_H__
#define MS_ILCD_H__

#include "IDevice.h"
#include "Timer.h"

class String;

namespace ms
{
	class ILcd : public IDevice 
	{
	public:
		ILcd( const Timer & wait_ready_timer, const Timer & update_timer ) 
		: IDevice( -1, OUTPUT, wait_ready_timer, update_timer )
		{
		}

		ILcd & getLcd() { return *this; }

		virtual void setCursor( int col, int line) = 0;
    
		virtual void print( const String & ) = 0;
    
		virtual void clear() = 0;
	 
	 	virtual int rows() const = 0;
    
    	virtual int cols() const = 0;
	};

}

#endif


