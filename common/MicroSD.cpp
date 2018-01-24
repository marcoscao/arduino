#include "MicroSD.h"
#include "Saver.h"
#include "Timer.h"
#include "File.h"
#include <WString.h>


namespace ms
{
	MicroSD::MicroSD( 	int cs_pin, int total_devices, 
				const Timer & wait_ready_timer=Timer(50), 
				const Timer & update_timer=Timer(120),
				const Timer & frame_timer=Timer(250) )
	: 	IDevice( cs_pin, OUTPUT, wait_ready_timer, update_timer ),
      	_curr_device(0),
      	_curr_add(0),
			_total_devices( total_devices ),
			_devices_list( new Saver*[ total_devices ] ),
      	_frame_timer( frame_timer )
	 {
	}

	int MicroSD::addDevice( ms::Saver * p )
	{
			int index = _curr_add;
			_devices_list[ index ] = p;

			if( ++_curr_add == _total_devices )
				_curr_add--;

			p->setMicroSd( static_cast<ms::ILcd*>( this ) );
			return index;
	}

   String MicroSD::name() const
    	{
      	return "MicroSD";
    	}

    	bool MicroSD::_do_initialize() 
    	{
      LOG( "MicroSD", "initializing card...");
      // pinMode( cs_pin, OUTPUT);
      digitalWrite( getPin(), HIGH);

      if ( not SD.begin( getPin() ) )
      {
        LOG( "MicroSD", "card initialization failed");
        return false;
      }

      LOG( "MicroSD", "card ready to be used");
      return true;
    	}
    
    	bool MicroSD::_do_uninitialize() 
    	{
      	return true; //_lcd->uninitialize();
    	}

    	bool MicroSD::_do_activate() 
    	{
        _frame_timer.start();
      	return true; //_lcd->activate();
    	}

    	bool MicroSD::_do_deactivate() 
    	{
      	return true; //_lcd->deactivate();
    	}

    bool MicroSD::existsFile( const String & fname )
    {
      bool r = false;
      File f;
      
      f = SD.open( fname, FILE_READ );
      if( f )
        r = true;

      f.close();
      
      return r;
    }
    

    bool MicroSD::createFile( const String & fname, File & f )
    {
        f = SD.open( fname, FILE_WRITE );
        if( not f )
        {
          LOG( "MicroSD", "error creating file", fname );
          return false;
        }

        LOG( "MicroSD","created file", fname );
      
        return true;
    }

    bool MicroSD::openFile( const String & fname, File & f )
    {
      f = SD.open(fname, FILE_WRITE);
      if( not f )
      {
        LOG( "MicroSD", "error opening file", fname );
        return false;
      }

      LOG( "MicroSD", "opened file", fname );
      return true;
    }
    

    bool MicroSD::createDir( const String & dname )
    {

      return false;
    }


	void MicroSD::_do_update( )
	{
		// LcdFrame & dev_frame = _devices_list[ _curr_device ]->lcdFrame();
		
    	// time to pass to a new frame during lcd refresh?? then increment frame of device
    	if( _frame_timer.isTime() )
    	{
		  //LOG( "[LCD] isTime. curr_sensor: ", String(_curr_sensor) );
      	//LOG( "[LCD] isTime. curr_frame: ", String( _sensors_list[_curr_sensor]->lcdFrame().currentFrame()) );
      
      	// clear();
      
      	// dev_frame.incFrame();
      
		  	// if( dev_frame.finished() ) 
		  	// {
        		// dev_frame.restart();
        
//			  	while( ++_curr_device < _total_devices	 )
//			  	{
//					if( _devices_list[ _curr_device ]->isActive() )
//						break;
//			  	}			
		
				_devices_list[ _curr_device ]->save( );
//		
			  	if( ++_curr_device >= _total_devices )			  		
					_curr_device = 0;	

				// dev_frame = _devices_list[ _curr_device ]->lcdFrame();
		  	// }
    
    	}

		// _devices_list[ _curr_device ]->lcdPrint( ); 
	}


}



