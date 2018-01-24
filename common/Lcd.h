#ifndef MS_LCD_H__
#define MS_LCD_H__

#include "ILcd.h"
#include "lcdtype_base.h"
#include "Decorator.h"

namespace ms
{
	template<typename T>
	class Lcd : public ILcd
	{
	  public:
		Lcd( 	int total_devices, 
				const Timer & wait_ready_timer=Timer(50), 
				const Timer & update_timer=Timer(120),
				const Timer & frame_timer=Timer(7000) )
		: 	ILcd( wait_ready_timer, update_timer ),
			_lcd( new lcdtype<T>() ),
      	_curr_device(0),
      	_curr_add(0),
			_total_devices( total_devices ),
			_devices_list( new Decorator*[ total_devices ] ),
      	_frame_timer( frame_timer )
	 	{
		}

		int addDevice( Decorator * p )
		{
			int index = _curr_add;
			_devices_list[ index ] = p;

			if( ++_curr_add == _total_devices )
				_curr_add--;

			p->setLcd( static_cast<ms::ILcd*>( this ) );
			return index;
		}

    	String name() const
    	{
      	return _lcd->name();
    	}

    	bool _do_initialize() 
    	{
      	return _lcd->initialize();
    	}
    
    	bool _do_uninitialize() 
    	{
      	return _lcd->uninitialize();
    	}

    	bool _do_activate() 
    	{
        _frame_timer.start();
      	return _lcd->activate();
    	}

    	bool _do_deactivate() 
    	{
      	return _lcd->deactivate();
    	}

//		ILcd & getLcd()
//		{
//			return static_cast<ILcd&>( *_lcd );
//		}
//    
		virtual void setCursor( int col, int line)
		{
			_lcd->setCursor( col, line );
		}

		virtual void print( const String & s)
		{
			_lcd->print(s);
		}

		virtual void clear()
		{
			_lcd->clear();
		}

		virtual int rows() const
		{
			return _lcd->rows();
		}

		virtual int cols() const
		{
			return _lcd->cols();
		}


  private:  
    const int _total_devices; 
    lcdtype< T > * _lcd;
    unsigned int _curr_device;
    int _curr_add;
    Decorator** _devices_list;
    Timer _frame_timer;


	void _do_update( )
	{
		LcdFrame & dev_frame = _devices_list[ _curr_device ]->lcdFrame();
		
    	// time to pass to a new frame during lcd refresh?? then increment frame of device
    	if( _frame_timer.isTime() )
    	{
		  //LOG( "[LCD] isTime. curr_sensor: ", String(_curr_sensor) );
      	//LOG( "[LCD] isTime. curr_frame: ", String( _sensors_list[_curr_sensor]->lcdFrame().currentFrame()) );
      
      	clear();
      
      	dev_frame.incFrame();
      
		  	if( dev_frame.finished() ) 
		  	{
        		dev_frame.restart();
        
//			  	while( ++_curr_device < _total_devices	 )
//			  	{
//					if( _devices_list[ _curr_device ]->isActive() )
//						break;
//			  	}			
//		
			  	if( ++_curr_device >= _total_devices )			  		
					_curr_device = 0;	

				dev_frame = _devices_list[ _curr_device ]->lcdFrame();
		  	}
    
    	}

		// _devices_list[ _curr_device ]->lcdPrint( ); 
		_devices_list[ _curr_device ]->render( dev_frame.currentFrame() );
	}

};

}

#endif


