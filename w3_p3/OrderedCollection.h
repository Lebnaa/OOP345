/*									Workshop 3 Part 2
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_ORDERED_COLLECTION_H
#define SDDS_ORDERED_COLLECTION_H

#include "Collection.h"

namespace sdds
{
	template <typename T>
	class OrderedCollection : public Collection<T, 72u>
	{
	public:
		OrderedCollection() : Collection<T, 72u>() {};

		OrderedCollection(const OrderedCollection& oc) = delete;

		~OrderedCollection() = default;
		/// <summary>
		/// If possible, insert the item such that the collection is in ascending order
		/// </summary>
		/// <param name="ro">Item to insert</param>
		/// <returns>true if inserted</returns>
		bool operator+=(const T& other)
		{
			if (this->size() < this->capacity())
			{
				this->incrSize();
				//inserting
				//if bigger than largest - place at the end
				if (other > this->getLargestItem())
				{
					//updates last emlement with value of other. this->size() - 1
					this->operator[](this->size() - 1) = other;
					// updating the largest item stored with the class with the value of other
					this->setLargestItem(other);
				}
				else//smaller than largest, will be placed either in the beginning or middle, will have to shift all items bigger than it up
				{
					//find index to place this item
					unsigned int targetIndex = 0u;
					bool foundTarget = false;
					for (unsigned i = 0u; i < this->size() && !foundTarget; i++)
					{
						if (this->operator[](i) > other)
						{
							targetIndex = i;
							foundTarget = true;
						}
					}
					//shift all bigger eleemnts up and insert item
					for (unsigned i = (this->size() - 1); i > targetIndex; i--)
					{
						this->operator[](i) = this->operator[](i - 1);
					}
					this->operator[](targetIndex) = other;		
				}
				this->setSmallestItem(other);
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}

#endif // !SDDS_ORDERED_COLLECTION_H