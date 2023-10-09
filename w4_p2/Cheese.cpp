/*									Workshop 4 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "Cheese.h"

using namespace std;
using namespace sdds;

sdds::Cheese::Cheese() : m_weight{}, m_price{}, m_features{}
{
	m_name = "NaC";
}

sdds::Cheese::Cheese(const std::string& details)
{
	string temp{};
	string copy = details;
	size_t delim{};

	//get cheese name
	delim = copy.find_first_of(',');
	temp = copy.substr(0, delim);
	m_name = cutSpaces(temp);

	copy.erase(0, delim + 1);

	//get cheese weights
	delim = copy.find_first_of(',');
	temp = copy.substr(0, delim);
	temp = cutSpaces(temp);
	m_weight = stoul(temp);

	copy.erase(0, delim + 1);

	//get cheese price
	delim = copy.find_first_of(',');
	temp = copy.substr(0, delim);
	temp = cutSpaces(temp);
	m_price = stod(temp);

	copy.erase(0, delim + 1);

	//get cheese features
	temp = "";
	while (copy.length())
	{
		delim = copy.find_first_of(',');
		if (delim < copy.length())
		{
			temp += cutSpaces(copy.substr(0, delim)) += " ";
			copy.erase(0, delim + 1);
		}
		else
		{
			temp += cutSpaces(copy.substr(0, copy.length()));
			copy = "";
		}
	}
	m_features = temp;
}

Cheese sdds::Cheese::slice(const size_t weight)
{
	if (weight <= m_weight)
	{
		Cheese slice = *this;
		slice.m_weight = weight;
		m_weight -= weight;
		return slice;
	}
	else
	{
		return Cheese();
	}
}

std::ostream& sdds::Cheese::printCheese(std::ostream& out) const
{
	out << "|" << setiosflags(ios::left) << setw(21) << m_name
		<< "|" << setw(5) << m_weight
		<< "|" << setw(5) << setiosflags(ios::fixed) << setprecision(2) << m_price
		<< "|" << setw(33) << setiosflags(ios::right) << m_features
		<< " |" << resetiosflags(ios::right) << endl;
	return out;
}

std::string sdds::Cheese::getName() const
{
	return m_name;
}

unsigned sdds::Cheese::getWeight() const
{
	return m_weight;
}

double sdds::Cheese::getPrice() const
{
	return m_price;
}

std::string sdds::Cheese::getFeatures() const
{
	return m_features;
}

std::ostream& sdds::operator<<(std::ostream& out, const Cheese& cheesy)
{
	return cheesy.printCheese(out);
}

std::string sdds::cutSpaces(std::string str)
{
	unsigned i = 0;

	//erasing trailing spaces
	while (isspace(str[i]) && i < str.length())
		i++;

	str = str.erase(0, i);

	//erasing following spaces
	i = 0;
	while (!(isspace(str[i]) && isspace(str[i + 1])) && i < str.length())
		i++;

	str = str.erase(i, str.length());

	return str;
}