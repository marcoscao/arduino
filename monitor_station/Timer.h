#ifndef MS_TIMER_H__
#define MS_TIMER_H__

namespace ms
{
	class Timer
	{
	public:
		enum TimerMode
		{
			TIMER_ENDLESS = 0,
			TIMER_ONCE = 1
		};

		Timer( unsigned long total_t = 1000, TimerMode tm = TIMER_ENDLESS );

		void start();

		void stop();

		bool isTime();

	private:
		bool _active;
		TimerMode _mode;
		unsigned long _total_t;
		unsigned long _prev_t;
	};

}

#endif

