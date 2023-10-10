/*									Workshop 4 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds
{
	class CheeseShop
	{
		std::string m_shopName{};
		unsigned m_cheeseNum{};
		const Cheese** m_Cheese{};	//Dynamically allocated array of dynamically allocated cheeses

	public:
		CheeseShop();
		CheeseShop(const std::string& name);
		CheeseShop& addCheese(const Cheese& addCheese);
		/// <summary>
		/// rats ate all the cheese
		/// </summary>
		void emptyShop();
		/// <summary>
		/// have you got any cheese?
		/// </summary>
		operator bool() const;

		std::ostream& print(std::ostream& os) const;

		//rule of 5
		CheeseShop(const CheeseShop& copy);
		CheeseShop(CheeseShop&& move) noexcept;
		CheeseShop& operator=(const CheeseShop& copy);
		CheeseShop& operator=(CheeseShop&& move) noexcept;
		~CheeseShop();

	};
	std::ostream& operator<<(std::ostream& os, const CheeseShop& cshop);

}
#endif // !SDDS_CHEESESHOP_H