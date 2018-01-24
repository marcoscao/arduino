#ifndef IMANAGER_H__
#define IMANAGER_H__

#include "IDevice.h"

namespace ms
{

class IManager
{
	typedef void (IManager::*OperationFn)(IDevice*);

	public:
	IManager( IDevice** a_objects, int total )
	: 	_total(total),
		_objects( a_objects ),
		_curr_add(0)
	{
   }

	IManager( int total )
	: 	_total(total),
		_objects( new IDevice*[total] )
	{

   }

	~IManager()
	{
		delete[] _objects;
	}

	int addObject( IDevice* p )
	{
		int index = _curr_add;

		_objects[index] = p;

		if( ++_curr_add == _total )
			_curr_add--;

		return index;
	}

	IDevice* getObject( unsigned int index )
	{
		if( index >= _total )
			return 0;

		return _objects[ index ];
	}

	int getTotalObjects() const
	{
		return _total;
	}

	void initialize()
    {
	 	iterate( &IManager::_do_initialize );
	 }

	void uninitialize()
   {
		iterate( &IManager::_do_uninitialize );
	}

	void activate()
    {
	 	iterate( &IManager::_do_activate );
	 }

	void deactivate()
   {
		iterate( &IManager::_do_deactivate );
	}

	void update()
   {
		iterate( &IManager::_do_update );
	}

	void debugPrint()
   {
		iterate( &IManager::_do_debug_print );
	}


private:

	virtual void _do_initialize( IDevice* p ) = 0;

	virtual void _do_uninitialize( IDevice* p ) = 0;

	virtual void _do_activate( IDevice* p ) = 0;

	virtual void _do_deactivate( IDevice* p ) = 0;

	virtual void _do_update( IDevice* p ) = 0;

	virtual void _do_debug_print( IDevice* p ) 
	{
		;
	}


private:
	const int _total;
	IDevice** _objects;
	int _curr_add;


	void iterate( OperationFn op_fn )
   {
      for (int i = 0; i < _total; ++i )
      {
		  (*this.*op_fn)( _objects[i] );
		}
    }

};

}

#endif


