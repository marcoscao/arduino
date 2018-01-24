/**
 * DHT11 Temperature and Humidity Sensor
 *
 */

#ifndef MS_DHT11SENSOR_H__
#define MS_DHT11SENSOR_H__

#include "Sensor.h"
//#include "ILcd.h"
#include <DHT.h>
#include <DHT_U.h>

#include <Time.h>

namespace ms
{
  struct sensor_value
  {
    float curr;
    float hist_min;
    float hist_max;
    float low_alert;
    float high_alert;

    bool is_low_alert;
    bool is_high_alert;

    sensor_value( float a_low_alert, float a_high_alert )
    : is_low_alert(false),
      is_high_alert(false),
      curr(0.0),
      hist_min( 99999.0),
      hist_max( -99999.0 ),
      low_alert( a_low_alert ),
      high_alert( a_high_alert )
      {
        
      }

    void setCurrentValue( float v )
    {
      curr = v;
      adjustValues();
    }
    
    void adjustValues()
    {       
        if( curr <= hist_min )
          hist_min = curr;

        if( curr >= hist_max )
           hist_max = curr;

        is_low_alert = hist_min < low_alert;
        is_high_alert = hist_max > high_alert;
    }

    bool operator!=( const sensor_value & r ) const
    {
      return curr != r.curr || hist_min != r.hist_min || hist_max != r.hist_max
        || low_alert != r.low_alert || high_alert != r.high_alert 
        || is_low_alert != r.is_low_alert || is_high_alert != r.is_high_alert; 
    }
  };


class DHT11Sensor : public Sensor
{
public:
   enum RecordMode
   {
      RM_UNKNOW = 0,
      RM_EACH_CHANGE = 2,  
      RM_MAXMIN = 4,
      RM_ALERTS = 8,
      RM_INTERVAL = 16
   };

	DHT11Sensor( int pin )
	: 	Sensor( pin, Timer(100), Timer(1000) ),
  		_read_err(0),	
		_temp_values( 6.0, 50.0 ),
		_hum_values( 5.0, 95.0 ),
    _old_temp_values( _temp_values ),
    _old_hum_values( _hum_values ),     
		_dht11( pin, DHT11 ),
    _output_fname("dht11.txt"),
    _record_mode( RM_UNKNOW ),
    _is_recording(false),
    _record_secs_interval(300)
		{
			_dht11.begin();
		}

		String name() const
		{
			return "DHT11 Sensor";
		}

    void setFileName( const String & fname )
    {
      _output_fname = fname;
    }

    void setRecordMode( bool onoff, enum RecordMode rm = RM_INTERVAL, int rec_secs_interval = 600, int rec_nseq = 3)
    {
      _record_mode = rm;
      _record_secs_interval = rec_secs_interval;
      _record_nseq = rec_nseq;
    }

    DHT11Sensor::RecordMode recordMode()
    {
      return _record_mode;
    }
    
    
		float temperature() const
		{
			return _temp_values.curr;
		}

		float humidity() const
		{
			return _hum_values.curr;
		}


	private:
    //static const String OUTPUT_FNAME;
    bool _new_temp_values;
    bool _new_hum_values;
    bool _is_recording;
    RecordMode _record_mode;
    int _record_secs_interval;
    int _record_nseq;
    
		int _read_err;
    sensor_value _temp_values;
    sensor_value _hum_values;
    sensor_value _old_temp_values;
    sensor_value _old_hum_values;
    
		DHT _dht11;
    String _output_fname;
    

    bool _do_initialize() 
    {
      if( getLcd() && getLcd()->rows() > 3 )
        lcdFrame().setTotalFrames( 4 );
       else
        lcdFrame().setTotalFrames( 6 );

      return true;
    }

    bool _do_activate()
    {
      File f;
      if( not getMicroSD()->existsFile( _output_fname ) )
      {       
        getMicroSD()->createFile( _output_fname, f );
        f.println( "DHT11 Sensor Values" );       
      }
      else
      {
        getMicroSD()->createFile( _output_fname, f );
        f.println( "......................................................................................." );       
        f.println( "......................................................................................." );       
        f.println(" ");
        LOG( "DHT11", "File exists");
      }

       f.close();
      
      //if( getMicroSD() )
      //{
        LOG("DHT11","Creating file");
        //_output_file = SD.open( "dht11sensor.log", FILE_WRITE );
        //if( _output_file )
          //_output_file.println( "prueba" );
        //_output_file.close();
        
        //if( _output_file ) {
         // _output_file.println( "xxxxxxxx" );
         // _output_file.close();
        //}
        
     // }
    }


		void _do_update()
   	{   
        _temp_values.setCurrentValue( _dht11.readTemperature() );           
				_hum_values.setCurrentValue( _dht11.readHumidity() );
        
         if( isnan(_temp_values.curr) )
          _temp_values.setCurrentValue( 0.0 );

//        _new_temp_values = false;
//        _new_hum_values = false;
//                        
//        if( _old_temp_values != _temp_values )
//        {
//          _new_temp_values=true;
//          _old_temp_values = _temp_values;
//          _output_file->println( String( "Temperature: " + String( _temp_values.curr ) ) );
//        }
//
//        if( _old_hum_values != _hum_values )
//        {
//          _new_hum_values=true;
//          _old_hum_values = _hum_values;
//          _output_file->println( String( "Humidity: " + String( _hum_values.curr ) ) );
//        }

   	}

		void _do_debug_print() const
		{
        LOG( "DHT11::_do_debug_print" );
		  
        Serial.print( "  T: " );
        Serial.print( static_cast<float>(_temp_values.curr), 2 );
        Serial.print( "  H: " );
        Serial.print( static_cast<float>( _hum_values.curr), 2 );
        Serial.print( "  Read-Error: " );
        Serial.print( _read_err );
		}

		void _do_lcd_print( )
		{ 
			Sensor::_do_lcd_print( );
			
			switch( lcdFrame().currentFrame() )
			{
				case 0 : _print1( "Temperatur: ", _temp_values.curr ); break;
				case 1 : _print1( "Temp_HI: ", _temp_values.hist_max ); break;
				case 2 : _print1( "Temp_LO: ", _temp_values.hist_min ); break;
				case 3 : _print1( "Humidity: ",  _hum_values.curr ); break;
				case 4 : _print1( "Hum_HI: ", _hum_values.hist_max ); break;
				case 5 : _print1( "Hum_LO: ", _hum_values.hist_min ); break;
			}
		}
		
		void _do_lcd_print_20x4( )
		{ 
      bool new_values = false;
      
      if( lcdFrame().currentFrame() == 0 && _old_temp_values != _temp_values )
      {
        new_values=true;
        File f;
        getMicroSD()->openFile( _output_fname, f );    
        //_output_file = SD.open("dht11_sensor.log");
        String s ( ms::Log::get().dateTimeStr() + " Temperature: " + String( _temp_values.curr ) );
        f.println( s );
        LOG( "DHT11", s );
        //f.println( "Temperature Hist MIN: " + String( _temp_values.hist_min ) ); 
        
        //f.println( "Temperature: " + String( _temp_values.curr ) ); //String( "Temperature: " + String( _temp_values.curr ) ) );
        //f.println( "Temperature Hist MIN: " + String( _temp_values.hist_min ) ); 
        //f.println( "Temperature Hist MAX: " + String( _temp_values.hist_max ) ); 
        f.close();
      }
    
      if( lcdFrame().currentFrame() == 1 && _old_hum_values != _hum_values )
      {
        new_values=true;
        File f;
        getMicroSD()->openFile( _output_fname, f );
        
        String s ( ms::Log::get().dateTimeStr() + " Humidity: " + String( _hum_values.curr ) );
        f.println( s );
        LOG( "DHT11", s );
        //_output_file = SD.open("dht11_sensor.log");
        //f.println( "Humidity: " );
        //f.println( _hum_values.curr );
        f.close();
      }
      
       if(new_values)
       {
          if( hasFlashLed() )
            getFlashLed()->sendFlash(); 
    
          getLcd()->clear();
          
          _old_temp_values = _temp_values;
          _old_hum_values = _hum_values;
      }       
     
			Sensor::_do_lcd_print_20x4( );      
      
			switch( lcdFrame().currentFrame() )
			{
				case 0 :            
					_print2( "Temperatura: ", _temp_values.curr, "MAX: ", _temp_values.hist_max );								 
					break;

        case 1 :            
          _print2( "Temperatura: ", _temp_values.curr, "MIN: ", _temp_values.hist_min );
          break;

				case 2 :
					_print2( "Humedad: ", _hum_values.curr, "MAX: ", _hum_values.hist_max );								 
					break;

        case 3 :
          _print2( "Humedad: ", _hum_values.curr, "MIN: ", _hum_values.hist_min );
          break;

				}
		}

		void _print1( const String & t, float v )
		{	
			getLcd()->print( t );
			getLcd()->print( String( v,2) );
		}

    void _print2( const String & t1, float v1,
                  const String & t2, float v2 )                
    {
      getLcd()->setCursor(0, 2 );
      _print1( t1, v1 );

      getLcd()->setCursor(0, 3);
      _print1( t2, v2 );
    }

		void _print3( const String & t1, float v1,
					        const String & t2, float v2,
					        const String & t3, float v3 )
		{
			_print1( t1, v1 );

			getLcd()->setCursor(0,2);
			_print1( t2, v2 );

			getLcd()->setCursor(0,3);
			_print1( t3, v3 );
		}
};


} // end namespace

#endif


