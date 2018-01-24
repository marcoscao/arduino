#ifndef MS_SENSOR_H__
#define MS_SENSOR_H__

//#include "IDevice.h"
// #include "ILcd.h"
// #include "LcdFrame.h"
#include "Timer.h"
#include "FlashLed.h"
// #include "MicroSD.h"
#include <EEPROM.h>

namespace ms 
{

class Sensor : public IDevice
{
	// typedef void (Sensor::*LcdPrintFn)(void);

	public:
		Sensor(	int pin, 
					Timer wait_ready_timer=Timer( 300 ), 
					Timer update_timer=Timer( 1200 ) )
			   	// LcdFrame lcd_frame=LcdFrame( 1 ) )	
		: 	IDevice( pin, INPUT, wait_ready_timer, update_timer ), 
			_blink_led(0)
			// _lcd_frame( lcd_frame),
			// _lcd_print_fn(0),
     // _microsd(0)
		{
		}

		~Sensor()
		{
			 if( _blink_led )
				 _blink_led->uninitialize();
		}

		// void setLcd( ILcd * lcd )
		// {
		// 	if( not lcd )
		// 	{
		// 		_lcd = 0;
		// 		_lcd_print_fn = 0;
      //
      //   		return;
		// 	}
      //
		// 	_lcd = lcd;
      //
		// 	if( _lcd->rows() > 3 )
		// 		_lcd_print_fn = &Sensor::_do_lcd_print_20x4;
		// 	else
		// 		_lcd_print_fn = &Sensor::_do_lcd_print;
		// }

    	// ILcd * getLcd()
    	// {
      // 	return _lcd;
    	// }
    
		// LcdFrame & lcdFrame() 
		// {
		// 	return _lcd_frame;
		// }
      //

		// void lcdPrint(  )
		// {
      // //if( not updateTimer().isTime() )
      //  // return;
      //   
		// 	//if( not _lcd_frame.incFrame() )
		// 	//	return;
      // //_lcd_frame.incFrame();
      //
		// 	if( _lcd_print_fn )
      // 	{
		// 		(*this.*_lcd_print_fn)();
      // 	}
		// }

		void setFlashLed( FlashLed * p )
		{
			// if( _blink_led )
				// _blink_led->uninitialize();

			 _blink_led = p;
			 //_blink_led->initialize();
		}

		bool hasFlashLed() const
		{
			return _blink_led;
		}

		FlashLed * getFlashLed()
		{
			return _blink_led;
		}

    // void setMicroSD( MicroSD * p )
    // {
    //   _microsd = p;
    // }

    // bool hasMicroSD()
    // {
    //   return _microsd != 0;
    // }
    //
    // MicroSD * getMicroSD()
    // {
    //   return _microsd;
    // }
    //
    
    
	private:
		// LcdFrame _lcd_frame;
		// LcdPrintFn _lcd_print_fn;
		// ILcd * _lcd;
    FlashLed* _blink_led;
    // MicroSD * _microsd;
    

	protected:

		virtual bool _do_uninitialize() 
		{
			return true;
		}

		virtual bool _do_activate()
		{
			return true;
		}

		virtual bool _do_deactivate()
		{
			return true;
		}

		// virtual void _do_lcd_print( )
		// {        
		// 	 // lcd.clear();
		// 	 _lcd->setCursor(0, 0);
		// 	 _lcd->print( name() );
		// 	 _lcd->setCursor(0, 1);
		// }
      //
		// virtual void _do_lcd_print_20x4( )
		// {  
		// 	// lcd.clear();
		// 	_lcd->setCursor(0, 0);
		// 	_lcd->print( name() );
      //
		// 	_lcd->setCursor(0, 1);
		// }
      //
	};

}

#endif

