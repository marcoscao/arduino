#include <LiquidCrystal.h>
#include "Sensors.h"
#include <math.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT11.h>


static const char * VERSION = "1.1.07";



/*
   Sensors Stuff
*/

class ISensor
{
  public:

    virtual const char * name() const = 0;

    void setActive( bool a )
    {
      _is_active = a;
    }

    bool isActive() const
    {
      return _is_active;
    }

    virtual void update() = 0;

    virtual void printSerial() const = 0;

    virtual void printLCD( LiquidCrystal & lcd ) = 0;

  private:
    bool _is_active;

};



template<typename T>
class SensorData : public ISensor
{
  public:

    SensorData()
      : _current_value(0),
        _low_limit(-10000),
        _high_limit(10000)
    {
    }


    // read current physical value
    void update()
    {
      _current_value = this->_readValue();
    }

    void printSerial() const
    {
      Serial.print( name() );
      Serial.print( " current_value : " );
      Serial.print( _current_value );
      Serial.println();
      Serial.print( "  |  current_value_2: ");
      Serial.print( _current_value );
      Serial.println();
    }

    void printLCD( LiquidCrystal & lcd )
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print( name() );

      lcd.setCursor(0, 1);
      lcd.print( _current_value );
      if( _current_value_2 != 999999 )
      {  
        lcd.print( " |  " );
        lcd.print( _current_value_2 );
      }
       
    }

    void setCurrentValue( const T & v )
    {
      _current_value = v;
    }

    void setCurrentValue2( const T & v )
    {
      _current_value_2 = v;
    }
    
    T currentValue() const
    {
      return _current_value;
    }

    void setHighLimit( T lim )
    {
      _high_limit = lim;
    }

    T highLimit() const
    {
      return _high_limit;
    }

    void setLowLimit( T lim )
    {
      _low_limit = lim;
    }

    T lowLimit() const
    {
      return _low_limit;
    }

    bool checkLimit() const
    {
      return _current_value > _high_limit || _current_value < _low_limit;
    }

  private:
    T _current_value;
    T _current_value_2;
    T _low_limit;
    T _high_limit;

    virtual T _readValue() = 0;
};



class TemperatureSensor : public SensorData<double>
{
  public:
    static const int IO_TEMPERATURE_SENSOR = A0;
    
    TemperatureSensor()
    {
      setLowLimit( 12.0 );
      setHighLimit( 24.0 );
    }

    const char * name() const
    {
      return "Temperature";
    }


  private:
    const double _temp_base = 20.0;

    double _readValue()
    {

      int val = analogRead( IO_TEMPERATURE_SENSOR );
      //float volt = (val / 1024.0) * 5.0;
      //float temp = ( volt - .5) * 100;
 
   double Temp;
  Temp = log(((10240000/val) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;
  return Temp;

      //int RawADC = val;
      //double temp = val;
      //double Vo;
      //Vo=float(RawADC)*(3.3/4095);
      //temp = log(10000*(3.3/Vo-1));
      ////Temp = log(((10240000/RawADC) - 10000));
      //temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
      //temp = temp - 273.15;// Convert Kelvin to Celcius
  
      //return temp;   
    }
};


class LightSensor : public SensorData<int>
{
  public:

    static const int IO_LIGHT_SENSOR = A5;

    LightSensor()
    {
    }

    const char * name() const
    {
      return "Luminosidad";
    }

  private:
    int _readValue()
    {
      int f = analogRead( IO_LIGHT_SENSOR );
      return f;
    }
};


class TempHumSensor : public SensorData<double>
{
  public:
    static const int IO_TEMP_HUM_SENSOR = 6;
    
    TempHumSensor()
    : _dht11( IO_TEMP_HUM_SENSOR ) {
      
      setLowLimit( 12.0 );
      setHighLimit( 24.0 );
     
    }

    const char * name() const
    {
      return "Temp-Humidity";
    }


  private:
    const double _temp_base = 20.0;

    double _readValue()
    {
       float temp, hum;
       int error = _dht11.read(hum,temp );

        Serial.print( "DHT11 temp: ");
        Serial.print( temp );
        Serial.print( "DHT11 hum: " );
        Serial.print( hum );
        Serial.println();
        
        setCurrentValue2( hum );

        delay(1000);
        return temp;
    
    }

    private:
    DHT11 _dht11;
};


class SensorsManager
{
  public:
    SensorsManager()
      : _current_lcd_sensor(0),
        _lcd_current_time(0),
        _lcd_previous_time(0),
        _lcd_interval_time(5000),      // by default each sensor value is displayed during 5sec
        _lcd( 12, 11, 5, 4, 3, 2 )
    {
      _lcd.begin(16, 2);
      _lcd.setCursor(0, 0);
      _lcd.print("Monitor-Station");
      _lcd.setCursor(0, 1);
      _lcd.print( VERSION );
    }


    void initialize()
    {
      // Activate sensors
      for (int i = 0; i < TOTAL_SENSOR_OBJECTS; ++i )
      {
        ISensor * p = sensors_list[i];
        p->setActive(true);
      }
    }


    void update()
    {
      for (int i = 0; i < TOTAL_SENSOR_OBJECTS; ++i )
      {
        ISensor * p = sensors_list[i];
        if ( p && p->isActive() )
          p->update();
      }
    }


    void printSerial()
    {
      for (int i = 0; i < TOTAL_SENSOR_OBJECTS; ++i )
      {
        ISensor * p = sensors_list[i];
        if ( p && p->isActive() )
          p->printSerial();
      }
    }


    void printSensorToLCD()
    {
      ISensor * p = 0;
      _lcd_current_time = millis();

      if ( _lcd_current_time - _lcd_previous_time > _lcd_interval_time )
      {
        _current_lcd_sensor++;

        // Prints each one during a time
        if ( _current_lcd_sensor >= TOTAL_SENSOR_OBJECTS || _current_lcd_sensor < 0 )
          _current_lcd_sensor = 0;

        // Verifies it is activated
        while ( _current_lcd_sensor < TOTAL_SENSOR_OBJECTS )
        {
          p = sensors_list[ _current_lcd_sensor ];

          if ( p->isActive() )
            break;

          p = 0;
        }
      }

      if ( !p )
        return;

      p->printLCD(_lcd);

      _lcd_previous_time = millis();
    }


  private:
    static const int TOTAL_SENSOR_OBJECTS = 3;
    static ISensor* sensors_list[TOTAL_SENSOR_OBJECTS];

    static TemperatureSensor _temp_sensor;
    static LightSensor _light_sensor;
    static TempHumSensor _temp_hum_sensor;

    int _current_lcd_sensor;
    unsigned long _lcd_interval_time;
    unsigned long _lcd_current_time;
    unsigned long _lcd_previous_time;
    LiquidCrystal _lcd;
};

TemperatureSensor SensorsManager::_temp_sensor;
LightSensor SensorsManager::_light_sensor;
TempHumSensor SensorsManager::_temp_hum_sensor;


ISensor* SensorsManager::sensors_list[TOTAL_SENSOR_OBJECTS] = {
  &_temp_sensor,
  &_light_sensor,
  &_temp_hum_sensor
};



/**
   LEDs Stuff
*/

class LED
{
    friend class LEDsManager;

  public:
    enum LedType
    {
      GREEN_LED,
      RED_LED,
      YELLOW_LED,
      RGB_LED
    };

    LED( int pin, LedType type, int io_mode = OUTPUT, int high_low = HIGH )
      : _type( type ),
        _pin( pin ),
        _io_mode(io_mode),
        _high_low( high_low )
    {
    }

  private:
    LedType _type;
    int _pin;
    int _io_mode;
    int _high_low;
};



class LEDsManager
{
  public:
    void initialize()
    {
      // Activate sensors
      for (int i = 0; i < TOTAL_LED_OBJECTS; ++i )
      {
        LED * p = leds_list[i];

        pinMode( p->_pin, p->_io_mode );
        digitalWrite( p->_pin, p->_high_low );
      }
    }

  private:
    static const int TOTAL_LED_OBJECTS = 2;
    static LED* leds_list[TOTAL_LED_OBJECTS];

    static LED _green_1_led;
    static LED _red_1_led;

};


LED LEDsManager::_green_1_led = LED( 13, LED::GREEN_LED, OUTPUT, HIGH );
LED LEDsManager::_red_1_led = LED( 7, LED::RED_LED, OUTPUT, LOW );

LED* LEDsManager::leds_list[TOTAL_LED_OBJECTS] = {
  &_green_1_led,
  &_red_1_led
};




/**

*/

class State
{
};

class RunWithDisplayState : public State
{
};

class StateManager
{
};







/*
   Main



*/


SensorsManager g_sensors_mngr;
LEDsManager g_leds_mngr;




void setup()
{
  Serial.begin(9600);

  g_leds_mngr.initialize();
  g_sensors_mngr.initialize();

}


void loop()

{
  g_sensors_mngr.update();

  g_sensors_mngr.printSerial();
  g_sensors_mngr.printSensorToLCD();

  delay(10);
}


