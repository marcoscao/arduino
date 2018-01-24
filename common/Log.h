#ifndef MS_LOG_H__
#define MS_LOG_H__

//#include "RTC_DS1302.h"
#include "WString.h"

class String;

namespace ms
{

  class Log
  {
    public:
      
      static ms::Log & get();

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

      bool hasRTC();

     String dateTimeStr();
      

   private:
      //ms::RTC_DS1302 * _rtc;
      void * _rtc;
  
      Log();

     String _dateTimeStr();

    String _dateTimeStrRTC();
  };


  
	void LOG( const String & section, const String & desc = String(), const String & val1 = String() );

}

#endif



