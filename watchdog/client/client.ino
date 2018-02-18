#include <RadioHead.h>
#include <RH_ASK.h>
/*
  #include <RH_CC110.h>
  #include <RH_E32.h>
  #include <RH_MRF89.h>
  #include <RH_NRF24.h>
  #include <RH_NRF51.h>
  #include <RH_NRF905.h>
  #include <RH_RF22.h>
  #include <RH_RF24.h>
  #include <RH_RF69.h>
  #include <RH_RF95.h>
  #include <RH_Serial.h>
  #include <RH_TCP.h>
  #include <RHCRC.h>
  #include <RHDatagram.h>
  #include <RHEncryptedDriver.h>
  #include <RHGenericDriver.h>
  #include <RHGenericSPI.h>
  #include <RHHardwareSPI.h>
  #include <RHMesh.h>
  #include <RHNRFSPIDriver.h>
  #include <RHReliableDatagram.h>
  #include <RHRouter.h>
  #include <RHSoftwareSPI.h>
  #include <RHSPIDriver.h>
  #include <RHTcpProtocol.h>
*/
/*
	Client

	Sends radio signal when someone enters the room

	RF
		- works like a UART connection between 2 MCUs  ( microcontrollers ) but with the exception of not error validation
		- recommended velocity of 1200 or 2400 baud
		- used for redundant data ( data could be lost )


	Hardware

	 RF Emitter		:
		Pin 2
		Tx Pin ( 1 ) if using UART ( serial communication )


	 Antenna			: one of...
		Whip antenna ( 16,5 cm )
		Helical antenna ( 5 mm diameter and 3,4 cm long )

	 Led					: Pin 13
	 Led Resistence	: 330 Ohm


*/

//#include <VirtualWire.h>

#define PIR_PIN 11
#define RF_EMITTER_PIN 2
#define LED_PIN 13

#define LED_BLINK_SLOW 100
#define LED_BLINK_FAST 900

bool g_led_onoff = false;
unsigned long g_led_blink_prev_t = 0;
unsigned long g_check_pir_t = 0;
bool g_pir_prev_state = LOW;


#define CLIENT_ADDRESS 1

// 2000 bps, RX ( D4, pin 3 ), TX ( D3, pin 2 )
//RH_ASK driver( 2000, 3 );

// 2000 bps, sending ( TX ) through D9   ( don't know whether D2 and D10 are used )
RH_ASK driver( 2000, 2, 9, 10 );

//RHReliableDatagram manager( driver, CLIENT_ADDRESS );

//uint8_t msg_data[] = "ALARM!! Presence detected in the room!";
//uint8_t msg_buf[RH_ASK_MAX_MESSAGE_LEN];
const char * msg_data = "ALARM!! Presence detected in the room!";

void _blink_led( unsigned long wait_t )
{
  unsigned long curr_t = millis();

  if ( curr_t - g_led_blink_prev_t >= wait_t )
  {
    Serial.println( "blinking!");
    g_led_blink_prev_t = curr_t;
    g_led_onoff = !g_led_onoff;

    digitalWrite( LED_PIN, g_led_onoff );
  }
}

void _send_rf_data( )
{
  //  char buf[VW_MAX_MESSAGE_LEN];
  char buf[512];
  float f = 3.141516;
  String s = "Value read from room: ";

  s = s + String(f);
  s.toCharArray(buf, sizeof(buf));
  //vw_send((uint8_t *)buf, strlen(buf));
  //vw_wait_tx();
}

void setup()
{
  Serial.begin( 9600 );
  pinMode( LED_PIN, OUTPUT );
  pinMode( PIR_PIN, INPUT );

  g_led_onoff = false;
  g_led_blink_prev_t = 0;
  digitalWrite( LED_PIN, LOW);
  digitalWrite( PIR_PIN, LOW );

  int calib_t = 5;
  Serial.print( "Calibrating PIR Sensor ( " );
  Serial.print( calib_t );
  Serial.println( " seconds ) " );

  // Calibrate PIr ( do reads during 10-60 seconds )
  for (int i = 0; i < calib_t; i++ )
  {
    digitalRead( PIR_PIN);
    Serial.print(i);
    Serial.print(" ");
    delay(1000);
  }
  Serial.println("");
  Serial.println( "PIR Sensor ready");

  if (!driver.init() )
  {
    Serial.println("Oops! Something wrong initializing Radio Transmitter" );
  }
  else
  {
    Serial.println("Radio transmitter initialized correctly" );
  }

  // RF bits per second
  //vw_setup(2000);
  //vw_set_tx_pin( RF_EMITTER_PIN );
}

void loop()
{
  //unsigned long curr_t = millis();
  //int pir_val = g_pir_prev_state;

  //if( curr_t - g_check_pir_t > 100 )
  //{
  int pir_val = digitalRead( PIR_PIN );
  //}

  //Serial.println( "********** PIR value: " + pir_val );

  if ( pir_val == HIGH )
  {
    if ( g_pir_prev_state == LOW )
    {
      Serial.println( "** ALARM!!!!!! a presence has been detected!!!" );

      g_led_blink_prev_t = 0;
      g_led_onoff = true;
      digitalWrite( LED_PIN, HIGH );

      // Send radio message
      //const char * msg = "ALARM! Presence in the room";
      Serial.println("   going to send radio message" );
      driver.send((uint8_t*)msg_data, strlen(msg_data) );
      Serial.println( "   waiting for packet sent" );
      driver.waitPacketSent();
      Serial.println( "   Alarm message has been sent" );
    }

    //_blink_led( LED_BLINK_SLOW );
  }
  else
  {
    if ( g_pir_prev_state == HIGH )
    {
      Serial.println( "** Presence has leave the room **" );
      digitalWrite( LED_PIN, LOW );
    }
  }

  g_pir_prev_state = pir_val;
}

