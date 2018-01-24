#ifndef MS_LCD_I2C2004_H__
#define MS_LCD_I2C2004_H__

 #include "Lcd.h"
// #include "lcdtype_i2c2004.h"

#include "lcdtype_base.h"
#include <LiquidCrystal_I2C.h>

namespace ms
{

	// Specialization for LiquidCrystal_I2C  ( 20x4 )
	
	template<>
	class lcdtype< LiquidCrystal_I2C> : public lcdtype_base< LiquidCrystal_I2C >
	{
	public:
		lcdtype( )
		: lcdtype_base(20,4),
		  _lcd( 0x27,20,4 )
		{
		}

		String name() const 
		{
			return "LCD Device I2C 20x4";
		}

		LiquidCrystal_I2C & getLcd()
		{
			return _lcd;
		}

		bool initialize( )
		{
	  		_lcd.init();
	 		_lcd.backlight();

	 		_lcd.begin(20,4, LCD_5x10DOTS);
	  		_lcd.setContrast( 40 );
       	_lcd.clear();
	  		// _lcd.setCursor(3,0);
	  		// _lcd.print("Monitor Station");
	  		// _lcd.setCursor(2,1);
	  		// _lcd.print( VERSION_2 );
			// _lcd.setCursor(0,2);
	  		// _lcd.print("(c) Copyright 2017");
			// _lcd.setCursor(2,3);
	  		// _lcd.print("Coded by mscao!");

      	return true;
		}

	private:
		LiquidCrystal_I2C _lcd;
	};


	//
	// Typedef
	//
	typedef Lcd<LiquidCrystal_I2C> Lcd_I2C2004;

}


#endif

