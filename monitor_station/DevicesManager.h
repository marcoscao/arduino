#ifndef MS_DEVICESMANAGER_H__
#define MS_DEVICESMANAGER_H__

#include "IManager.h"

namespace ms
{

class DevicesManager : public IManager
{
	public:
   	DevicesManager( const int total )
		: 	IManager( total )
    	{
    	}

	private:
		virtual void _do_initialize( IDevice* p )
		{
			if(not p )
			{
				return;
			}

			p->initialize();
		}

		virtual void _do_uninitialize( IDevice* p )
		{
			if(not p )
			{
				return;
			}

			p->uninitialize();
		}

		virtual void _do_activate( IDevice* p )
		{
			p->activate();
		}

		virtual void _do_deactivate( IDevice* p )
		{
			p->deactivate();
		}

		virtual void _do_update( IDevice* p )
		{
			if(not p )
			{
				return;
			}

			p->update();

		}

		virtual void _do_debug_print( IDevice* p )
		{
			p->debugPrint();
		}

};

}

#endif


