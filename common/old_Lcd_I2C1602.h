#ifndef LCDDEVICE_I2C1602_H__
#define LCDDEVICE_I2C1602_H__

#include "TLcdDevice.h"
#include "ISensor.h"
#include <LiquidCrystal.h>


namespace ms
{

class LcdDevice_I2C1602 : public TLcdDevice< LiquidCrystal>
{
  public:
   LcdDevice_I2C1602( int total_sensors, unsigned long show_t = 3000 )
	: 	TLcdDevice( 16, 4, _lcd, total_sensors, show_t ),
		_lcd( 12, 11, 5, 4, 3, 2 )
    {
    }

	const char * name() const 
	{
		return "LCD I2C 16x02 Device";
	}

	private:

	virtual bool _do_initialize( )
	{
       _lcd.begin(16, 2);
       _lcd.setCursor(0, 0);
       _lcd.print("M-Station");
       _lcd.setCursor(0, 1);
       _lcd.print( VERSION );
	
		 return true;
	}

	virtual bool _do_uninitialize( )
	{
		return true;
	}

		
   private:
      LiquidCrystal _lcd;
};


}

#endif


