
// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <string>
#include"Station.h"
#include "Utilities.h"

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;


	Station::Station(const std::string& line)
	{
		m_id = ++Station::id_generator;
		Utilities utils; 
		bool result = true; 
		size_t pos{}; 

		/*auto WhiteSpace = [](const std::string& something)
			{
				size_t start = something.find_first_not_of(" \t");
				size_t end = something.find_last_not_of(" \t");
				return something.substr(start, end - start + 1);
			}; */
		
			m_name = utils.extractToken(line, pos, result); 
			//m_name = WhiteSpace(m_name); 
			m_serialNum = std::stoi(utils.extractToken(line, pos, result)); 
			m_currStock = std::stoi(utils.extractToken(line, pos, result)); 
			Station::m_widthField = std::max(utils.getFieldWidth(), Station::m_widthField); 
			m_desce = utils.extractToken(line, pos, result); 
			m_desce = WhiteSpace(m_desce); 
	}

	const std::string& Station::getItemName() const
	{
		// TODO: insert return statement here
		return m_name; 
	}

	size_t Station::getNextSerialNumber()
	{
		// ++m_serialNum; 
		 return m_serialNum++; 
	}

	size_t Station::getQuantity() const
	{
		return m_currStock; 
	}

	void Station::updateQuantity()
	{
		if (m_currStock < 0) 
		{
			--m_currStock;
		}
		else 
		{
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
			//os << m_id <<   " |" << m_name  << " |" << m_serialNum << " |"; 
			os << std::right << std::setw(4) << std::setfill(' ') << m_currStock << " | "
				<< std::left << m_desce << std::endl; 
		}
		else
		{
			/*os << m_id << std::setw(3) << " |" << m_name << std::setw(m_widthField) << " |" << m_serialNum << std::setw(6) << 
				" |" << m_currStock << std::setw(4) <<  " |" << m_desce << std::endl;*/
			os << std::endl; 
		}
	}
}