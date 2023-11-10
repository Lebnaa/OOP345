#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <iostream>
#include <vector>
#include <list>
#include <string>

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
		size_t m_recovered{};
		std::string m_severity_status{ "General" };

		/*void print() const {
			std::cout << std::setw(8) << std::left << m_city << ": "
				<< "Cases - " << m_cases << ", Deaths - " << m_deaths << ", Recovered - " << m_recovered << ", Severity - " << std::setw(8) << severity_status << std::endl;
		}*/

	};

	class CovidCollection
	{
		std::vector<Covid> covidRecords;
		void trimString(std::string& source);
	public:
		CovidCollection() = default;
		CovidCollection(const char* filename);
		void display(std::ostream& out) const;

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
