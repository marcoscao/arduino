//#include <Adafruit_Sensor.h>


#include "message.h"


// SPI, SD needed due to console Arduino-Makefile usage
#include <SPI.h>
#include <SD.h>

#include <RadioHead.h>
#include <RH_ASK.h>

#include <DHT.h>


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

#define PIR_PIN 11
#define RF_EMITTER_PIN 2
#define LED_PIN 13
#define DHT_PIN 3
#define LED_BLINK_SLOW 100
#define LED_BLINK_FAST 900

#define DHTTYPE DHT22   // Sensor DHT22

DHT dht(DHT_PIN, DHTTYPE);

unsigned long dht_wait_t = 3500;
unsigned long dht_prev_t = 0;


bool g_led_onoff = false;
unsigned long g_led_blink_prev_t = 0;
unsigned long g_check_pir_t = 0;
bool g_pir_prev_state = LOW;

#define CLIENT_ADDRESS 1

// 2000 bps, sending ( TX ) through D9   ( don't know whether D2 and D10 are used )
RH_ASK driver( 2000, 2, 9, 10 );

//RHReliableDatagram manager( driver, CLIENT_ADDRESS );

//uint8_t msg_data[] = "ALARM!! Presence detected in the room!";
//uint8_t msg_buf[RH_ASK_MAX_MESSAGE_LEN];
// const char * msg_data = "ALARM!! Presence detected in the room!";

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

  dht.begin();
  Serial.println("DHT22 ready");
  
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

      msc::message msg;
      String s = msg.serialize();
      
      //Serial.println(" ** going to send radio message" );
      //driver.send((uint8_t*)s.toCharArray(), s.length() );
      //Serial.println( "   waiting for packet to be sent" );
      //driver.waitPacketSent();
      //Serial.println( "** radio message has been sent" );
  
      // Send radio message      
      //Serial.println("   going to send radio message" );
      //driver.send((uint8_t*)msg_data, strlen(msg_data) );
      //Serial.println( "   waiting for packet sent" );
      //driver.waitPacketSent();
      //Serial.println( "   Alarm message has been sent" );
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


    
  
  unsigned long dht_curr_t = millis();
  
  if( !dht_prev_t )
    dht_prev_t = dht_curr_t;
  
  if( dht_curr_t - dht_prev_t >= dht_wait_t )
  {
    float h = dht.readHumidity();

    // temperature in ºC
    float t = dht.readTemperature();      
  
    // float f = dht.readTemperature(true);  // Fahrenheit
        
    Serial.print("Humedad ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" *C ");

    /*
    String s = "T: ";
    s += t;
    s += " | H: ";
    s += h;
    
    char buff[s.length()+1];
    s.toCharArray(buff,s.length()+1);
    
      Serial.println("   going to send temperature radio message" );
      driver.send((uint8_t*)buff, strlen(buff) );
      Serial.println( "   waiting for packet to be sent" );
      driver.waitPacketSent();
      Serial.println( "   Temperature radio message has been sent" );

    */
    msc::message msg;
   
    msg.header.set_info( "Room-01" );
    msg.header.type = msc::message_type::MT_DHT22;
     
    msg.body.body_dht22.temperature = t;
    msg.body.body_dht22.humidity = h;

    String s2 = msg.serialize();
    char buff2[s2.length()+1];
    s2.toCharArray(buff2,s2.length()+1);
    Serial.println("   going to send temperature radio message" );
      driver.send((uint8_t*)buff2, strlen(buff2) );
      Serial.println( "   waiting for packet to be sent" );
      driver.waitPacketSent();
      Serial.println( "   Temperature radio message has been sent" );

    
    dht_prev_t = 0;
  }

  
}

