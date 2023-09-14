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
		~RideRequest();
		/// <summary>
		/// Read name, desc and boolean if discounted from given istream
		/// </summary>
		/// <param name="input">where to read from</param>
		/// <returns>same istream that was passed</returns>
		std::istream& read(std::istream& input);
		/// <summary>
		/// display counter and contents of the object to cout
		/// </summary>
		void display() const;
		/// <summary>
		/// copy assignment operator
		/// </summary>
		/// <param name="ro">what to assign</param>
		/// <returns>object after assigning</returns>
		RideRequest& operator=(RideRequest& ro);
	private:
		/// <summary>
		/// Return true if name populated
		/// </summary>
		operator bool()const;
		/// <summary>
		/// sets current object to empty state
		/// </summary>
		void setEmpty();
	};


}
#endif // !SDDS_RIDEREQUEST_H
