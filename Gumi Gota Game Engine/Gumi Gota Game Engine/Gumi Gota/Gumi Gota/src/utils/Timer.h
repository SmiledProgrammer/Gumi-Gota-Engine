#ifndef GUMIGOTA_TIMER_H
#define GUMIGOTA_TIMER_H



namespace gg
{

	class Timer
	{
	private:
		/* Variables */
		double m_startTime;

	public:
		/* Constructors */
		Timer();

		/* Functions */
		void reset();

		float elapsed() const;

	};

}



#endif