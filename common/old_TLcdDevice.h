#ifndef TLCDDEVICE_H__
#define TLCDDEVICE_H__

#include "ILcd.h"
#include "ISensor.h"

static const char * VERSION = "1.2.37";

namespace ms
{

template<typename T_LCD>
class TLcdDevice : public ILcd
{
  public:
   TLcdDevice( int col, int row, T_LCD & lcd, int total_sensors, unsigned long show_t = 3000 )
	: 	ILcd( col, row ),
		_lcd( lcd ),
		_curr_add(0),
		_curr_obj(0),
		_prev_t(0),
		_show_t( show_t ),
		_total( total_sensors ),
		_sensors_list( new ISensor*[ total_sensors ] )
    {
    }

	void setCursor( int col, int line)
	{
		_lcd.setCursor(col,line);
	}

	void print( String & s )
	{
		_lcd.print( s );
	}

	void print( const char * s )
	{
		_lcd.print(s );
	}

	void print( int v)
	{
		_lcd.print( v );
	}

	void print( float v, int i )
	{
		_lcd.print( v, i );
	}


	// int addSensor( ISensor * p )
	// {
	// 	int index = _curr_add;
	// 	_sensors_list[ index ] = p;
   //
	// 	if( ++_curr_add == _total )
	// 		_curr_add--;
   //
	// 	return index;
	// }


	private:

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
			
		_sensors_list[ _curr_obj ]->lcdPrint( static_cast<ms::ILcd&>(*this) ); //_lcd );
	
		return true;
	}

		
   private:
		const int _total; 
     	unsigned long _prev_t;
      unsigned int _curr_obj;
		unsigned long _show_t;
		int _curr_add;
		ISensor** _sensors_list;

      T_LCD & _lcd;
};


}

#endif


