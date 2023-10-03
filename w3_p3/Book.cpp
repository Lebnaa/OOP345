/*									Workshop 3 Part 2
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
#include <sstream>
#include "Book.h"

using namespace std; 
namespace sdds 
{

	//initilize memebrs 
	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
		: m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}


	//checks is book is empty 
	bool Book::isEmpty() const
	{
		bool result = true;
		if (m_title.empty() || m_numChapters == 0 || m_numPages == 0)
		{
			result = true;
		}

		return result;
	}

	Book::operator bool() const
	{
		return m_title.length();
	}

	//part 2 
	bool Book::operator<(const Book& other) const
	{
		return ((double)m_numPages / m_numChapters) < ((double)other.m_numPages / other.m_numChapters);
	}

	bool Book::operator>(const Book& other) const
	{
		return ((double)m_numPages / m_numChapters) > ((double)other.m_numPages / other.m_numChapters);
	}

	std::ostream& Book::print(std::ostream& os) const
	{
		//if obj in good state print its data
		if (*this)
		{	
			stringstream ss;
			ss << m_title << "," << m_numChapters << "," << m_numPages << " | (";
			os << setw(60) << setiosflags(ios::right) << ss.str();
			os << setprecision(6) << resetiosflags(ios::right)
				<< setiosflags(ios::left) << setiosflags(ios::fixed)
				<< ((double)m_numPages / m_numChapters) << ")    ";
			os << resetiosflags(ios::fixed);
		}
		else {
			os << "| Invalid book data";
		}

		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Book& bk)
	{
		// TODO: insert return statement here
		return bk.print(os);
	}
}
