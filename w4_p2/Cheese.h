/*									Workshop 4 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds
{
	class Cheese
	{
		std::string m_name;
		unsigned m_weight;
		double m_price;
		std::string m_features;
	public:
		Cheese();
		Cheese(const std::string& details);
		Cheese(const Cheese& copy) = default;
		/// <summary>
		/// attempts to slice the cheese
		/// </summary>
		/// <param name="weight">It's not much of a cheese shop is it?</param>
		/// <returns>some cheese</returns>
		Cheese slice(const size_t weight);
		/// <summary>
		/// output cheese properties
		/// </summary>
		/// <param name="out">where to print cheese</param>
		/// <returns>same as received</returns>
		std::ostream& printCheese(std::ostream& out) const;

		std::string getName() const;
		unsigned getWeight() const;
		double getPrice() const;
		std::string getFeatures() const;
	};

	/// <summary>
	/// insertion operator that just calls the printCheese function
	/// </summary>
	/// <param name="cheesy">what to print</param>
	/// <param name="out">WHERE to print</param>
	/// <returns>same ostream</returns>
	std::ostream& operator<<(std::ostream& out, const Cheese& cheesy);

	/// <summary>
	/// cut a strings trailing and following spaces
	/// </summary>
	/// <param name="str">what to trim</param>
	/// <returns>trimmed string</returns>
	std::string cutSpaces(std::string str);
}
#endif // !SDDS_CHEESE_H
