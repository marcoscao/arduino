/*
  #include <math.h>
  #include <OneWire.h>
  #include <DallasTemperature.h>
*/

//#include <SoftwareSerial.h>

//#include "DevicesManager.h"
//#include "DHT11Sensor.h"
//#include "DHT11Sensor_Decorator20x4.h"
//#include "DHT11Sensor_Saver.h"
/* #include "KY013Sensor.h" */
/* #include "LDRSensor.h" */
/* #include "Lcd_I2C1602.h" */
//#include "Lcd_I2C2004.h"
#include "Log.h"
//#include "FlashLed.h"
//#include "Lcd.h"
//#include "RTC_DS1302.h"
//#include "MicroSD.h"



const int TOTAL_DEVICES = 4;

const int TOTAL_LCD_DISPLAYED_DEVICES = 2;

const int MICROSD_CS_PIN = 53;
const int TOTAL_MICROSD_SAVER_DEVICES = 1;


//ms::DevicesManager g_devices_mngr( TOTAL_DEVICES );



void configure()
{
	// initialize singletons
	ms::Log::get();
	// ms::MicroSD::get( MICROSD_CS_PIN );


  //setTime( 07,58,10,25,05,2017);
  
  	//
  	// Create Devices
  	//

//  	ms::DHT11Sensor * p_dht11 = new ms::DHT11Sensor( 22 );
//  	//////ms::llLight * p_light = new ms::DHT11Sensor( 6 );
//  	ms::FlashLed * p_flash = new ms::FlashLed( 42 );
//  	////ms::Lcd<LiquidCrystal_I2C> * p_lcd_2 = new ms::Lcd<LiquidCrystal_I2C>(1);
//  	ms::RTC_DS1302 * p_ds1302 = new ms::RTC_DS1302( 27,25,23 );
//
//
//	// Composite devices
//  	ms::Lcd_I2C2004 * p_lcd_2 = new ms::Lcd_I2C2004( TOTAL_LCD_DISPLAYED_DEVICES );
//  	//ms::MicroSD * p_msd = new ms::MicroSD( MICROSD_CS_PIN, TOTAL_MICROSD_SAVER_DEVICES );
//
//
//
//  //
//  // Set relationships
//  //
//
//  	p_dht11->setFlashLed( p_flash );
//  	//p_dht11->setMicroSD( p_msd );
//
//  	p_lcd_2->addDevice( new ms::DHT11Sensor_Decorator20x4(*p_dht11) );
//	//ms::renderable_device<DHT11Sensor_Decorator20x4>(p_dht11) );
//  	//p_lcd_2->addSensor( p_ds1302 );
//  
//  	//p_msd->addDevice( new ms::DHT11Sensor_Saver(*p_dht11) );
//
//
//  //
//  // "Graph" build. Add Order is important due to initialization order
//  //
//  // Note: Remember to increment TOTAL_DEVICES each time a new device is added
//  //
//
//  g_devices_mngr.addObject( p_flash );
//  g_devices_mngr.addObject( p_dht11 );
//  g_devices_mngr.addObject( p_ds1302 );
//
//  g_devices_mngr.addObject( p_lcd_2 );
//  //g_devices_mngr.addObject( p_msd );
//
//
//
//
//  //Serial.println( "Before initialize" );
//  g_devices_mngr.initialize();
//
//  //Serial.println( "Before activate" );
//  g_devices_mngr.activate();
//
//
//  //ms::Log & log = ms::Log::get().setRTC( p_ds1302 );
//  
}





void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // when using USB connection waits for serial synchronize
  }


  configure();

}



void loop()

{
//  g_devices_mngr.update();
//  //g_devices_mngr.debugPrint();
//
//  ////g_sensors_mngr.debugPrint();
//
//  //microsd_loop();
}


