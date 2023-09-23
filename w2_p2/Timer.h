/*									Workshop 2 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/


#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>

namespace sdds
{
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> m_start{};
	public:
		void start();
		long long int stop();
	};

}

#endif // !SDDS_TIMER_H