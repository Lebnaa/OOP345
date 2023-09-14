/*									Workshop 2 Part 1
	Lebna Noori 
	Sections: NAA
	Student ID: 157672205
	Seneca Email: lnoori1@myseneca.ca

I have done all the coding by myself and only copied the code that 
my professor provided to complete my workshops and assignments.
*/


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "RideRequest.h"

using namespace std; 

namespace sdds
{
    istream& RideRequest::read(istream& is)
    {
        char comma, discountStatus; 
        if (!is.fail())
        {
            is >> CustName;
            is.ignore();
            getline(is, RideDescrip, ',');
            is.getline(g_taxrate, ',');
            is >> comma;
            is.ignore();
            is >> discountStatus;
         
            if (discountStatus == 'Y')
            {
                hasDiscount = true;
            }
            else {
                hasDiscount = false;
            }
            is.ignore();
        }
        return is;
    }
    
    
    void RideRequest::display() const 
    {
       // Counter variable (local to the function, remains in memory for the lifetime of the program)
       static int counter = 1; // Initialized to 1 the first time the function is called

       // Check if a customer name has been stored in the current object
       if (CustName[0] != '\0')
       {
           // Calculate the price with tax and discount if applicable
           double priceWithTax = g_taxrate * (1.0 + g_taxrate);
           double priceWithDiscount = priceWithTax;

           if (hasDiscount) 
           {
               priceWithDiscount *= (1.0 - g_discount);
           }

            // Display the ride request in the proper format
            cout << left << setw(2) << counter << ". " << left << setw(10) << CustName << "|"
                << left << setw(25) << RideDescrip << "|"
                << left << setw(12) << fixed << setprecision(2) << priceWithTax;

           if (hasDiscount) 
           {
               cout << "|" << right << setw(13) << priceWithDiscount << endl;
           }
                // Increment the counter
             counter++;
       }
      else 
      {
         // No customer name stored in the current object
         cout << left << setw(2) << counter << ". No Ride Request" << endl;
      }
    }

}