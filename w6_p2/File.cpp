/*									Workshop 6 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/


#include <string>
#include "File.h"
#include "Resource.h"


namespace sdds
{
	File::File(const char* name, const char* contents)
	{
		m_name = name;
		m_contents = contents;
	}
	void File::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
	}
	NodeType File::type() const
	{
		return NodeType::FILE;
	}
	std::string File::path() const
	{
		return m_parent_path + m_name;
	}
	std::string File::name() const
	{
		return m_name;
	}
	int File::count() const
	{
		return -1;
	}
	size_t File::size() const
	{
		return m_contents.length();
	}
}