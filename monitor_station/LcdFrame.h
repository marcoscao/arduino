#ifndef MS_LCDFRAME_H__
#define MS_LCDFRAME_H__

#include "Timer.h"
#include <EEPROM.h>

namespace ms 
{

class LcdFrame
{
public:
	LcdFrame( int total_frames  = 1) 
	:   _finished(false),
	   _total_frames( total_frames),
		  _curr_frame(0)     
	{
	}

  void setTotalFrames( int total )
  {
    _total_frames = total;
  }
  
	void incFrame()
	{
    if( _finished )
      return;
      
		if( ++_curr_frame >= _total_frames )
		{
			_curr_frame = 0;
      _finished = true;
		}
	}

  bool finished() const
  {
    return _finished;
  }

  void restart() 
  {
    _finished=false;
    _curr_frame=0;
  }
  
	int currentFrame() const
	{
		return _curr_frame;
	}

	int getTotalFrames() const
	{
		return _total_frames;
	}

		
	private:
	  bool _finished;
		int _total_frames;
		int _curr_frame;
};

}

#endif

