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
#include "CheeseShop.h"

using namespace sdds;
using namespace std; 

sdds::CheeseShop::CheeseShop()
{
	m_shopName = "No Name";
	m_cheeseNum = 0u;
	m_Cheese = nullptr;
}

CheeseShop::CheeseShop(const string& name)
{
	m_shopName = name;
	m_cheeseNum = 0u;
	m_Cheese = nullptr;
}

CheeseShop& sdds::CheeseShop::addCheese(const Cheese& addCheese)
{

	//creating a new array thats 1 bigger
	const Cheese** newCheese = new const Cheese * [m_cheeseNum + 1];

	//copying from old array to new
	for (size_t i = 0; i < m_cheeseNum; i++)
	{
		newCheese[i] = m_Cheese[i];
	}

	//adding the new one to new array
	newCheese[m_cheeseNum] = new Cheese(addCheese);

	//clearing current collection before taking new address
	delete[] m_Cheese;
	//moving the address of the new array to member
	m_Cheese = newCheese;
	m_cheeseNum++;

	return *this;
}

void sdds::CheeseShop::emptyShop()
{
	if (*this)
	{
		for (size_t i = 0; i < m_cheeseNum; i++)
		{
			delete m_Cheese[i];
			m_Cheese[i] = nullptr;
		}
	}
	m_shopName = "";
	m_cheeseNum = 0u;
	delete[] m_Cheese;
	m_Cheese = nullptr;
}

sdds::CheeseShop::operator bool() const
{
	return m_Cheese != nullptr;
}

std::ostream& sdds::CheeseShop::print(std::ostream& os) const
{
	os << "--------------------------" << endl
		<< m_shopName << endl
		<< "--------------------------" << endl;

	if (*this)
	{
		for (size_t i = 0; i < m_cheeseNum; i++)
		{
			os << *(m_Cheese[i]);
		}
		os << "--------------------------" << endl;
	}
	else
	{
		os << "This shop is out of cheese!" << endl
			<< "--------------------------" << endl;
	}
	return os;
}

sdds::CheeseShop::CheeseShop(const CheeseShop& copy)
{
	*this = copy;
}

sdds::CheeseShop::CheeseShop(CheeseShop&& move) noexcept
{
	*this = std::move(move);
}

CheeseShop& sdds::CheeseShop::operator=(const CheeseShop& copy)
{
	if (this != &copy)
	{
		for (size_t i = 0u; i < m_cheeseNum; i++)
		{
			delete m_Cheese[i];
		}
		delete[] m_Cheese;

		m_shopName = copy.m_shopName;
		m_cheeseNum = copy.m_cheeseNum;
		m_Cheese = new const Cheese * [m_cheeseNum];

		for (size_t i = 0; i < m_cheeseNum; i++)
		{
			m_Cheese[i] = new Cheese{ *(copy.m_Cheese[i]) };
		}
	}

	return *this;
}

CheeseShop& sdds::CheeseShop::operator=(CheeseShop&& move) noexcept
{
	if (this != &move)
	{
		emptyShop();
		//take everything
		m_shopName = move.m_shopName;
		m_cheeseNum = move.m_cheeseNum;
		m_Cheese = move.m_Cheese;
		//leave nothing behind
		move.m_Cheese = nullptr;
		move.m_shopName = "";
		move.m_cheeseNum = 0u;
	}

	return *this;
}

sdds::CheeseShop::~CheeseShop()
{
	emptyShop();
}

std::ostream& sdds::operator<<(std::ostream& os, const CheeseShop& cshop)
{
	return cshop.print(os);
}