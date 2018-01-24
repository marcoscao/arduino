#ifndef ILED_H__
#define ILED_H__

namespace ms 
{

class ILed : public IDevice
{
  public:
	 ILed( int pin )
	 : _pin( pin )
	 {
	 }

    void activate( ) 
	 { 
		 isDigital() ? digitalWrite( getPin(), HIGH ) : analogWrite( getPin(), HIGH ) 
	 	_is_active = true;
	 } 

    void deActivate( ) 
	 { 
		 isDigital() ? digitalWrite( getPin(), HIGH ) : analogWrite( getPin(), HIGH ) 
	 	_is_active = false;
	 } 

    bool isActive() const { return _is_active; }

  private:
    bool _is_active;

};

}

#endif


