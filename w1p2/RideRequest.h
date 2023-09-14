/*									Workshop 2 Part 1
	Lebna Noori
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that
my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>

extern double g_taxrate;
extern double g_discount;

const int CUSTOMER_NAME = 10;
const int MAX_RIDE_DESC = 25;

namespace sdds
{
	class RideRequest
	{
		char m_custName[CUSTOMER_NAME]{};
		char* m_rideDesc{};//Dynamic c type string
		double m_ridePrice{};
		bool m_isDiscounted{};
	public:
		RideRequest();
		RideRequest(RideRequest& copy);
		RideRequest& operator=(RideRequest& ro);
		~RideRequest();
		
		std::istream& read(std::istream& input);		
		void display() const;

	private:
		operator bool()const;
		void setEmpty();
	};

}
#endif // !SDDS_RIDEREQUEST_H
