// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
	sdds::CovidCollection::CovidCollection(const char* filename)
	{
		fstream file(filename);

		if (file)
		{
			//extract covid details from file
			while (file.peek() != EOF)
			{
				Covid newCovid{};
				string t_year{};
				string t_cases{};
				string t_deaths{};
				char temp[26]{};
				char t_num[6]{};

				//read country
				file.read(temp, 25);
				newCovid.m_country = temp;
				trimString(newCovid.m_country);

				//read city
				file.read(temp, 25);
				newCovid.m_city = temp;
				trimString(newCovid.m_city);

				//read variant
				file.read(temp, 25);
				newCovid.m_variant = temp;
				trimString(newCovid.m_variant);

				//read year
				file.read(t_num, 5);
				t_year = t_num;
				trimString(t_year);
				newCovid.m_year = stoi(t_year);

				//read cases
				file.read(t_num, 5);
				t_cases = t_num;
				trimString(t_cases);
				newCovid.m_cases = stoul(t_cases);

				//read deaths
				file >> t_deaths;
				trimString(t_deaths);
				newCovid.m_deaths = stoul(t_deaths);

				//ignore everything else untill newline
				file.ignore(numeric_limits<std::streamsize>::max(), '\n');

				//add the new covid to collection
				CovidRecord.push_back(newCovid);
			}
		}
		else //file could not be reached raise exception
		{
			throw "File could not be reached";
		}
	}

	//part 2 
	void CovidCollection::display(std::ostream& out, const std::string& country) const
	{
		const size_t totalCases = accumulate(CovidRecord.begin(), CovidRecord.end(), 0, [](size_t sum, const Covid& covid) 
			{
				return sum + covid.m_cases;
			});
		const size_t totalDeaths = accumulate(CovidRecord.begin(), CovidRecord.end(), 0, [](size_t sum, const Covid& covid) 
			{
				return sum + covid.m_deaths;
			});

		if (country == "ALL")
		{
			for_each(CovidRecord.begin(), CovidRecord.end(), [=, &out](Covid covid) {out << covid << endl; });
			out << "|" << setw(80) << setiosflags(ios::right) << "Total cases around the world: " << totalCases << " |\n"
				<< "|" << setw(80) << "Total deaths around the world: " << totalDeaths << " |\n" << resetiosflags(ios::right);
		}
		else
		{
			const size_t localCases = accumulate(CovidRecord.begin(), CovidRecord.end(), 0, [country](size_t sum, const Covid& covid) 
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
			const size_t localDeaths = accumulate(CovidRecord.begin(), CovidRecord.end(), 0, [country](size_t sum, const Covid& covid)
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

			stringstream TotalCases{};
			stringstream TotalDeaths{};
			stringstream TotalPercent{};
			out << "Displaying information of country = " << country << "\n";
			for_each(CovidRecord.begin(), CovidRecord.end(), [=, &out, &localCases, &localDeaths](Covid covid)
				{
					if (covid.m_country == country)
						out << covid << endl;;
				});
			out << setfill('-') << setw(89) << '\n' << setfill(' ');
			TotalCases << "Total cases in " << country << ": " << localCases;
			out << "|" << setw(85) << setiosflags(ios::right) << TotalCases.str() << " |\n";
			TotalDeaths << "Total deaths in " << country << ": " << localDeaths;
			out << "|" << setw(85) << TotalDeaths.str() << " |\n";
			TotalPercent << country << " has " << setprecision(6) << setiosflags(ios::fixed) << ((double)localCases / totalCases) * 100 << "% of global cases and " << ((double)localDeaths / totalDeaths) * 100 << "% of global deaths";
			out << "|" << setw(85) << TotalPercent.str() << " |\n"
				<< resetiosflags(ios::right);
		}
	}

	void CovidCollection::sort(const std::string& field)
	{
		//for city 
		if (field == "city")
		{
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
				{
					if (a.m_city.compare(b.m_city) < 0)
					{
						return true;
					}
					else if (a.m_city.compare(b.m_city) > 0)
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
		else if (field == "variant")
		{
			//for variant 
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
				{
					if (a.m_variant.compare(b.m_variant) < 0)
					{
						return true;
					}
					else if (a.m_variant.compare(b.m_variant) > 0)
					{
						return false;
					}
					else 
					{
						if (a.m_deaths < b.m_deaths)
						{
							return true;
						}
						else if (a.m_deaths > b.m_deaths)
						{
							return false;
						}
						else 
						{
							return a.m_year < b.m_year;
						}
					}
				});
		}
		else if (field == "year")
		{
			//for year 
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
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
			//for cases 
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
				{
					if (a.m_cases > b.m_cases)
					{
						return true;
					}
					else if (a.m_cases < b.m_cases)
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
		else if (field == "deaths")
		{
			//for deaths 
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
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
			//for severity
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
			{
				if (a.m_severity.compare(b.m_severity) < 0)
				{
					return true;
				}
				else if (a.m_severity.compare(b.m_severity) > 0)
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
			//for country
			std::sort(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& a, const Covid& b) 
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
		return
			any_of(CovidRecord.begin(), CovidRecord.end(), [=](const Covid& covid)
				{
					return covid.m_variant == variant && covid.m_country == country && covid.m_deaths > deaths;
				});
	}

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		list<Covid> list{};
		copy_if(CovidRecord.begin(), CovidRecord.end(), std::back_inserter(list), [=](const Covid& covid) -> bool
			{
				return covid.m_deaths >= deaths;
			});
		return list;
	}

	void CovidCollection::updateStatus()
	{
		transform(CovidRecord.begin(), CovidRecord.end(), CovidRecord.begin(), [](const Covid& covid)
		{
				Covid newCov = covid;
				
				if (covid.m_deaths > EPIDEMIC_DEATHS)
				{
					newCov.m_severity = "EPIDEMIC";
				}
				else if (covid.m_deaths < EARLY_DEATHS)
				{
					newCov.m_severity = "EARLY";
				}
				else
				{
					newCov.m_severity = "MILD";

				}
			return newCov;
		});
	}

	void CovidCollection::trimString(std::string& source)
	{
		size_t begin = source.find_first_not_of(" \t\n");
		size_t end = source.find_last_not_of(" \t\n");
		string res{};
		if (begin != string::npos && end != string::npos)
		{
			res = source.substr(begin, end - begin + 1);
		}
		else
		{
			res = "";
		}
		source = res;
	}

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| " << setw(21) << std::left << theCovid.m_country << " | "
			<< setw(15) << theCovid.m_city << " | "
			<< setw(20) << theCovid.m_variant << " | " << resetiosflags(ios::left)
			<< setw(6);
		if (theCovid.m_year > 0)
		{
			out << theCovid.m_year << " | ";
		}
		else
		{
			out << " " << " | ";
		}

		out << setw(4) << theCovid.m_cases << " | "
			<< setw(3) << theCovid.m_deaths << " | "
			<< "| " << setw(8) << theCovid.m_severity << " |";

		return out;
	}

	bool operator<(const std::string& a, const std::string& b)
	{
		return false;
	}
}