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
#include <fstream>
#include <vector>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"

using namespace std;
namespace sdds
{
	void Filesystem::addResource(std::string& path, const std::string& content)
	{
		bool done = false;
		Directory* current = m_root;
		do
		{
			done = path.find("/") == string::npos;
			if (!done)
			{
				string dirName = path.substr(0, path.find("/") + 1);
				Directory* newDir = nullptr;
				path = path.substr(path.find("/") + 1);
				//check wether such a directory exists
				newDir = dynamic_cast<Directory*>(m_root->find(dirName));

				//if not create it
				if (!newDir)
				{
					newDir = new Directory(dirName);
					*current += newDir;
				}
				//set current to new
				current = newDir;
			}
			else if (content.length() && !m_root->find(path))
			{
				//reading and adding file at the end if there is one
				*current += new File(path.c_str(), content.c_str());
			}

		} while (!done);
	}

	Filesystem::Filesystem(const char* fileName, const std::string& rootName)
	{
		m_root = new Directory(rootName);
		m_current = m_root;

		fstream file(fileName);
		//load resources from file
		if (file)
		{
			string line{};
			//read line by line and populate
			do
			{
				bool isFile{};
				getline(file, line);

				isFile = line.find('|') != string::npos;

				if (isFile)
				{
					//read content and path, trim
					string path = line.substr(0, line.find('|'));
					trimString(path);
					string contents = line.substr(line.find('|') + 1);
					trimString(contents);
					addResource(path, contents);
				}
				else// if DIR
				{
					//read path
					trimString(line);
					//add it
					addResource(line);
				}

			} while (file);
		}
		else
		{
			delete m_root;
			throw "ERROR READING FILE";
		}
	}
	Filesystem::Filesystem(Filesystem&& move) noexcept
	{
		*this = std::move(move);
	}
	Filesystem& Filesystem::operator=(Filesystem&& move) noexcept
	{
		if (this != &move)
		{
			delete m_root;
			m_root = move.m_root;
			delete move.m_root;
			move.m_current = nullptr;
			m_current = m_root;
		}
		return *this;
	}
	Filesystem& Filesystem::operator+=(Resource* res)
	{
		*m_current += res;
		return *this;
	}
	Directory* Filesystem::change_directory(const std::string& dirName)
	{
		if (dirName.length())
		{
			Resource* targetDir = m_root->find(dirName, vector<OpFlags>{OpFlags::RECURSIVE});
			if (targetDir && targetDir->type() == NodeType::DIR)
			{
				m_current = dynamic_cast<Directory*>(targetDir);
			}
			else
			{
				throw std::invalid_argument("Cannot change directory! " + dirName + " not found!");
			}
		}
		else
		{
			m_current = m_root;
		}
		return m_current;
	}
	Directory* Filesystem::get_current_directory() const
	{
		return m_current;
	}
	Filesystem::~Filesystem()
	{
		delete m_root;
		m_current = nullptr;
	}
	void trimString(std::string& source)
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
}
