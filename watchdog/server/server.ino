/*
	Different working modes.

	Main working modes:

	0 : sleep, no reaction to clients signals
	1 : alert, waiting for client signals to perform actions
	2 : attend, attending a client alert
	3 : check, checking environment and systems
	

	Hardware:

	WM Led				: attached to pin 13
	WM Led Resistence	: 330 Ohm
	
*/

#define WM_SLEEP 0
#define WM_ALERT 1
#define WM_ATTEND 2
#define WM_CHECK 3

#define LED_WM_PIN 13

#define LED_BLINK_SLOW 3000
#define LED_BLINK_FAST 900

int g_wm = WM_ALERT;

bool g_led_wm_blink_onoff = false;
unsigned long g_led_wm_blink_prev_t = 0;



void _blink_led_wm( unsigned long wait_t )
{
	unsigned long curr_t = millis();
	
	if( curr_t - g_led_wm_blink_prev_t >= wait_t )
	{
		g_led_wm_blink_prev_t = curr_t;
		g_led_wm_blink_onoff = !g_led_wm_blink_onoff;

		digitalWrite( LED_WM_PIN, g_led_wm_blink_onoff );
	}

}


void _set_wm_sleep()
{
	g_wm = WM_SLEEP;
	digitalWrite( LED_WM_PIN, LOW );
}

void _set_wm_alert()
{
	g_wm = WM_ALERT;
	g_led_wm_blink_onoff = true;
	g_led_wm_blink_prev_t = 0;
	digitalWrite( LED_WM_PIN, HIGH );
}

void _set_wm_attend()
{
	g_wm = WM_ATTEND;
	g_led_wm_blink_onoff = true;
	g_led_wm_blink_prev_t = 0;
	digitalWrite( LED_WM_PIN, HIGH );
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


void setup()
{
  	pinMode( LED_WM, OUTPUT );

	set_wm( g_wm );
}

void loop()
{
	loop_wm();
}


/*
#include <Servo.h>
#include <IRremote.h>

#define Echo A4
#define Trig A5

#define MOTOR_PWM_1 5
#define MOTOR_PWM_2 11

#define MOTOR_CTL_1 6    // I1
#define MOTOR_CTL_2 7    // I2
#define MOTOR_CTL_3 8    // I3
#define MOTOR_CTL_4 9    // I4

// IR control values
#define A 16736925
#define B 16754775
#define X 16712445
#define C 16720605
#define D 16761405
#define E 5316027
#define F2 2747854299
#define Y 3622325019
#define G 1386468383
#define H 553536955


const int MAIN_WORK_MODE = 1;





void setup()
{
}





const int IR_PIN = 12;

const int SPEED = 160;

const int MAX_READS = 25;
float g_reads[MAX_READS];
const int DISCARD_MAXMIN_VALUES = 2;     // discards series of max and min

const int COLLISION_DIST_1 = 60;
const int COLLISION_DIST_2 = 20;

int g_rot = 1;
unsigned long g_rot_delay_time = 200;
unsigned long g_rot_old_time = millis();

unsigned long g_stopped_time = 2000;
unsigned long g_stopped_old_time = 0;

unsigned long g_rectified_time = 2000;
unsigned long g_rectified_old_time = 0;

float g_old_dist = 0.0;
float g_dist_threshold = 2.0;

Servo myservo;  

//IRrecv g_ir( IR_PIN);
//decode_results g_ir_results;



int pos = 0;    

void go_forward()
{
  // forward
  
  digitalWrite(MOTOR_CTL_1,HIGH); 
  digitalWrite(MOTOR_CTL_2,LOW);
  digitalWrite(MOTOR_CTL_3,LOW); 
  digitalWrite(MOTOR_CTL_4,HIGH);
}

void go_back()
{
 analogWrite(MOTOR_PWM_1,100);
 analogWrite(MOTOR_PWM_2,100);
  digitalWrite(MOTOR_CTL_1,LOW);
  digitalWrite(MOTOR_CTL_2,HIGH);
  digitalWrite(MOTOR_CTL_3,HIGH);
  digitalWrite(MOTOR_CTL_4,LOW);
}

void go_left()
{
  analogWrite(MOTOR_PWM_1,120);
  analogWrite(MOTOR_PWM_2,120);
  digitalWrite(MOTOR_CTL_1,HIGH);
  digitalWrite(MOTOR_CTL_2,LOW);
  digitalWrite(MOTOR_CTL_3,HIGH);
  digitalWrite(MOTOR_CTL_4,LOW);
}

void go_right()
{
    analogWrite(MOTOR_PWM_1,120);
  analogWrite(MOTOR_PWM_2,120);
  digitalWrite(MOTOR_CTL_1,LOW);
  digitalWrite(MOTOR_CTL_2,HIGH);
  digitalWrite(MOTOR_CTL_3,LOW);
  digitalWrite(MOTOR_CTL_4,HIGH);
} 

void go_stop()
{
  digitalWrite(MOTOR_PWM_1,LOW);
  digitalWrite(MOTOR_PWM_2,LOW);
}

void setup() {

  // Pin 3 --> Servo motor
  myservo.attach(3);  

  // A4  --> Sensor Input   ( Echo )
  // A5  --> Sensor Output  ( Trig )
  pinMode( Echo, INPUT );
  pinMode( Trig, OUTPUT );

  // Motor speed
  pinMode(MOTOR_PWM_1,OUTPUT); 
  pinMode(MOTOR_PWM_2,OUTPUT); 

  pinMode(MOTOR_CTL_1,OUTPUT); 
  pinMode(MOTOR_CTL_2,OUTPUT); 
  pinMode(MOTOR_CTL_3,OUTPUT); 
  pinMode(MOTOR_CTL_4,OUTPUT); 

  // Speed
  analogWrite(MOTOR_PWM_1, SPEED );      // 0-255
  analogWrite(MOTOR_PWM_2, SPEED );      // 0-255

  // IR remote control
//  pinMode( IR_PIN,INPUT);
//  g_ir.enableIRIn();
  
  Serial.begin(9600);

  g_rectified_old_time = millis();

  move_servo_front();
  go_forward();
  
}



void move_servo_right()
{
   myservo.write( 0 );
}

void move_servo_right_45()
{
   myservo.write( 45 );
}

void move_servo_front()
{
   myservo.write( 80 );
}

void move_servo_left_45()
{
   myservo.write( 120 );
}

void move_servo_left()
{
   myservo.write( 160 );
}

float calculate_distance( int ntimes  )   
{
  if( ntimes >= MAX_READS )
    ntimes=MAX_READS;
  
  float d = 1.0;
  float max[DISCARD_MAXMIN_VALUES];  
  float min[DISCARD_MAXMIN_VALUES];
  int i = 0;

  for(int i = 0; i < DISCARD_MAXMIN_VALUES; ++i) max[i]=0.0;
  for(int i = 0; i < DISCARD_MAXMIN_VALUES; ++i) min[i]=500.0;
  
  
  for(int i=0; i < ntimes; ++i )
  {
    digitalWrite(Trig, LOW);   
    delayMicroseconds(20);
    digitalWrite(Trig, HIGH);  
    delayMicroseconds(20);
    digitalWrite(Trig, LOW);   
    delayMicroseconds(20);
    digitalWrite(Trig, HIGH);  
    delayMicroseconds(20);
  
    d = pulseIn(Echo, HIGH);  
    d = d / 58.0;

    float old = -99.0;
    for(int j = 0; j < DISCARD_MAXMIN_VALUES; ++j )
    { 
      if( old > max[j] )
      {
        float x = max[j];
        max[j]=old;
        old=x; 
      }

      if( old != -99.0 )
        continue;
      
      if( d > max[j] ) 
      {
        old = max[j];
        max[j] = d;
      }
      
    }

    old = 9999.0;
    for(int j = 0; j < DISCARD_MAXMIN_VALUES; ++j )
    {
      if( old < min[j] )
      {
        float x = min[j];
        min[j]=old;
        old=x;
      }

      if( old != 9999.0 )
        continue;
        
      if( d < min[j] ) 
      {
        old = min[j];
        min[j] = d;
      }
    }    

    g_reads[i] = d;            
    
//    Serial.println( d );
  }

  // Debug
  for( int j = 0; j < DISCARD_MAXMIN_VALUES; ++j )
  {
    Serial.print("Max ");
    Serial.print( j );
    Serial.print( " : " );
    Serial.print( max[j] );

    Serial.print( "  |  " );
    Serial.print("Min ");
    Serial.print( j );
    Serial.print( " : " );
    Serial.print( min[j] );

    Serial.println();
  }

  // discards max an min values

  float tot_dist = 0.0;
  int total_be_discarded = DISCARD_MAXMIN_VALUES * 2;
  
  for( int i = 0; i < ntimes; ++i )
  {
    bool add = true;

    if( total_be_discarded )
    {
      for(int j = 0; j < DISCARD_MAXMIN_VALUES; ++j )
      {
        if( g_reads[i] == max[j] || g_reads[i] == min[j] )
        {
          add=false;
          total_be_discarded--;
          break;
        }
      }
    }
    
    if( add )
    {
//      Serial.print("Adding: ");
//      Serial.println( g_reads[i] );

       tot_dist += g_reads[i];           
    }
    
  }

    Serial.println();
    Serial.print("Total Dist: ");
    Serial.println( tot_dist );
    Serial.print("total items: ");
    Serial.println( ntimes - (DISCARD_MAXMIN_VALUES*2) );

  return tot_dist / ( ntimes - (DISCARD_MAXMIN_VALUES*2) );
}  



float escape_dist( int dir )
{
  switch( dir )
  { 
    //case 0 : move_servo_right_45(); break;
    case 0 : move_servo_right(); break;
    //case 2 : move_servo_left_45(); break;
    case 1 : move_servo_left(); break;
  }

  delay(1000);
  return calculate_distance( MAX_READS );
}


int g_better_dist = 0.0;


//void process_ir() {
//  if (not g_ir.decode(&g_ir_results))
//    return;
//    
//  unsigned long v=g_ir_results.value;
//  Serial.println(v);
//  g_ir.resume();
//  delay(150);
//
//  switch( v )
//  {
//    case A :
//    case E : 
//      go_forward(); 
//      break;
//      
//    case B : 
//    case F2 :
//      go_back(); 
//      break;
//      
//    case C : 
//    case G : 
//      go_left(); 
//      break;
//    
//    case D : 
//    case H : 
//      go_right(); 
//      break;
//
//    case X :
//    case Y : 
//       go_stop();
//       break;
//  }
//  
//} 
//

void loop()
{

  //process_ir();
  //return;

  if( (millis() - g_rectified_old_time ) > g_rectified_time )
  {
    go_left();
    delay(90);
    go_forward();
    g_rectified_old_time = millis();   
  }
  
//  go_forward();
//   
//  switch( g_rot )
//  { 
//      case 0 : move_servo_left_45(); break;
//      case 1 : move_servo_front(); break;
//      case 2 : move_servo_right_45(); break;
//      case 3 : move_servo_front(); break;
//  }

  
  float d1 = calculate_distance( MAX_READS );

  Serial.println("");
  Serial.print( "* d1: " );
  Serial.println( d1 );
  Serial.print( "* g_old_dist: " );
  Serial.println( g_old_dist );
  Serial.print( "* g_stopped_old_time: " );
  Serial.println( g_stopped_old_time );
  
//  Serial.print( "* g_old_d1 + threshold: " );
//  Serial.println( g_old_dist + g_dist_threshold );
  

  if( (d1 <= ( g_old_dist + g_dist_threshold ) )
  && ( d1 >= ( g_old_dist - g_dist_threshold ) ) )
  {
//    Serial.println( "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" );
//    Serial.println( "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" );
        
    if( not g_stopped_old_time )
      g_stopped_old_time = millis();     
  }
//  else
//    g_stopped_old_time = 0;

  g_old_dist = d1;

//  Serial.print( "************* g_old_d1: " );
//  Serial.println( g_old_dist );
//  Serial.print( "************* g_old_d1 + threshold: " );
//  Serial.println( g_old_dist + g_dist_threshold );
// 
  Serial.print( "************* g_stopped_old_time: " );
  Serial.println( g_stopped_old_time );

  if( g_stopped_old_time )
  {
    unsigned long curr = millis();
    if( (curr - g_stopped_old_time ) > g_stopped_time )
    {
      d1 = COLLISION_DIST_1 - 5; 
      g_stopped_old_time = 0;
    }
  }
  
  Serial.println("");
  Serial.print( "Final distance: " );
  Serial.println( d1 );
  Serial.println( "--------------------------------------------------------------------------------------------" );

  
  if( d1 < COLLISION_DIST_1 ) {
    
    go_stop();
    delay(100 );

    int back_time = 700;
    int dir_time = 1000;
    int dir = 1;
    bool escape = false;

    
    while( not escape )
    {
      float max_escape_dist = 0.0;
      int escape_dir = 99;
      
      for(int i = 0; i < 2; ++i )
      {
        float d = escape_dist(i);
        if( d > max_escape_dist )
        {
          escape_dir = i;           
        }
      }

      g_old_dist = max_escape_dist;

      switch( escape_dir )
      {
        // could escape 45º right?
//        case 0: 
//        {
//          back_time = 800;
//          dir_time = 400;
//          dir = 0;
//          break;
//        }

        // could escape right?
        case 0:
        {
          back_time = 900;
          dir_time = 600;
          dir = 0;
          break;
        }

        // could escape 45º left?
//        case 2:
//        {
//          back_time = 800;
//          dir_time = 400;
//          dir = 1;
//          break;
//        }

        // could escape left?
        case 1:
        {
          back_time = 900;
          dir_time = 600;
          dir = 1;
          break;
        }
      
      } // end switch
      
      if( escape_dir != 99 )
        break;
      
        // Go back a bit to try another way to escape
        go_back();
        delay( 700 );
        go_stop();
            
    }

    move_servo_front();
    
    go_back();
    delay( back_time );

    if( dir )
    {
      //move_servo_right_45();
      go_right();
    }
    else
    {
      //move_servo_right_45();
      go_left();
    }
     
    delay( dir_time);    
    move_servo_front();

    g_rot = 1;
    g_rot_old_time = millis();
    g_rectified_old_time = millis();

    go_forward();
  }
  else
  {
    
//    if( d1 > g_better_dist )
//    {
//      g_better_dist = d1;
//      switch( g_rot )
//      {  
//        case 0 : go_left(); break;
//        //case 1 : go_forwardt(); break;
//        case 2 : go_right(); break;
//        //case 3 : move_servo_front(); break;
//      }
//      
//      delay(100);
//      go_forward();
//    }
//  
//
//    unsigned long curr_time = millis();
//    if( (curr_time - g_rot_old_time) > g_rot_delay_time )
//    {  
//      if( ++g_rot > 3 )
//        g_rot = 0;
//
//      g_rot_old_time = curr_time;
//    }
//  
   }
   
  Serial.println( "---" );
  
  //delay(500);
    
}

*/


