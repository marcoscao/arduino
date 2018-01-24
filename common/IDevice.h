
#ifndef MS_IDEVICE_H__
#define MS_IDEVICE_H__

//#include <SoftwareSerial.h>

#include "Log.h"
#include "Timer.h"
#include <WString.h>
#include <Arduino.h>


namespace ms
{

class IDevice
{
    typedef void (IDevice::*LoopFn)(void);

  public:
    IDevice( int pin = -1,
             int io_mode = OUTPUT,
             Timer wait_ready_timer = Timer(200, Timer::TIMER_ONCE ),
             Timer update_timer = Timer() )
      :	_activated(false),
        _ready(false),
        _pin( pin ),
        _io_mode( io_mode ),
        _err(0),
        _wait_ready_timer( wait_ready_timer ),
        _update_timer( update_timer )
    {
      pinMode( getPin(), getIOMode() );
    }

    virtual String name() const = 0;


    int getPin() const
    {
      return _pin;
    }

    int getIOMode() const
    {
      return _io_mode;
    }

    bool isDigitalPin() const
    {
      return _pin >= 0 && _pin <= 53 ? true : false;
    }

    Timer & updateTimer()
    {
      return _update_timer;
    }

    Timer & waitReadyTimer()
    {
      return _wait_ready_timer;
    }

    void initialize( )
    {
      String s = "Successful";
      if ( not _do_initialize() )
      {
        _err = 1;
        s = "FAILED!!";
      }

      LOG( "IDevice", "initializing " + name() + "...", s );
    }

    void uninitialize( )
    {
      _wait_ready_timer.stop();
      _update_timer.stop();

      if ( not _do_uninitialize() )
        _err = 2;
    }

    void activate( )
    {
      if ( _activated )
        return;

      String s = "Ok";

      if ( not _do_activate() )
      {
        _err = 3;
        s = "ERROR!";
      }
      else
      {
        _activated = true;
        _loop_fn = &IDevice::loopWhileNotReady;
        _wait_ready_timer.start();
      }

      LOG( "IDevice", "activating " + name() + "...", s );
    }

    void deactivate( )
    {
      if ( not _activated )
        return;

      _activated = false;
      _wait_ready_timer.stop();
      _update_timer.stop();

      if ( not _do_deactivate() )
        _err = 4;
    }

    bool isActive() const
    {
      return _activated;
    }

    void update()
    {
      (*this.*_loop_fn)();
    }

    void loopWhenReady()
    {
      if ( not _activated )
        return;

      if ( not _update_timer.isTime() )
        return;

      _do_update();
      //debugPrint();
    }

    void loopWhileNotReady()
    {
      if ( not _wait_ready_timer.isTime() )
        return;

      _ready = true;
      LOG( "IDevice", name() + " is ready" );

      _loop_fn = &IDevice::loopWhenReady;
      _update_timer.start();
    }

    void debugPrint() const
    {
      // delay(1000);
      LOG("- " + name() + " " );

      _do_debug_print();

      Serial.println();
    }

  private:
    bool _activated;
    bool _ready;
    int _pin;
    int _io_mode;
    int _err;
    Timer _wait_ready_timer;
    Timer _update_timer;
    LoopFn _loop_fn;

    virtual bool _do_initialize() = 0;
    virtual bool _do_uninitialize() = 0;
    virtual bool _do_activate() = 0;
    virtual bool _do_deactivate() = 0;

    virtual void _do_update() = 0;
    virtual void _do_debug_print() const {
      ;
    }
};


//
//class ILcd;
//
//class IRenderableDevice
//{
//	public:
//		virtual void render( ILcd & lcd, int frame ) = 0;
//};




}

#endif


