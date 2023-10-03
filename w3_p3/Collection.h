/*									Workshop 3 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <iomanip>
#include "Book.h"

namespace sdds
{

	template <typename T, const unsigned C>
	class Collection
	{
		static T m_smallestItem;
		static T m_largestItem;
		unsigned m_cnt;
		T m_items[C];
	protected:

		/// <summary>
		/// sets smallest item to received item if its smaller
		/// </summary>
		/// <param name="item">item to set</param>
		void setSmallestItem(const T& item)
		{
			if (item < m_smallestItem)
			{
				m_smallestItem = item;
			}
		}
		/// <summary>
		/// sets biggest item if received item is bigger
		/// </summary>
		/// <param name="item">item to set</param>
		void setLargestItem(const T& item)
		{
			if (m_largestItem < item)
			{
				m_largestItem = item;
			}
		}
	public:
		Collection() : m_cnt(0), m_items() {}

		/// <summary>
		/// copy constructor is prohibited, class is to only be instantiated with default constructor
		/// </summary>
		/// <param name=""></param>
		Collection(const Collection&) = delete;
		~Collection() = default;
		/// <summary>
		/// retruns current smallest item
		/// </summary>
		/// <returns></returns>
		static T getSmallestItem()
		{
			return m_smallestItem;
		}
		/// <summary>
		/// returns current largest item
		/// </summary>
		/// <returns></returns>
		static T getLargestItem()
		{
			return m_largestItem;
		}
		/// <summary>
		/// return current size
		/// </summary>
		unsigned size() const
		{
			return m_cnt;
		}
		/// <summary>
		/// return current capacity
		/// </summary>
		unsigned capacity() const
		{
			return C;

		}
		/// <summary>
		/// returns true if theres anything in collection
		/// </summary>
		operator bool() const
		{
			return m_cnt;
		}
		/// <summary>
		/// adds received item to collection if theres space for it
		/// </summary>
		/// <param name="ro">item to add</param>
		/// <returns>true if added</returns>
		bool operator+=(const T& other)
		{
			if (m_cnt < C)
			{
				setSmallestItem(other);
				setLargestItem(other);
				m_items[m_cnt] = other;
				m_cnt++;
				return true;
			}
			else
			{
				return false;
			}
		}
		/// <summary>
		/// print content of collection
		/// </summary>
		/// <param name="out">where to print</param>
		void print(std::ostream& os) const
		{
			if (*this)
			{
				os << '[';
				for (size_t i = 0u; i < m_cnt; i++)
				{
					os << m_items[i] << ((i == (m_cnt - 1)) ? ']' : ',');
				}
				os << std::endl;
			}
		}
		/// <summary>
		/// returns item at given index if index is valid, otherwise first item
		/// </summary>
		/// <param name="index">index of item to return</param>
		T& operator[](const unsigned index) 
		{
			if (index < m_cnt)
			{
				return m_items[index];
			}
			else
			{
				return m_items[0];
			}
		}
		/// <summary>
		/// increase the size by 1 if its less than capacity
		/// </summary>
		void incrSize()
		{
			if (m_cnt < C)
			{
				m_cnt++;
			}
		}
	};

	//initializing for general collection
	template <typename T, const unsigned C>
	T Collection<T, C>::m_smallestItem = 9999;
	template <typename T, const unsigned C>
	T Collection<T, C>::m_largestItem = -9999;

	//Book specialization with size 10
	template <>
	Book Collection<Book, 10>::m_smallestItem("", 1, 1000);
	template <>
	Book Collection<Book, 10>::m_largestItem("", 10000, 1);

	//Book specialization with size 72
	template <>
	Book Collection<Book, 72>::m_smallestItem("", 1, 10000);
	template <>
	Book Collection<Book, 72>::m_largestItem("", 10000, 1);


	/// <summary>
	/// print specialization for Book collection of size 10
	/// </summary>
	/// <param name="out">where to print</param>
	template <>
	void Collection<Book, 10>::print(std::ostream& os) const
	{
		if (*this)
		{
			os << std::setfill('-') << std::setw(77) << "| " << '|' << std::endl;
			os << std::setfill(' ');
			for (size_t i = 0; i < m_cnt; i++)
			{
				os << "| ";
				m_items[i].print(os) << " |" << std::endl;
			}
			os << std::setfill('-') << std::setw(77) << "| " << '|' << std::endl;
			os << std::setfill(' ');
		}
	}
	/// <summary>
	/// print specialization for Book collection of size 72
	/// </summary>
	/// <param name="out">where to print</param>
	template <>
	void Collection<Book, 72>::print(std::ostream& os) const
	{
		if (*this)
		{
			os << std::setfill('-') << std::setw(77) << "| " << '|' << std::endl;
			os << std::setfill(' ');
			for (size_t i = 0; i < m_cnt; i++)
			{
				os << "| ";
				m_items[i].print(os) << " |" << std::endl;
			}
			os << std::setfill('-') << std::setw(77) << "| " << '|' << std::endl;
			os << std::setfill(' ');
		}
	}
}

#endif // !SDDS_COLLECTION_H
