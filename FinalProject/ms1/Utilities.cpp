// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include "Utilities.h"

using namespace std; 

namespace sdds 
{
	char Utilities::m_delimiter = ' ';


	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth; 
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField; 
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string result = ""; 
		size_t firstPos = next_pos; 

		next_pos = str.find(m_delimiter, firstPos); 
		
		if (firstPos == next_pos)
		{
			more = false; 
			throw "   ERROR: No token.\n";
		}
		else if (next_pos == std::string::npos)
		{
			more = false;
			result = result.substr(firstPos); 
			m_widthField = std::max(result.length(), m_widthField); 
		}
		else
		{
			more = true; 
			result = result.substr(firstPos, next_pos - firstPos);
			m_widthField = std::max(result.length(), m_widthField); 
		}
		next_pos++; 
		return result; 
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter; 
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter; 
	}
}