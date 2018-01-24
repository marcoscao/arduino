#include "Log.h"
//#include "RTC_DS1302.h"
// #include "WString.h"
//#include <Time.h>
#include <TimeLib.h>
#include <Arduino.h>            // needed to avoid 'Serial' undefined error 

namespace ms
{
      
       ms::Log & Log::get() 
      {
        static ms::Log l;
        return l;
      }

//      
//      void setRTC( ms::RTC_DS1302 * rtc )
//      {
//        _rtc = rtc;
//      }
//
//      RTC_DS1302 * rtc() 
//      {
//        return _rtc;
//      }

      bool Log::hasRTC()
      {
        return _rtc;
      }

     String Log::dateTimeStr()
     {
      if( hasRTC() )
        return _dateTimeStrRTC();

      return _dateTimeStr();
     }
      

  
	  Log::Log()
      : _rtc(0)
      {      
      }

     String Log::_dateTimeStr()
     {
        String dt( year()  );
        dt = dt + "-" + month() + "-" + day() + " " + hour() + ":" + minute() + ":" + second();
        return dt;
     }

    String Log::_dateTimeStrRTC()
    {
      //return _rtc->time();
      return "NULL";
    }

  
  
	void LOG( const String & section, const String & desc, const String & val1 )
	{
    	ms::Log & log = Log::get();
                
		String s( log.dateTimeStr() + " [" + section + "] " + desc );
    
	  if( val1.length() )
	  {
	  		s = s + "'" + val1 + "'";
	  }

	  Serial.println( s );
	}


}




