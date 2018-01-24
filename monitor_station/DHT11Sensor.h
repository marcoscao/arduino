/**
 * DHT11 Temperature and Humidity Sensor
 *
 */

#ifndef MS_DHT11SENSOR_H__
#define MS_DHT11SENSOR_H__

#include "Sensor.h"
#include "sensor_values.h"
//#include "File.h"
#include "MicroSD.h"
//#include "ILcd.h"
#include <DHT.h>
#include <DHT_U.h>

#include <Time.h>

namespace ms
{

class DHT11Sensor : public Sensor
{
public:
   // enum RecordMode
   // {
   //    RM_UNKNOW = 0,
   //    RM_EACH_CHANGE = 2,  
   //    RM_MAXMIN = 4,
   //    RM_ALERTS = 8,
   //    RM_INTERVAL = 16
   // };

	DHT11Sensor( int pin )
	: 	Sensor( pin, Timer(100), Timer(1000) ),
  		_read_err(0),	
		_temp_values( 6.0, 50.0 ),
		_hum_values( 5.0, 95.0 ),
    // _old_temp_values( _temp_values ),
    // _old_hum_values( _hum_values ),     
		_dht11( pin, DHT11 ),
    _output_fname("dht11.txt"),
    // _record_mode( RM_UNKNOW ),
    // _is_recording(false),
    // _record_secs_interval(300)
	 // _render( *this )
		{
			_dht11.begin();
		}

		String name() const
		{
			return "DHT11 Sensor";
		}

    // void setFileName( const String & fname )
    // {
    //   _output_fname = fname;
    // }

    // void setRecordMode( bool onoff, enum RecordMode rm = RM_INTERVAL, int rec_secs_interval = 600, int rec_nseq = 3)
    // {
    //   _record_mode = rm;
    //   _record_secs_interval = rec_secs_interval;
    //   _record_nseq = rec_nseq;
    // }
    //
    // DHT11Sensor::RecordMode recordMode()
    // {
    //   return _record_mode;
    // }
    
    
	sensor_values temperature() const
	{
		return _temp_values;
	}

	sensor_values humidity() const
	{
		return _hum_values;
	}

	
		// void render( int frame )
		// {
		// 	RENDER_DECORATOR::render( *this, frame );
		// }
      //

	private:
    //static const String OUTPUT_FNAME;
    // bool _new_temp_values;
    // bool _new_hum_values;
    // bool _is_recording;
    // RecordMode _record_mode;
    // int _record_secs_interval;
    // int _record_nseq;
    
	int _read_err;
    sensor_values _temp_values;
    sensor_values _hum_values;
    // sensor_values _old_temp_values;
    // sensor_values _old_hum_values;
    
	DHT _dht11;
    // String _output_fname;


    bool _do_initialize() 
    {
      // if( getLcd() && getLcd()->rows() > 3 )
      //   lcdFrame().setTotalFrames( 4 );
      //  else
      //   lcdFrame().setTotalFrames( 6 );
      //
      return true;
    }

    bool _do_activate()
    {
      File f;
      if( not MicroSD::get().existsFile( _output_fname ) )
      {       
			MicroSD::get().createFile( _output_fname, f );
        f.println( "DHT11 Sensor Values" );       
      }
      else
      {
			MicroSD::get().createFile( _output_fname, f );
        f.println( "......................................................................................." );       
        f.println( "......................................................................................." );       
        f.println(" ");
        LOG( "DHT11", "File exists");
      }

       f.close();
      
        LOG("DHT11","Creating file");
    }


		void _do_update()
   	{   
        	_temp_values.setCurrentValue( _dht11.readTemperature() );           
			_hum_values.setCurrentValue( _dht11.readHumidity() );
        
         if( isnan(_temp_values.current) )
          _temp_values.setCurrentValue( 0.0 );

			if( not _temp_values.hasChanges() && not _hum_values.hasChanges() )
				return;

        	File f;
        	MicroSD::get().openFile( _output_fname, f );    

			if( _temp_values.hasChanges() )
			{
        		String s ( ms::Log::get().dateTimeStr() + " Temperature: " + String( _temp_values.curr ) );
				f.println( s );
        		LOG( "DHT11", s );
			}

			if( _hum_values.hasChanges() )
			{
        		String s ( ms::Log::get().dateTimeStr() + " Temperature: " + String( _temp_values.curr ) );
				f.println( s );
        		LOG( "DHT11", s );
			}

      	f.close();		
   	}

		void _do_debug_print() const
		{
        LOG( "DHT11::_do_debug_print" );
		  
        Serial.print( "  T: " );
        Serial.print( static_cast<float>(_temp_values.current), 2 );
        Serial.print( "  H: " );
        Serial.print( static_cast<float>( _hum_values.current), 2 );
        Serial.print( "  Read-Error: " );
        Serial.print( _read_err );
		}

		// void _do_lcd_print( )
		// { 
		// 	Sensor::_do_lcd_print( );
		// 	
		// 	switch( lcdFrame().currentFrame() )
		// 	{
		// 		case 0 : _print1( "Temperatur: ", _temp_values.curr ); break;
		// 		case 1 : _print1( "Temp_HI: ", _temp_values.hist_max ); break;
		// 		case 2 : _print1( "Temp_LO: ", _temp_values.hist_min ); break;
		// 		case 3 : _print1( "Humidity: ",  _hum_values.curr ); break;
		// 		case 4 : _print1( "Hum_HI: ", _hum_values.hist_max ); break;
		// 		case 5 : _print1( "Hum_LO: ", _hum_values.hist_min ); break;
		// 	}
		// }
		
		// void _do_lcd_print_20x4( )
		// { 
      // bool new_values = false;
      //
      // if( lcdFrame().currentFrame() == 0 && _old_temp_values != _temp_values )
      // {
      //   new_values=true;
      //   File f;
      //   getMicroSD()->openFile( _output_fname, f );    
      //   //_output_file = SD.open("dht11_sensor.log");
      //   String s ( ms::Log::get().dateTimeStr() + " Temperature: " + String( _temp_values.curr ) );
      //   f.println( s );
      //   LOG( "DHT11", s );
      //   //f.println( "Temperature Hist MIN: " + String( _temp_values.hist_min ) ); 
      //   
      //   //f.println( "Temperature: " + String( _temp_values.curr ) ); //String( "Temperature: " + String( _temp_values.curr ) ) );
      //   //f.println( "Temperature Hist MIN: " + String( _temp_values.hist_min ) ); 
      //   //f.println( "Temperature Hist MAX: " + String( _temp_values.hist_max ) ); 
      //   f.close();
      // }
      //
      // if( lcdFrame().currentFrame() == 1 && _old_hum_values != _hum_values )
      // {
      //   new_values=true;
      //   File f;
      //   getMicroSD()->openFile( _output_fname, f );
      //   
      //   String s ( ms::Log::get().dateTimeStr() + " Humidity: " + String( _hum_values.curr ) );
      //   f.println( s );
      //   LOG( "DHT11", s );
      //   //_output_file = SD.open("dht11_sensor.log");
      //   //f.println( "Humidity: " );
      //   //f.println( _hum_values.curr );
      //   f.close();
      // }
      //
      //  if(new_values)
      //  {
      //     if( hasFlashLed() )
      //       getFlashLed()->sendFlash(); 
      //
      //     getLcd()->clear();
      //     
      //     _old_temp_values = _temp_values;
      //     _old_hum_values = _hum_values;
      // }       
     
			// Sensor::_do_lcd_print_20x4( );      
        //
			// switch( lcdFrame().currentFrame() )
			// {
			// 	case 0 :            
			// 		_print2( "Temperatura: ", _temp_values.curr, "MAX: ", _temp_values.hist_max );								 
			// 		break;
        //
        // case 1 :            
        //   _print2( "Temperatura: ", _temp_values.curr, "MIN: ", _temp_values.hist_min );
        //   break;
        //
			// 	case 2 :
			// 		_print2( "Humedad: ", _hum_values.curr, "MAX: ", _hum_values.hist_max );								 
			// 		break;
        //
        // case 3 :
        //   _print2( "Humedad: ", _hum_values.curr, "MIN: ", _hum_values.hist_min );
        //   break;
        //
			// 	}
		// }

		// void _print1( const String & t, float v )
		// {	
		// 	getLcd()->print( t );
		// 	getLcd()->print( String( v,2) );
		// }
    //
    // void _print2( const String & t1, float v1,
    //               const String & t2, float v2 )                
    // {
    //   getLcd()->setCursor(0, 2 );
    //   _print1( t1, v1 );
    //
    //   getLcd()->setCursor(0, 3);
    //   _print1( t2, v2 );
    // }
    //
		// void _print3( const String & t1, float v1,
		// 			        const String & t2, float v2,
		// 			        const String & t3, float v3 )
		// {
		// 	_print1( t1, v1 );
    //
		// 	getLcd()->setCursor(0,2);
		// 	_print1( t2, v2 );
    //
		// 	getLcd()->setCursor(0,3);
		// 	_print1( t3, v3 );
		// }
};






//
//class DHT11_Decorator20x4 : public Renderable
//{
//	public:
//		DHT11_Decorator20x4( DHT11Sensor & dht11 )
//		: _dht11( dht11 )
//		 {
//		 }
//
//		void render( int frame f )
//		{
//			print( 0, 0, _dht11.name() );
//
//			if( f == 0 || f == 1 )
//				print( 0, 2, "Temperatura: ", _dht11.temperature().current );
//			else
//				print( 0, 2, "Humedad: ", _dht11.humidity().current );
//
//			switch( f )
//			{
//				case 0 : print( 0, 3, "MAX: ", _dht11.temperature().max() ); break;
//				case 1 : print( 0, 3, "MIN: ", _dht11.temperature().min() ); break;
//				case 2 : print( 0, 3, "MAX: ", _dht11.humidity().hist_max ); break;
//				case 3 : print( 0, 3, "MIN: ", _dht11.humidity().min() ); break;
//			}					
//		}
//
//	private:
//		 DHT11Sensor & _dht11;
//};
//


} // end namespace

#endif


