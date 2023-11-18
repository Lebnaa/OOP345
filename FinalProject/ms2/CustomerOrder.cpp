// Name: Lebna Noori 
// Seneca Student ID: 157672205
// Seneca email: lnoori1@myseneca.ca
// Date of completion: Nov.9th 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <iomanip>
#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds 
{
   
    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}


    CustomerOrder::CustomerOrder(const std::string& str) : CustomerOrder() {
        Utilities util;
        size_t next_pos = 0, posOfItems;
        bool more = true;
        m_name = trim(util.extractToken(str, next_pos, more));
        m_product = util.extractToken(str, next_pos, more);
        m_cntItem = 0;
        posOfItems = next_pos;

        while (more) 
        {
            util.extractToken(str, next_pos, more);
            m_cntItem++;
        }

        m_lstItem = new Item * [m_cntItem];
        next_pos = posOfItems;
        more = true;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }
        m_product = trim(m_product);
        m_widthField = std::max(m_widthField, util.getFieldWidth());
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& move) noexcept 
    {
        *this = std::move(move);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& move) noexcept 
    {
        if (this != &move) {
            if (this->m_lstItem != nullptr) {
                for (size_t i = 0; i < m_cntItem; i++)
                    delete m_lstItem[i];

                delete[] m_lstItem;
            }
            m_name = move.m_name;
            m_product = move.m_product;
            m_cntItem = move.m_cntItem;
            m_lstItem = move.m_lstItem;
            move.m_name = "";
            move.m_product = "";
            move.m_cntItem = 0;
            move.m_lstItem = nullptr;
        }
        return *this;
    }

    // copy operations are not allowed, throws exception
    CustomerOrder::CustomerOrder(const CustomerOrder& copy) {
        throw "Copy operations are not allowed.";
    }

    // copy operations are not allowed, throws exception
    CustomerOrder& CustomerOrder::operator=(const CustomerOrder& src) 
    {
        throw "Copy operations are not allowed.";
    }

    bool CustomerOrder::isOrderFilled() const 
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (!m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }


    bool CustomerOrder::isItemFilled(const std::string& itemName) const 
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) 
    {
        bool found = false;
        for (size_t i = 0; i < m_cntItem && !found; i++) 
        {
            if (trim(m_lstItem[i]->m_itemName) == trim(station.getItemName()) && !m_lstItem[i]->m_isFilled) 
            {
                if (station.getQuantity() > 0) 
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << trim(m_product) << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    found = true;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    // displays the customer order
    void CustomerOrder::display(std::ostream& os) const 
    {
        os << m_name << " - " << std::left << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
                << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << "- "; 
            if (isItemFilled(m_lstItem[i]->m_itemName)) 
            {
                os << "FILLED";
            }
            else 
            {
                os << "TO BE FILLED";
            }
            os << std::endl;
        }
    }
}
    