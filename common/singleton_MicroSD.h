#ifndef MS_MICROSD_H__
#define MS_MICROSD_H__

// #include "IDevice.h"

#include <SD.h>
#include <SPI.h>

namespace ms
{
class MicroSD //: public IDevice
{
  public:
	 static MicroSD & get( int cs_pin = -1 )
	 {
      static MicroSD * sd = 0;
      
	 	if( not sd && cs_pin != -1 )
		  sd = new MicroSD( cs_pin );
	 }

    String name() const
    {
      return "MicroSD";
    }

    bool existsFile( const String & fname )
    {
      bool r = false;
      File f;
      
      f = SD.open( fname, FILE_READ );
      if( f )
        r = true;

      f.close();
      
      return r;
    }
    

    bool createFile( const String & fname, File & f )
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

    bool openFile( const String & fname, File & f )
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
    

    bool createDir( const String & dname )
    {

      return false;
    }


    
  private:

    MicroSD( int cs_pin )
      //: 	IDevice( cs_pin, OUTPUT, Timer( 100, Timer::TIMER_ONCE ) )
    {
		 _initialize(cs_pin);
    }

    bool _initialize( int cs_pin )
    {
      LOG( "MicroSD", "initializing card...");
      pinMode( cs_pin, OUTPUT);
      digitalWrite( cs_pin, HIGH);

      if ( not SD.begin( cs_pin ) )
      {
        LOG( "MicroSD", "card initialization failed");
        return false;
      }

      LOG( "MicroSD", "card ready to be used");
      return true;
    }

    // bool _do_uninitialize()
    // {
    //   return true;
    // }
    //
    // bool _do_activate()
    // {
    //   return true;
    // }
    //
    // bool _do_deactivate()
    // {
    //   return true;
    // }
    //
    // void _do_update()
    // {
    //   ;
    // }
    //


};
}

#endif

