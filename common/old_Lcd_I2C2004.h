#ifndef LCDDEVICE_I2C2004_H__
#define LCDDEVICE_I2C2004_H__

// #include "TLcdDevice.h"
// #include "ISensor.h"
#include "lcdtype"
#include <LiquidCrystal_I2C.h>

namespace ms
{
	template<>
	class lcdtype< LiquidCrystal_I2C >
	{
		friend class Lcd;

	public:
		const char * name() const 
		{
			return "LCD I2C_204 Device";
		}
		
		int rows() const {  return 4; }
		int cols() const { return 20; }

	private:
		LiquidCrystal_I2C _lcd;

		lcdtype()
			: _lcd( 0x27, 20, 4 )
		{
		}

		void _initialize( )
		{
			_lcd.init();
			_lcd.backlight();

			_lcd.begin(20,4, LCD_5x10DOTS);
			_lcd.setContrast( 40 );
			// _lcd.setCursor(0,1);
			// _lcd.print("Monitor Station  ");
			// _lcd.print( VERSION );
			// _lcd.setCursor(0,2);
			// _lcd.print("(c) 2017 ");
			// _lcd.print("Coded by mscao!");
		}

	};

// class LcdDevice_I2C2004 : public TLcdDevice< LiquidCrystal_I2C>
// {
//   public:
//    LcdDevice_I2C2004( int total_sensors, unsigned long show_t = 3000 )
// 	: 	TLcdDevice( 20, 4, _lcd, total_sensors, show_t ),
// 		_lcd( 0x27,20,4 )
//     {
//     }
//
// 	const char * name() const 
// 	{
// 		return "LCD I2C_204 Device";
// 	}
//
// 	private:
// 		LiquidCrystal_I2C _lcd;
//
// 		virtual bool _do_initialize( )
// 		{
// 			_lcd.init();
// 			_lcd.backlight();
//
// 			_lcd.begin(20,4, LCD_5x10DOTS);
// 			_lcd.setContrast( 40 );
// 			_lcd.setCursor(0,1);
// 			_lcd.print("Monitor Station  ");
// 			_lcd.print( VERSION );
// 			_lcd.setCursor(0,2);
// 			_lcd.print("(c) 2017 ");
// 			_lcd.print("Coded by mscao!");
// 		
// 			 return true;
// 		}
//
// 		virtual bool _do_uninitialize( )
// 		{
// 			return true;
// 		}
// 			
// };
//
//
}

#endif


