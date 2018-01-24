#ifndef MS_DECORATOR_H__
#define MS_DECORATOR_H__

#include "LcdFrame.h"
#include "ILcd.h"

namespace ms 
{

class Decorator
{
	public:
		Decorator( LcdFrame lcd_frame = LcdFrame(1))
		: _lcd_frame(lcd_frame) 
		{
		}

		virtual void render( int frame ) = 0;


		void setLcd( ILcd * lcd )
		{
			_lcd = lcd;
		}

		ILcd & lcd()
		{
			return *_lcd;
		}

		void setLcdFrame( LcdFrame & lcdframe )
		{
			_lcd_frame = lcdframe;
		}

		LcdFrame & lcdFrame() 
		{
			return _lcd_frame;
		}

		void print( int col, int row, const String & s )
		{	
			_lcd->setCursor( col, row );
			_lcd->print( s );
		}

		void print( int col, int row, const String & s, float v )
		{	
			print( col, row, s );
			_lcd->print( String( v,2) );
		}

	private:
		ILcd * _lcd;
		LcdFrame _lcd_frame;

};

}

#endif

