#include "Saver.h"
#include "MicroSD.h"

#include <Time.h>

namespace ms
{

	Saver::Saver( )
	: 	_output_fname("unknow_recorder.txt"),
    	_record_mode( RM_UNKNOW ),
    	_is_recording(false),
    	_record_secs_interval(300),
		_msd(0)
	{
	}
		void Saver::setMicroSd( ms::MicroSD * msd )
		{
			_msd = msd;
		}

		MicroSD & Saver::msd()
		{
			return *_msd;
		}

    void Saver::setFileName( const String & fname )
    {
      _output_fname = fname;
    }

    void Saver::setRecordMode( bool onoff, enum RecordMode rm = RM_INTERVAL, int rec_secs_interval = 600, int rec_nseq = 3)
    {
      _record_mode = rm;
      _record_secs_interval = rec_secs_interval;
      _record_nseq = rec_nseq;
    }

    Saver::RecordMode Saver::recordMode()
    {
      return _record_mode;
    }
    
	bool Saver::write( const String & s )
	{
   	File f;
		MiroSD::get().openFile( _output_fname );
		f.println( s );
		LOG( _output_fname, s );
		f.close();
	}
		

} // end namespace



