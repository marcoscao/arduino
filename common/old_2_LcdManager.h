#ifndef LCDMANAGER_H__
#define LCDMANAGER_H__

#include "IDevice.h"
#include "IManager.h"
#include <LiquidCrystal.h>

static const char * VERSION = "1.2.27";

namespace ms
{

class LcdManager : public IManager
{
  public:
   LcdManager( IDevice** obj_list, unsigned long * intervals_list, int total )
	: 	IManager( obj_list, total ),
		_lcd( 12, 11, 5, 4, 3, 2 ),
		_curr_obj(0),
		_prev_t(0),
		_intervals_list( intervals_list )
    {
    }

	

	private:

	virtual void _do_initialize( IDevice* p )
	{
       _lcd.begin(16, 2);
       _lcd.setCursor(0, 0);
       _lcd.print("M-Station");
       _lcd.setCursor(0, 1);
       _lcd.print( VERSION );
	}

	virtual void _do_uninitialize( IDevice* p )
	{
	}

	void _do_update( IDevice * /*p*/ )
	{
		unsigned long curr_t = millis();

		if( not _prev_t )
			_prev_t = curr_t;


		if( (curr_t - _prev_t) > _intervals_list[_curr_obj] )
		{
			if( getObject(_curr_obj)->incrementLcdStep() )
			{
				_lcd.clear();
				_prev_t=0;
			}
			else
			{
				while( ++_curr_obj < getTotalObjects()	 )
				{
					if( getObject( _curr_obj )->isEnable() )
						break;
				}

				_lcd.clear();
				_prev_t=0;
			}
		}
		
		if( _curr_obj >= getTotalObjects() )
		{	
			_curr_obj = 0;
			return;
		}
			
		getObject( _curr_obj )->lcdPrint( _lcd );
	}

		
   private:
		unsigned long * _intervals_list;
     	unsigned long _prev_t;
      unsigned int _curr_obj;

      LiquidCrystal _lcd;
};

}

#endif


