
/**
 * RTC_DS1302 Real Time Clock
 *
 */

#ifndef MS_RTCDS1302_H__
#define MS_RTCDS1302_H__

#include "Sensor.h"
//#include "ILcd.h"
//#include <DS1307RTC.h>
#include <DS1302RTC.h>

#include <Time.h>
#include <TimeLib.h>

namespace ms
{

class RTC_DS1302 : public Sensor
{
public:

	RTC_DS1302( int ce_pin, int io_pin, int scl_pin )
	: 	Sensor( ce_pin, Timer(100), Timer(1000) ),
		_ds1302( ce_pin, io_pin, scl_pin )
		{
		}

		String name() const
		{
			return "RTC DS1302";
		}
    
		String time() const
		{
			time_t t = _ds1302.get();
			char buf[50];
      
      snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
            year(t), month(t), day(t),
     			 hour(t), minute(t), second(t) );

			String s( buf );

			return s;
		}

    String dateStr() const
    {
      time_t t = _ds1302.get();
      char buf[50];
      
      snprintf(buf, sizeof(buf), "%04d-%02d-%02d", year(t), month(t), day(t) );           
      String s( buf );
      return buf;
    }

    String timeStr() const
    {
      time_t t = _ds1302.get();
      char buf[50];

      snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hour(t), minute(t), second(t) );      
      String s( buf );
      return buf;
    }

	private:
		DS1302RTC _ds1302;
    

    bool _do_initialize() 
    {
      // if( getLcd() && getLcd()->rows() > 3 )
      //   lcdFrame().setTotalFrames( 2 );
      //  else
      //   lcdFrame().setTotalFrames( 6 );
      //

//    if( getLcd() && getLcd()->rows() > 3 )
//        lcdFrame().setTotalFrames( 2 );
//       else
//        lcdFrame().setTotalFrames( 2 );

		  _ds1302.writeEN();
  		_ds1302.haltRTC();

//    typedef struct  { 
//      uint8_t Second; 
//      uint8_t Minute; 
//      uint8_t Hour; 
//      uint8_t Wday;   // day of week, sunday is day 1
//      uint8_t Day;
//      uint8_t Month; 
//      uint8_t Year;   // offset from 1970; 
//    }   tmElements_t, TimeElements, *tmElementsPtr_t;


    // Adjust date-time first time
    tmElements_t t{ 0,15,11,7,27,5,47 };
    time_t t_now = makeTime( t );
    
  	// Set the time and date on the chip.
  	//_ds1302.set(t_now);
      
      return true;
    }

    bool _do_activate()
    {
    }


		void _do_update()
   	{   

   	}

		void _do_debug_print() const
		{
        LOG( "DS1302::_do_debug_print" );
		  
		  Serial.print( time() );
		}

//		void _do_lcd_print( )
//		{ 
//			Sensor::_do_lcd_print( );
//			_print1( "Hora: ", time() ); 
//		}
//		
//		void _do_lcd_print_20x4( )
//		{ 			
//			//getLcd()->clear();
//      Sensor::_do_lcd_print_20x4( );      
//      
//      getLcd()->setCursor(0,2);
//      _print1( "Hora : ", timeStr() ); 
//
//      getLcd()->setCursor(0,3);
//			_print1( "Fecha: ", dateStr() );      
//		}
//
//		void _print1( const String & t, const String & s )
//		{	
//			getLcd()->print( t );
//			getLcd()->print( s );
//		}

};


} // end namespace

#endif


