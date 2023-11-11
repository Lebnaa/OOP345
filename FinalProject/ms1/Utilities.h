// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds
{
	class Utilities {
		size_t m_widthField = 1; 
		static char m_delimiter; 
	public:
		//member functions 
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;

		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		//member funcs 
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

	};
}
#endif // !SDDS_UTILITIES_H
	