/*									Workshop 6 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <string>
#include "Directory.h"

namespace sdds
{
	class Filesystem
	{
		Directory* m_root{};
		Directory* m_current{};

		void addResource(std::string&, const std::string & = "");
	public:
		Filesystem(const char*, const std::string & = std::string());

		//copy operations not allowed
		Filesystem& operator=(Filesystem&) = delete;
		Filesystem(Filesystem&) = delete;

		//move operations
		Filesystem(Filesystem&&) noexcept;
		Filesystem& operator=(Filesystem&&) noexcept;

		//add a recourse to current directory
		Filesystem& operator+=(Resource*);

		//change current to given directory name
		Directory* change_directory(const std::string & = "");

		Directory* get_current_directory() const;

		~Filesystem();
	};

	void trimString(std::string&);
}

#endif