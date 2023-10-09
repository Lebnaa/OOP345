/*									Workshop 4 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include "Cheese.h"

namespace sdds
{
	class CheeseParty
	{
		const Cheese** m_pCheeses{};
		unsigned m_numCheeses{};
	public:
		CheeseParty() = default;

		void emptyParty();
		operator bool();

		/// <summary>
		/// removes a cheese by index and shrinks m_pCheeses accordingly
		/// </summary>
		/// <param name="index"></param>
		void removeCheeseAndShrink(const unsigned index);

		std::ostream& print(std::ostream& os) const;

		/// <summary>
		/// return first index of empty cheese, otherwise -1
		/// </summary>
		/// <returns>index of empty cheese or -1</returns>
		int findEmptyCheese();

		//rule of 5
		CheeseParty(const CheeseParty& copy);
		CheeseParty(CheeseParty&& move) noexcept;
		CheeseParty& operator=(const CheeseParty& copy);
		CheeseParty& operator=(CheeseParty&& move) noexcept;
		~CheeseParty();

		CheeseParty& addCheese(const Cheese& newCheese);
		CheeseParty& removeCheese();
	};

	std::ostream& operator<<(std::ostream& os, const CheeseParty& cparty);
}

#endif // !SDDS_CHEESEPARTY_H	