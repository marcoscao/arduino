/*
 * Microfono WODE E087
 */
#include <Servo.h>

const int MIC_APIN = A0;
const int MIC_DPIN = 3;
const int VIB_DPIN = 4;

Servo g_servo;  
 
void setup() 
{
  pinMode( MIC_APIN, INPUT );
  pinMode( VIB_DPIN, INPUT );

  // Pin 3 --> Servo motor
  g_servo.attach(5);
  
  for(int i=10; i < 290; i+=10 )
  { 
    g_servo.write( i );
    delay(300);
  }

 
  Serial.begin(9600);
}

void loop() 
{
//  int v = analogRead( MIC_APIN );
//  int v2 = map( v, 0, 1023, 0, 100 );

  int vib = digitalRead( VIB_DPIN );
  
//  Serial.print( "v: " );
//  Serial.println( v );
//
//  Serial.print( "v2: " );
//  Serial.println( v2 );

//  Serial.print( "*** SHOCK: " );
  if( vib == HIGH )
    Serial.println( "HIGH. EARTHQUAKE ########################################### " );
//  else
//    Serial.println( "LOW" );


//
//  for(int i=10; i < 290; i+=10 )
//  { 
//    g_servo.write( i );
//    delay(300);
//  }
//
//
//  delay(2000);
  
}
