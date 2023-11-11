// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <string>
#include <vector>
#include <list>


namespace sdds
{
	const size_t EPIDEMIC_DEATHS = 300;
	const size_t EARLY_DEATHS = 50;

	struct Covid
	{
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		int m_year{};
		size_t m_cases{};
		size_t m_deaths{};
		std::string m_severity{ "General" };
	};

	class CovidCollection
	{
		std::vector<Covid> m_coll{};

		void trimString(std::string& source);
	public:
		CovidCollection() = default;
		CovidCollection(const char* fileName);
		//part 2
		void display(std::ostream& out, const std::string& country = "ALL") const;
		void sort(const std::string& field = "country");
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
		std::list<Covid> getListForDeaths(unsigned int deaths) const;
		void updateStatus();
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

}

#endif // !SDDS_COVIDCOLLECTION_H