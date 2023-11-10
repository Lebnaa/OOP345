#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include "CovidCollection.h"

using namespace std;

namespace sdds
{
	void CovidCollection::trimString(std::string& source)
	{
		size_t begin = source.find_first_not_of(" \t\n");
		size_t end = source.find_last_not_of(" \t\n");
		string resutl{};
		if (begin != string::npos && end != string::npos)
		{
			resutl = source.substr(begin, end - begin + 1);
		}
		else
		{
			resutl = "";
		}

		source = resutl;
	}

	CovidCollection::CovidCollection(const char* filename)
	{
		ifstream file(filename);

		if (file)
		{
			//getting covid details from file 
			while (file.peek() != EOF) {

				Covid CovidRecord{};
				string t_year{};
				string t_cases{};
				string t_deaths{};
				char temp[26]{};
				char tempNum[6]{};

				//reading country 
				file.read(temp, 25);
				CovidRecord.m_country = temp;
				trimString(CovidRecord.m_country);

				//reading city	
				file.read(temp, 25);
				CovidRecord.m_city = temp;
				trimString(CovidRecord.m_city);

				//reading varient 
				file.read(temp, 25);
				CovidRecord.m_variant = temp;
				trimString(CovidRecord.m_variant);

				//read year
				file.read(tempNum, 5);
				t_year = tempNum;
				trimString(t_year);
				CovidRecord.m_year = stoi(t_year);

				//reading cases 
				file.read(tempNum, 5);
				t_cases = tempNum;
				trimString(t_cases);
				CovidRecord.m_cases = stoul(t_cases);

				//reading deaths 
				file >> t_deaths;
				trimString(t_deaths);
				CovidRecord.m_year = stoul(t_deaths);


				//ignore eveerything untill a newline 
				file.ignore(numeric_limits<std::streamsize>::max(), '\n');

				covidRecords.push_back(CovidRecord);
			}
		}

		//istream_iterator<Covid> begin(file); 
		//istream_iterator<Covid> end; 
		//copy(begin, end, back_inserter(CovidRecord)); 
		else
		{
			throw std::invalid_argument("Can't Open file. ");
		}
	}

	void CovidCollection::display(std::ostream& out) const
	{
		for_each(covidRecords.begin(), covidRecords.end(), [&out](Covid covid) { out << covid;  });
	}


	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| " << std::setw(21) << std::left << theCovid.m_country << " | " << std::setw(15) << theCovid.m_city
			<< " | " << std::setw(20) << theCovid.m_variant << " | " << resetiosflags(ios::left) << std::setw(6);

		if (theCovid.m_year > 0)
		{
			out << theCovid.m_year << "|";
		}
		else
		{
			out << " " << "|";
		}

		out << " | " << std::setw(4) << theCovid.m_cases << " | " << std::setw(3) << theCovid.m_deaths << " |" << endl;

		return out;
	}

	//part 2 
	void CovidCollection::display(std::ostream& out, const std::string& country) const
	{
		const size_t totalCases = accumulate(covidRecords.begin(), covidRecords.end(), 0, [](size_t sum, const Covid& covid)
			{
				return sum + covid.m_cases;
			});
		const size_t totalDeaths = accumulate(covidRecords.begin(), covidRecords.end(), 0, [](size_t sum, const Covid& covid)
			{
				return sum + covid.m_deaths;
			});

		if (country == "ALL")
		{
			//print all covids
			for_each(covidRecords.begin(), covidRecords.end(), [=, &out](Covid cov) {out << cov << endl; });
			out << "|" << setw(80) << setiosflags(ios::right) << "Total cases around the world: " << totalCases << " |\n"
				<< "|" << setw(80) << "Total deaths around the world: " << totalDeaths << " |\n" << resetiosflags(ios::right);
		}
		else
		{
			const size_t localCases = accumulate(covidRecords.begin(), covidRecords.end(), 0, [country](size_t sum, const Covid& covid)
				{
					if (covid.m_country == country)
					{
						return sum + covid.m_cases;
					}
					else
					{
						return sum;

					}
				});
			const size_t localDeaths = accumulate(covidRecords.begin(), covidRecords.end(), 0, [country](size_t sum, const Covid& covid)
				{
					if (covid.m_country == country)
					{
						return sum + covid.m_deaths;
					}
					else
					{
						return sum;
					}
				});

			stringstream TotCases{};
			stringstream TotDeaths{};
			stringstream TotPercent{};
			out << "Displaying information of country = " << country << "\n";
			//print all covids for given country
			for_each(covidRecords.begin(), covidRecords.end(), [=, &out, &localCases, &localDeaths](Covid covid)
				{
					if (covid.m_country == country)
					{
						out << covid << endl;;
					}
				});
			out << setfill('-') << setw(89) << '\n' << setfill(' ');
			TotCases << "Total cases in " << country << ": " << localCases;
			out << "|" << setw(85) << setiosflags(ios::right) << TotCases.str() << " |\n";
			TotDeaths << "Total deaths in " << country << ": " << localDeaths;
			out << "|" << setw(85) << TotDeaths.str() << " |\n";
			TotPercent << country << " has " << setprecision(6) << setiosflags(ios::fixed) << ((double)localCases / totalCases) * 100 << "% of global cases and " << ((double)localDeaths / totalDeaths) * 100 << "% of global deaths";
			out << "|" << setw(85) << TotPercent.str() << " |\n"
				<< resetiosflags(ios::right);
		}
	}


	void CovidCollection::sort(const std::string& field)
	{
		if (field == "city")
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_city.compare(b.m_city) < 0)
					{
						return true;
					}
					else if (a.m_city.compare(b.m_city) > 0)
					{
						return false;
					}
					//if they're the same 
					else
					{
						if (a.m_city < b.m_city)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				});
		}
		else if (field == "variant")
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_variant.compare(b.m_variant) < 0)
					{
						return true;
					}
					else if (a.m_variant.compare(b.m_variant) > 0)
					{
						return false;
					}
					//if theyre the same 
					else
					{
						if (a.m_variant < b.m_variant)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				});
		}
		else if (field == "year")
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_year < b.m_year)
					{
						return true;
					}
					else if (a.m_year > b.m_year)
					{
						return false;
					}
					else
					{
						if (a.m_deaths < b.m_deaths)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				});
		}
		else if (field == "cases")
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_cases < b.m_cases)
					{
						return true;
					}
					else if (a.m_cases > b.m_cases)
					{
						return false;
					}
					//if they're the same 
					else
					{
						if (a.m_deaths < b.m_deaths)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				});
		}
		else if (field == "deaths")
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_deaths > b.m_deaths)
					{
						return true;
					}
					else
					{
						return false;
					}
				});
		}
		else if (field == "severity")
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_severity_status.compare(b.m_severity_status) < 0)
					{
						return true;
					}
					else if (a.m_severity_status.compare(b.m_severity_status) > 0)
					{
						return false;
					}
					else
					{
						if (a.m_deaths < b.m_deaths)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				});
		}
		else
		{
			std::sort(covidRecords.begin(), covidRecords.end(), [=](const Covid& a, const Covid& b)
				{
					if (a.m_country.compare(b.m_country) < 0)
					{
						return true;
					}
					else if (a.m_country.compare(b.m_country) > 0)
					{
						return false;
					}
					else
					{
						if (a.m_deaths < b.m_deaths)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				});
		}
	}

	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
	{
		return any_of(covidRecords.begin(), covidRecords.end(), [=](const Covid& covid)
			{
				return (covid.m_variant == variant && covid.m_country == country && covid.m_deaths > deaths);
			});
	}


	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		list<Covid> list{};

		copy_if(covidRecords.begin(), covidRecords.end(), std::back_inserter(list), [=](const Covid& covid) -> bool
			{
				return covid.m_deaths >= deaths;
			});
		return list;
	}

	void CovidCollection::updateStatus()
	{
		transform(covidRecords.begin(), covidRecords.end(), covidRecords.begin(), [](const Covid& covid)
			{
				Covid newCovid = covid;
				if (covid.m_deaths > EPIDEMIC_DEATHS)
				{
					newCovid.m_severity_status = "EPIDEMIC";
				}
				else if (newCovid.m_deaths < EARLY_DEATHS)
				{
					newCovid.m_severity_status = "EARLY";
				}
				else
				{
					newCovid.m_severity_status = "MILD";
				}
			});
	}


}