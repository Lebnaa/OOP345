// Name: Lebna Noori
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds
{
	class Station
	{
		int m_id{};
		std::string m_name{};
		std::string m_desce{};
		size_t m_serialNum{};
		size_t m_currStock{};

		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& line);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H