#ifndef LEDSMANAGER_H__
#define LEDSMANAGER_H__

#include "ILed.h"
#include "IManager.h"
// #include <LiquidCrystal.h>

// static const char * VERSION = "1.10.13";

namespace ms
{

class LedsManager : public IManager
{
	// struct show_st
	// {
   //  	int current_sensor;
   //  	unsigned long interval_t;
   //  	unsigned long curr_t;
   //  	unsigned long prev_t;
   //    
	// 	show_st() 
	// 		: current_sensor(0),
   //      curr_t(0),
   //      prev_t(0),
   //      interval_t(5000)
	// 	{
	// 	}	
	// };
   //

  public:
   LedsManager( IDevice** leds_list, int total )
	: IManager( leds_list, total )
       // : _total_sensors(total)
			 // _lcd( 12, 11, 5, 4, 3, 2 ),
		 	// _show()
    {
      // _lcd.begin(16, 2);
      // _lcd.setCursor(0, 0);
      // _lcd.print("M-Station");
      // _lcd.setCursor(0, 1);
      // _lcd.print( VERSION );
      //
		// _sensors_list = new ISensor*[ _total_sensors ];
      //
		// for(int i = 0; i < _total_sensors; ++i )
		// {
		// 	_sensors_list[i] = a_sensors_list[i];
		// }
    }

	 // ~SensorsManager()
	 // {
		//  delete[] _sensors_list;
	 // }
    //
    // void initialize()
    // {
    //   // Activate sensors
    //   for (int i = 0; i < _total_sensors; ++i )
    //   {
    //     ISensor * p = _sensors_list[i];
    //     p->activate();
    //   }
    // }
    //

	private:
	 // void _do_initialize( IDevice* p )
	 // {
	 // 	p->enable();
	 // 	p->activate();
	 // }

  //   void update()
  //   {
  //     for (int i = 0; i < _total_sensors; ++i )
  //     {
  //       ISensor * p = _sensors_list[i];
  //       if ( p && p->isActive() )
  //         p->update();
  //     }
  //   }
  //
  //
  //   void serialPrint()
  //   {
  //     for (int i = 0; i < _total_sensors; ++i )
  //     {
  //       ISensor * p = _sensors_list[i];
  //       if ( p && p->isActive() )
  //         p->serialPrint();
  //     }
  //   }
  //
  //
  //   void lcdPrint()
  //   {
  //     ISensor * p = 0;
  //     _show.curr_t = millis();
  //
  //     if ( _show.curr_t - _show.prev_t > _show.interval_t )
  //     {
  //       _show.current_sensor++;
  //
  //       // Prints each one during a time
  //       if ( _show.current_sensor >= _total_sensors || _show.current_sensor < 0 )
  //         _show.current_sensor = 0;
  //
  //       // Verifies it is activated
  //       while ( _show.current_sensor < _total_sensors )
  //       {
  //         p = _sensors_list[ _show.current_sensor ];
  //
  //         if ( p->isActive() )
  //           break;
  //
  //         p = 0;
  //       }
  //     }
  //
  //     if ( !p )
  //       return;
  //
  //     p->lcdPrint(_lcd);
  //
  //     _show.prev_t = millis();
  //   }
  //
  //
  // private:
  //   const int _total_sensors;
  //   ISensor** _sensors_list;
	//  show_st _show;
  //   LiquidCrystal _lcd;
};

}

#endif


