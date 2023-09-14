/*									Workshop 2 Part 1
	Lebna Noori 
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca
	Date: Sept. 14/2023

I have done all the coding by myself and only copied the code that 
my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "RideRequest.h"

using namespace sdds;
using namespace std;

RideRequest::RideRequest() : m_custName{}, m_rideDesc{}, m_isDiscounted{}
{
}


RideRequest::RideRequest(RideRequest& copy)
{
	*this = copy;
}


RideRequest& RideRequest::operator=(RideRequest& copy)
{
	if (*this != copy)
	{
		if (copy)
		{	//if in good state copy all
			strcpy(m_custName, copy.m_custName);
			//Checking if description is empty, if not clear it before copying to it

			delete[] m_rideDesc;

			//Dynamically allocate space for description and copy to it
			size_t size = strlen(copy.m_rideDesc);
			m_rideDesc = new char[size + 1];
			strcpy(m_rideDesc, copy.m_rideDesc);

			m_ridePrice = copy.m_ridePrice;
			m_isDiscounted = copy.m_isDiscounted;
		}
		else
		{	//otherwise destroy the object
			setEmpty();
		}
	}
	return *this;
}


RideRequest::~RideRequest()
{
	setEmpty();
}

RideRequest::operator bool() const
{
	return !(m_custName[0] == '\0');
}

void RideRequest::setEmpty()
{
	m_custName[0] = '\0';
	delete[] m_rideDesc;
	m_rideDesc = NULL;
}

istream& RideRequest::read(std::istream& input)
{
	if (input)//testing if istream is in good state
	{
		char tempName[CUSTOMER_NAME]{};
		string tempDesc{};
		double tempPrice{};
		char tempDiscount{};
		//Read name
		input.getline(tempName, CUSTOMER_NAME, ',');
		//Read description
		getline(input, tempDesc, ',');
		//Read price
		input >> tempPrice;
		//ignore delimiter
		input.get();
		//Read discount
		input.get(tempDiscount);

		//check if reading succeeded
		if (input)
		{
			//assign to members
			strcpy(m_custName, tempName);
			//clearing description before copying to it

			delete[] m_rideDesc;

			//setting the description
			size_t size = tempDesc.length();
			m_rideDesc = new char[size + 1];
			strcpy(m_rideDesc, tempDesc.c_str());

			m_ridePrice = tempPrice;
			m_isDiscounted = (tempDiscount == 'Y') ? true : false;
		}
		else
		{
			setEmpty();
		}
	}
	return input;
}

void RideRequest::display() const 
{
	static size_t count = 1;
	if (*this)
	{
		//calculate tax
		double priceWithTax = m_ridePrice * (1 + g_taxrate);

		//setiosflag aligns to the left within its 2-character-wide field
		cout << setw(2) << setiosflags(ios::left) << count << ". ";
		cout << setw(CUSTOMER_NAME) << m_custName << '|';
		cout << setw(MAX_RIDE_DESC) << m_rideDesc << '|';
		//rest character 
		cout << setw(12) << std::fixed << setprecision(2) << priceWithTax << '|' << resetiosflags(ios::left);

		//if discounted print discounted price
		if (m_isDiscounted)
		{
			double discountedPrice = priceWithTax - g_discount;
			cout << setiosflags(ios::right) << setw(13) << discountedPrice;
			cout << resetiosflags(ios::right);
		}
		cout << endl;
	}
	else
	{
		//no customer name
		cout << setw(2) << count << ". No Ride Request" << endl;
	}
	count++;
}