/*
	Different working modes.

	RF
		- works like a UART connection between 2 MCUs  ( microcontrollers ) but with the exception of not error validation
		- recommended velocity of 1200 or 2400 baud
		- used for redundant data ( data could be lost )


	Hardware:

	 RF Receptorr		:
		Pin 2 ( no UART )
		Rx Pin ( 0 ) if using UART ( serial communication )

	 Antenna			: one of...
		Whip antenna ( 16,5 cm )
		Helical antenna ( 5 mm diameter and 3,4 cm long )

	 Working Mode Led					    : Pin 13
	 Working Mode Led Resistence		: 330 Ohm

*/

//#define USE_TFT 1

#ifdef USE_TFT

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define TS_MINX 130
#define TS_MAXX 905

#define TS_MINY 75
#define TS_MAXY 930

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BOXSIZE 40
#define PENRADIUS 2
int oldcolor, currentcolor;

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
//Adafruit_TFTLCD tft;

#endif




#include <RadioHead.h>
#include <RH_ASK.h>



#ifndef USE_TFT
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

////LiquidCrystal_I2C lcd(0x3F,16,2);
//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd(0x3F, 20, 4);


#endif

#define LED_WM 13
#define BUZ_PIN 4
//#define RF_RECEPTOR_PIN 4

#define LED_BLINK_SLOW 3000
#define LED_BLINK_FAST 900


//int g_wm = WM_ALERT;

bool g_led_wm_blink_onoff = false;
unsigned long g_led_wm_blink_prev_t = 0;


// 2000 bps, RX connected to D9, ( 2 and 10 guess not used, or perhaps for send messages )
RH_ASK driver( 2000, 9, 2, 10 );


unsigned long msg_led_prev_t = 0;
unsigned long msg_led_wait_t = 1500;

uint8_t msg_buffer[RH_ASK_MAX_MESSAGE_LEN];
uint8_t msg_buffer_length = sizeof(msg_buffer);

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

  if ( curr_t - g_led_wm_blink_prev_t >= wait_t )
  {
    g_led_wm_blink_prev_t = curr_t;
    g_led_wm_blink_onoff = !g_led_wm_blink_onoff;

    digitalWrite( LED_WM, g_led_wm_blink_onoff );
  }

}


void setup_rf()
{
  Serial.println("Setting up RF Receptor");
  if (!driver.init() )
  {
    Serial.println("Oops! Something wrong initializing Radio Module" );
  }
  else
  {
    Serial.println("Radio module initialized correctly" );
  }
}

#ifndef USE_TFT
void setup_lcd()
{
  lcd.init();

  
  //lcd.backlight();
  lcd.backlight();
  //lcd.setContrast(70);
  lcd.setCursor(0,0);
  lcd.print("Ready!");

  Serial.println("LCD initialized");

}
#endif


#ifdef USE_TFT
void setup_tft()
{
  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  tft.setRotation(1);

  tft.fillScreen(BLACK);

  tft.fillRect(50, 20, BOXSIZE, BOXSIZE, RED);
  //tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  //tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  //tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  //currentcolor = RED;

  //pinMode(13, OUTPUT);

  tft.fillScreen(BLACK);

  unsigned long start = micros();
  tft.setCursor(0, 0);

  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.println("Control Inteligente Hogar");
  //tft.println(01234.56789);
  //tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.println();
  tft.setTextColor(GREEN); tft.setTextSize(2);
  tft.println("Ubicacion  Temperatura  Humedad  Presen");
  tft.println("---------------------------------------");
  tft.println("Salon        23.20 C      45%      X");
  //tft.println("Habitacion   21.20 C      45%");
  //tft.println("Terraza      19.10 C      46%");
  //tft.println("Atico        19.10 C      46%");
  //tft.println("Atico-Terr   19.10 C      46%");
  //tft.println("_______________________________________");
  //tft.println();
  //tft.println();
  //tft.println();
  //tft.println();
  //tft.println();
  //tft.println();
  //tft.println();
  //tft.println();
  //tft.setTextColor(CYAN);
  //tft.println("Volver   Alertas   Historial");
}
#endif

void setup()
{
  Serial.begin(9600);

  pinMode( LED_WM, OUTPUT );

  // led on during setup
  digitalWrite( LED_WM, true );


  pinMode( BUZ_PIN, OUTPUT );


#ifdef USE_TFT
  setup_tft();
#else
  setup_lcd();
#endif

  setup_rf();

  // set led to off after setup
  digitalWrite( LED_WM, false );
}


void loop_rf()
{
  
  if (driver.recv(msg_buffer, &msg_buffer_length))
  {
    digitalWrite(LED_WM, true);

    tone(BUZ_PIN, 2100);

    Serial.println(" Great! Received radio message" );
    //driver.printBuffer("Got: ", buf, buflen);
    Serial.print( "   Message length: ");
    Serial.println( msg_buffer_length );

    String str = "";

    for (int i = 0; ( i < 16 ) && ( i < msg_buffer_length ); ++i )
      str += (char)msg_buffer[i];

    Serial.print( "   Message data: \'");
    Serial.print( str );
    Serial.println( "\'");

    //Serial.print( "prev_t = " );
    msg_led_prev_t = millis();
    //Serial.println( prev_t );


#ifndef USE_TFT
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print( msg_led_prev_t );
    lcd.setCursor(0, 1);
    lcd.print( "msg: " );
    lcd.setCursor(0, 2);
    lcd.print( str );
#endif
  }


  if ( msg_led_prev_t ) {
    //Serial.print( "curr_t = " );
    unsigned long curr_t = millis();

    //Serial.println( curr_t );
    if ( curr_t - msg_led_prev_t >= msg_led_wait_t ) {
      digitalWrite(LED_WM, false);
      noTone(BUZ_PIN);
      msg_led_prev_t = 0;
    }

    if ( curr_t - msg_led_prev_t >= ( msg_led_wait_t / 8 ) ) {
      noTone(BUZ_PIN );
    }
  }

  //Serial.println(" looping..................." );
}


void loop()
{

  loop_rf();

}


