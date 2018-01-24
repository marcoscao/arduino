#ifndef MS_LCDTYPE_I2C1602_H__
#define MS_LCDTYPE_I2C1602_H__

#include "lcdtype_base.h"

namespace ms
{
	
	template<>
	class lcdtype< LiquidCrystal> : public lcdtype_base< LiquidCrystal >
	{
	public:
		lcdtype( )
		: 	_lcd( 12, 11, 5, 4, 3, 2 )
		{
		}

		String name() const 
		{
			return "LCD Device 16x2";
		}

		LiquidCrystal & getLcd()
		{
			return _lcd;
		}

		bool initialize( )
		{
			_lcd.clear();
       	_lcd.begin(16, 2);
       	_lcd.setCursor(0, 0);

       	return true;
		}


	private:
		LiquidCrystal _lcd;

	};


}

#endif


