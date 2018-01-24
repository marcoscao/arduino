/**
 * DHT11 Temperature and Humidity Sensor
 *
 */

#ifndef MS_RECORDER_H__
#define MS_RECORDER_H__

#include "sensor_values.h"
//#include "File.h"
#include "MicroSD.h"
//#include "ILcd.h"
#include <DHT.h>
#include <DHT_U.h>

#include <Time.h>

namespace ms
{

class Saver
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

	Saver( )
	: 	_output_fname("unknow_recorder.txt"),
    	_record_mode( RM_UNKNOW ),
    	_is_recording(false),
    	_record_secs_interval(300)
	{
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

    Saver::RecordMode recordMode()
    {
      return _record_mode;
    }
    
	bool write( const String & s )
	{
   	File f;
		MiroSD::get().openFile( _output_fname );
		f.println( s );
		LOG( _output_fname, s );
		f.close();
	}
		

	private:
    bool _is_recording;
    RecordMode _record_mode;
    int _record_secs_interval;
    int _record_nseq;
    String _output_fname;

};







class DHT11_Saver : public Saver
{
	public:
		DHT11_Saver( DHT11Sensor & dht11 )
		: _dht11( dht11 )
		 {
		 }

		void save( int frame f )
		{
			write( "Temperatura: " );
		}

	private:
		 DHT11Sensor & _dht11;
};


} // end namespace

#endif


