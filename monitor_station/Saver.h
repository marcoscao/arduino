/**
 *
 */

#ifndef MS_SAVER_H__
#define MS_SAVER_H__

//#include "File.h"
// #include "MicroSD.h"
#include <WString.h>
#include <Time.h>

namespace ms
{
class MicroSD;

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

	Saver( );

		void setMicroSd( ms::MicroSD * msd );

		MicroSD & msd();

    void setFileName( const String & fname );

    void setRecordMode( bool onoff, enum RecordMode rm = RM_INTERVAL, int rec_secs_interval = 600, int rec_nseq = 3);

    Saver::RecordMode recordMode();
    
	bool write( const String & s );

    virtual void save() = 0;

	private:
    bool _is_recording;
    RecordMode _record_mode;
    int _record_secs_interval;
    int _record_nseq;
    String _output_fname;
	 ms::MicroSD * _msd;

};


} // end namespace

#endif


