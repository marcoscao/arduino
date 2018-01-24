#ifndef LCDI2C20x4DEVICE_H__
#define LCDI2C20x4DEVICE_H__

#include "ILcd.h"
#include "ISensor.h"
#include <LiquidCrystal_I2C.h>

static const char * VERSION_2 = "1.2.31";

namespace ms
{

class LcdI2C20x4Device : public ILcd
{
  public:
   LcdI2C20x4Device( int total_sensors, unsigned long show_t = 3000 )
	: 	_lcd( 0x27,20,4 ),
		_curr_add(0),
		_curr_obj(0),
		_prev_t(0),
		_show_t( show_t ),
		_total( total_sensors ),
		_sensors_list( new ISensor*[ total_sensors ] )
    {
    }

	const char * name() const 
	{
		return "LCD I2C 20x4 Device";
	}

	void setCursor( int col, int line)
	{
		_lcd.setCursor(col,line);
	}

	void print( const char * s )
	{
		_lcd.print(s );
	}

	void print( int v)
	{
		_lcd.print( v );
	}

	void print( float v)
	{
		_lcd.print( v );
	}

	int addSensor( ISensor * p )
	{
		int index = _curr_add;
		_sensors_list[ index ] = p;

		if( ++_curr_add == _total )
			_curr_add--;

		return index;
	}


	private:

	virtual bool _do_initialize( )
	{
	  	_lcd.init();
	 	_lcd.backlight();

	 	_lcd.begin(20,4, LCD_5x10DOTS);
	  	_lcd.setContrast( 40 );
	  	_lcd.setCursor(3,0);
	  	_lcd.print("Monitor Station");
	  	_lcd.setCursor(2,1);
	  	_lcd.print( VERSION_2 );
		_lcd.setCursor(0,2);
	  	_lcd.print("(c) Copyright 2017");
		_lcd.setCursor(2,3);
	  	_lcd.print("Coded by mscao!");
	
		 return true;
	}

	virtual bool _do_uninitialize( )
	{
		return true;
	}

	virtual void _do_update( )
	{
		unsigned long curr_t = millis();

		if( not _prev_t )
			_prev_t = curr_t;

		if( (curr_t - _prev_t) > _show_t )
		{
			if( _sensors_list[_curr_obj]->incrementLcdStep() )
			{
				_lcd.clear();
				_prev_t=0;
			}
			else
			{
				while( ++_curr_obj < _total	 )
				{
					if( _sensors_list[ _curr_obj ]->isEnable() )
						break;
				}

				_lcd.clear();
				_prev_t=0;
			}
		}
		
		if( _curr_obj >= _total )
		{	
			_curr_obj = 0;
			return;
		}
			
		_sensors_list[ _curr_obj ]->lcdPrint( *this ); //_lcd );
	
		return true;
	}

		
   private:
		const int _total; 
     	unsigned long _prev_t;
      unsigned int _curr_obj;
		unsigned long _show_t;
		int _curr_add;
		ISensor** _sensors_list;

      //LiquidCrystal _lcd;
		LiquidCrystal_I2C _lcd;
};

}

#endif


