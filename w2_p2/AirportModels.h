/*									Workshop 2 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <string>

namespace sdds
{
	struct Airport
	{
		std::string m_airportCode = "";
		std::string m_airportName = "";
		std::string m_airportCity = "";
		std::string m_airportState = "";
		std::string m_airportCoutry = "";
		double m_latitude = 0.0;
		double m_longitude = 0.0;
		/// <summary>
		/// Returns true if object is not in empty state
		/// </summary>
		operator bool()const;
		/// <summary>
		/// if not in empty state will output airport details on istream and return it
		/// </summary>
		/// <param name="out">istream to output</param>
		/// <returns>same isrtream given</returns>
		std::ostream& print(std::ostream& os) const;

		/// <summary>
		/// set all members of aiport according to given values
		/// </summary>
		/// <param name="airportCode"></param>
		/// <param name="airportName"></param>
		/// <param name="airportCity"></param>
		/// <param name="airportState"></param>
		/// <param name="airportCoutry"></param>
		/// <param name="latitude"></param>
		/// <param name="longitude"></param>
		void set(const std::string airportCode,
			const std::string airportName,
			const std::string airportCity,
			const std::string airportState,
			const std::string airportCoutry,
			const double latitude,
			const double longitude);
		void set(const Airport& copy);
	};
	/// <summary>
	/// operator << overload, calls print of airport
	/// </summary>
	/// <param name="out">where to print</param>
	/// <param name="airPort">what to print</param>
	/// <returns>same istream given</returns>
	std::ostream& operator<<(std::ostream& os, const Airport& airPort);
	/// <summary>
	/// prints a label on received istream with special formatting
	/// </summary>
	/// <param name="out">where to print</param>
	/// <param name="str">what to print</param>
	/// <returns>same istream as received</returns>
	std::ostream& printLabel(std::ostream& os, const std::string& str);
	/// <summary>
	/// print a value with special formatting
	/// </summary>
	/// <param name="out">where to print</param>
	/// <param name="str">what to print</param>
	/// <returns>same istream as received</returns>
	std::ostream& printValue(std::ostream& os, const std::string& str);

	/// <summary>
	/// prints double value with special formatting
	/// </summary>
	/// <param name="out">where to print</param>
	/// <param name="val">what to print</param>
	/// <returns>same istream as received</returns>
	std::ostream& printValue(std::ostream& os, const double& val);

	//Airport& operator=(Airport& lo, Airport& ro);

	class AirportLog
	{
		Airport* m_airPorts{};
		size_t m_count{};
		/// <summary>
		/// loading airports from file, with given c_string name, m_count should be set to the right number of lines before calling
		/// </summary>
		/// <param name="fileName">file name to read from</param>
		/// <returns>will return 1 if succesful, otherwise 0</returns>
		int loadAirports(const char* fileName);
		/// <summary>
		/// sets object to safe empty state, dealocating space
		/// </summary>
		void setEmpty();
	public:
		AirportLog();
		AirportLog(const char* fileName);
		/// <summary>
		/// adds a given airport if it isnt empty
		/// </summary>
		/// <param name="toAdd">what to add</param>
		void addAirport(const Airport& toAdd);
		/// <summary>
		/// returns true if object not in safe empty state
		/// </summary>
		operator bool();
		/// <summary>
		/// finds all airports with given state and country, returns an Airport log with all airports in state and country given
		/// </summary>
		/// <param name="state">which state?</param>
		/// <param name="country">which country?</param>
		/// <returns>AirportLog with all airports in state and country</returns>
		AirportLog findAirport(const char* state, const char* country) const;
		/// <summary>
		/// add an airport
		/// </summary>
		/// <param name="ro">what Airport to add</param>
		/// <returns>AirportLog after adding</returns>
		AirportLog& operator+=(const Airport& airport);
		/// <summary>
		/// return the airport in the index provided, empty if invalid
		/// </summary>
		/// <param name="index">where?!</param>
		/// <returns>AN AIRPORT</returns>
		Airport operator[](size_t index);
		operator size_t();


		//rule of 5 TO DO
		AirportLog(const AirportLog& copy);
		AirportLog(AirportLog&& move)noexcept;
		AirportLog& operator=(const AirportLog& copy);
		AirportLog& operator=(AirportLog&& move)noexcept;
		~AirportLog();
	};

	size_t getFileNumRows(const char* fileName);
}


#endif // !SDDS_AIRPORTMODELS_H