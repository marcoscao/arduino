#ifndef MS_MICROSD_H__
#define MS_MICROSD_H__

#include "IDevice.h"
#include "Timer.h"
#include <WString.h>

namespace ms
{
	class Saver;

	class MicroSD : public IDevice
	{
	  public:
		MicroSD( 	int cs_pin, int total_devices, 
				const Timer & wait_ready_timer=Timer(50), 
				const Timer & update_timer=Timer(120),
				const Timer & frame_timer=Timer(250) );

		int addDevice( ms::Saver * p );

    	String name() const;

    	bool _do_initialize() ;
    
    	bool _do_uninitialize(); 

    	bool _do_activate();

    	bool _do_deactivate(); 

    bool existsFile( const String & fname );

    bool createFile( const String & fname, File & f );

    bool openFile( const String & fname, File & f );
    
    bool createDir( const String & dname );

  private:  
    const int _total_devices; 
    unsigned int _curr_device;
    int _curr_add;
    Saver** _devices_list;
    Timer _frame_timer;


	void _do_update( );

};

}

#endif


