/**
 * SensorValues
 *
 */

#ifndef MS_SENSOR_VALUES_H__
#define MS_SENSOR_VALUES_H__


namespace ms
{
  struct sensor_values
  {
    bool is_low_alert;
    bool is_high_alert;

    float current;
    float hist_min;
    float hist_max;
    float low_alert;
    float high_alert;


    sensor_values( float a_low_alert, float a_high_alert )
    : is_low_alert(false),
      is_high_alert(false),
      current(-9999.0),
      hist_min( 99999.0),
      hist_max( -99999.0 ),
      low_alert( a_low_alert ),
      high_alert( a_high_alert ),
		_has_changes(false)
      {
        
      }

    void setCurrentValue( float v )
    {	
		 _has_changes = false;

		 if( current != v )
		 {	 
			_has_changes=true;
      	current = v;
      	adjustValues();
		 }
    }

	bool hasChanges() const
	{
		return _has_changes;
	}		

    bool operator!=( const sensor_values & r ) const
    {
      return current != r.current || hist_min != r.hist_min || hist_max != r.hist_max
        || low_alert != r.low_alert || high_alert != r.high_alert 
        || is_low_alert != r.is_low_alert || is_high_alert != r.is_high_alert; 
    }


private:
	 bool _has_changes;

    void adjustValues()
    {       
        if( current < hist_min )
          hist_min = current;

        if( current > hist_max )
           hist_max = current;

        is_low_alert = current < low_alert;
        is_high_alert = current > high_alert;
    }

  };


} // end namespace

#endif


