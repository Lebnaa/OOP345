#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>

extern double g_taxrate = 0.0;
extern double g_discount = 0.0;

namespace sdds
{
	class RideRequest {
		char CustName[11]; 
		char RideDescrip[26]; 
		double ridePrice;
		bool hasDiscount = true; 
	public:
		RideRequest() = default; 
		std::istream& read(std::istream& is); 
		void display()const;
	};
}


#endif // !SDDS_RIDEREQUEST_H
