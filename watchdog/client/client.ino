/*
	Client

	Sends radio signal when someone enters the room

	RF 
		- works like a UART connection between 2 MCUs  ( microcontrollers ) but with the exception of not error validation
		- recommended velocity of 1200 or 2400 baud
		- used for redundant data ( data could be lost )


	Hardware

	* RF Emitter		: 
		Pin 2 
		Tx Pin ( 1 ) if using UART ( serial communication )
		

	* Antenna			: one of...
		Whip antenna ( 16,5 cm )
		Helical antenna ( 5 mm diameter and 3,4 cm long )

	* Led					: Pin 13 
	* Led Resistence	: 330 Ohm


*/

#include <VirtualWire.h>

#define PIR_PIN 2
#define RF_EMITTER_PIN 4
#define LED_PIN 13

#define LED_BLINK_SLOW 3000
#define LED_BLINK_FAST 900

bool g_led_onoff = false;
unsigned long g_led_blink_prev_t = 0;
bool g_pir_prev_state = false;


void _blink_led_wm( unsigned long wait_t )
{
	unsigned long curr_t = millis();
	
	if( curr_t - g_led_blink_prev_t >= wait_t )
	{
		g_led_blink_prev_t = curr_t;
		g_led_onoff = !g_led_onoff;

		digitalWrite( LED_PIN, g_led_onoff );
	}
}

void _send_rf_data( )
{
 	char buf[VW_MAX_MESSAGE_LEN]; 
	float f=3.141516;   
	String s="Value read from room: ";  
    
	s=s + String(f); 
   s.toCharArray(buf,sizeof(buf)); 
   vw_send((uint8_t *)buf, strlen(buf)); 
   vw_wait_tx(); 
}

void setup()
{
	Serial.begin( 9600 );
  	pinMode( LED_PIN, OUTPUT );
  	pinMode( PIR_PIN, INPUT );
	
	g_led_onoff = true;
	g_led_blink_prev_t = 0;
	digitalWrite( LED_PIN, LOW );

	// RF bits per second
	vw_setup(2000);	
	vw_set_tx_pin( RF_EMITTER_PIN );
}

void loop()
{
	int pir_val = digitalRead( PIR_PIN );

	if( pir_val == HIGH )
	{
		if( g_pir_prev_state == LOW )
		{
  			Serial.println( "** ALARM!!!!!! a presence has been detected!!!" );
			
			g_led_blink_prev_t = 0;
			g_led_onoff = true;
			digitalWrite( PIR_PIN, HIGH );
		}
		
		_blink_led( LED_BLINK_SLOW );
	}
	else
	{
		if( g_pir_prev_state == HIGH )
		{
  			Serial.println( "** Presence has leave the room **" );
			digitalWrite( PIR_PIN, LOW );
		}
	}

	g_pir_prev_state = pir_val;

}

