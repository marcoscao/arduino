/*
	Different working modes.

	Main working modes:

	0 : sleep, no reaction to clients signals
	1 : alert, waiting for client signals to perform actions
	2 : attend, attending a client alert
	3 : check, checking environment and systems
	
	RF 
		- works like a UART connection between 2 MCUs  ( microcontrollers ) but with the exception of not error validation
		- recommended velocity of 1200 or 2400 baud
		- used for redundant data ( data could be lost )
	

	Hardware:

	* RF Receptorr		: 
		Pin 2 ( no UART )
		Rx Pin ( 0 ) if using UART ( serial communication )
								
	* Antenna			: one of...
		Whip antenna ( 16,5 cm )
		Helical antenna ( 5 mm diameter and 3,4 cm long )
	
	* Working Mode Led					: Pin 13 
	* Working Mode Led Resistence		: 330 Ohm


*/

#include <RadioHead.h>
#include <RH_ASK.h>

//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//#include <VirtualWire.h>

#define WM_SLEEP 0
#define WM_ALERT 1
#define WM_ATTEND 2
#define WM_CHECK 3

#define LED_WM 13
#define BUZ_PIN 4
//#define RF_RECEPTOR_PIN 4

#define LED_BLINK_SLOW 3000
#define LED_BLINK_FAST 900

//LiquidCrystal_I2C lcd(0x3F,20,4);
LiquidCrystal_I2C lcd(0x27,20,4);

int g_wm = WM_ALERT;

bool g_led_wm_blink_onoff = false;
unsigned long g_led_wm_blink_prev_t = 0;

// 2000 bps, RX connected to D9, ( 2 and 10 guess not used, or perhaps for send messages )
RH_ASK driver( 2000, 9, 2, 10 );

 unsigned long prev_t = 0;
 unsigned long wait_t = 1500;
  
 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
 uint8_t buflen = sizeof(buf);

/*
void _read_from_rf()
{
	uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    int dato1=0;
    float dato2=0.0;

 if (vw_get_message((uint8_t *)buf,&buflen))
    {
	int i;
	String  DatoCadena="";
        if((char)buf[0]=='i') //verificamos el inicio de trama
        {
            for (i = 1; i < buflen; i++)
            {
        	DatoCadena.concat((char)buf[i]);
            }
            dato1=DatoCadena.toInt();
            Serial.print("Dato1 recivido: ");
            Serial.println(dato1);
        }
        else if((char)buf[0]=='f') //verificamos el inicio de trama
        {
            for (i = 1; i < buflen; i++)
            {
        	DatoCadena.concat((char)buf[i]);
            }
            dato2=DatoCadena.toFloat();
            Serial.print("Dato2 recivido: ");
            Serial.println(dato2);
        }
    }
}
*/

void _blink_led_wm( unsigned long wait_t )
{
	unsigned long curr_t = millis();
	
	if( curr_t - g_led_wm_blink_prev_t >= wait_t )
	{
		g_led_wm_blink_prev_t = curr_t;
		g_led_wm_blink_onoff = !g_led_wm_blink_onoff;

		digitalWrite( LED_WM, g_led_wm_blink_onoff );
	}

}


void _set_wm_sleep()
{
	g_wm = WM_SLEEP;
	digitalWrite( LED_WM, LOW );
}

void _set_wm_alert()
{
	g_wm = WM_ALERT;
	g_led_wm_blink_onoff = true;
	g_led_wm_blink_prev_t = 0;
	digitalWrite( LED_WM, HIGH );
}

void _set_wm_attend()
{
	g_wm = WM_ATTEND;
	g_led_wm_blink_onoff = true;
	g_led_wm_blink_prev_t = 0;
	digitalWrite( LED_WM, HIGH );
}

void _set_wm_check()
{
	g_wm = WM_CHECK;
	digitalWrite( LED_WM, HIGH );
}

void _loop_wm_sleep()
{
	// led off
}

void _loop_wm_alert()
{
	// led blinks slowly
	_blink_led_wm( LED_BLINK_SLOW );
}

void _loop_wm_attend()
{
	// led blinks faster
	_blink_led_wm( LED_BLINK_FAST );
}

void _loop_wm_check()
{
	// led on ( no blink )
}


void set_wm( int new_wm )
{
	switch( new_wm ) {
		case WM_SLEEP : _set_wm_sleep(); break;
		case WM_ALERT : _set_wm_alert(); break;
		case WM_ATTEND : _set_wm_attend(); break;
		case WM_CHECK : _set_wm_check(); break;
	}

}

void loop_wm()
{
	switch( g_wm ) {
		case WM_SLEEP : _loop_wm_sleep(); break;
		case WM_ALERT : _loop_wm_alert(); break;
		case WM_ATTEND : _loop_wm_attend(); break;
		case WM_CHECK : _loop_wm_check(); break;
	}
}

void setup_rf()
{
    Serial.println("Setting up RF Receptor");

    //vw_setup(2000);
    //vw_set_rx_pin( RF_RECEPTOR_PIN );
    //vw_rx_start();
}

void loop_rf()
{
	//_read_from_rf();
}

void setup()
{
	Serial.begin(9600);	
  	
	pinMode( LED_WM, OUTPUT );
  digitalWrite( LED_WM, false );

  pinMode( BUZ_PIN, OUTPUT );
  
   if(!driver.init() )
  {
    Serial.println("Oops! Something wrong initializing Radio Module" );
  }
  else
  {
    Serial.println("Radio module initialized correctly" );
  }
	//set_wm( g_wm );
	
	//setup_rf();

  
  lcd.init();
  lcd.backlight();
  lcd.setContrast(40);
  lcd.print("Ready!");
}

void loop()
{
  if(driver.recv(buf, &buflen))
  {
    digitalWrite(LED_WM,true);
    
    tone(BUZ_PIN,2100);
    
    Serial.println(" Great! Received radio message" );
    //driver.printBuffer("Got: ", buf, buflen);
    Serial.print( "   Message length: ");
    Serial.println( buflen );
    String str="";
    for (int i=0; ( i < 16 ) && ( i < buflen ); ++i )
      str +=(char)buf[i];

    Serial.print( "   Message data: \'");
    Serial.print( str );
    Serial.println( "\'");

    //Serial.print( "prev_t = " );
    prev_t = millis(); 
    //Serial.println( prev_t );

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print( prev_t );
    lcd.setCursor(0, 1);
    lcd.print( "msg: " );
    lcd.setCursor(0,2);
    lcd.print( str );
  }


  if( prev_t ) {
    //Serial.print( "curr_t = " );
    unsigned long curr_t = millis();
      
        //Serial.println( curr_t );
    if( curr_t - prev_t >= wait_t ) {
      digitalWrite(LED_WM,false); 
      noTone(BUZ_PIN);
      prev_t = 0;
    }

    if( curr_t - prev_t >= ( wait_t / 8 ) ) {
      noTone(BUZ_PIN );
    }
  }

  //Serial.print(".");
}


