// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <string>
#include <algorithm>
#include"Station.h"
#include "Utilities.h"

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& line)
	{
		m_id = ++Station::id_generator;
		Utilities utils;
		bool more = true;
		size_t pos = 0;
		auto whiteSpace = [](const std::string str)
			{
				size_t start = str.find_first_not_of(" \t");
				size_t end = str.find_last_not_of(" \t");
				return str.substr(start, end - start + 1);
			};

		try
		{
			m_name = utils.extractToken(line, pos, more);
			m_name = whiteSpace(m_name);
			m_serialNum = std::stoi(utils.extractToken(line, pos, more));
			m_currStock = std::stoi(utils.extractToken(line, pos, more));
			Station::m_widthField = std::max(utils.getFieldWidth(), Station::m_widthField);
			m_desce = utils.extractToken(line, pos, more);
			m_desce = whiteSpace(m_desce);
		}
		catch (std::string err)
		{
			std::cout << err;
		}
	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		++m_serialNum;
		return m_serialNum - 1;
	}

	size_t Station::getQuantity() const
	{
		return m_currStock;
	}

	void Station::updateQuantity()
	{
		if (m_currStock > 0) 
		{
			--m_currStock;
		}
		else {
			m_currStock = 0;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << std::right << std::setw(3) << std::setfill('0') << m_id << " | ";
		os << std::left << std::setw(Station::m_widthField) << std::setfill(' ') << m_name;
		os << "| " << std::right << std::setw(6) << std::setfill('0') << m_serialNum << " | ";

		if (full)
		{
			os << std::right << std::setw(4) << std::setfill(' ') << m_currStock << " | ";
			os << std::left << m_desce << std::endl;
		}
		else
		{

			os << std::endl;
		}
	}

}