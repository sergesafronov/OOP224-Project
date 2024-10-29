/*****************************************************************************
Milestone - 5, Part 6 
Full Name : Serge Safronov
Student ID# : 132736224
Email : SSafronov@myseneca.ca
Section : RNB
Date : November 30, 2023

Authenticity Declaration :
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*****************************************************************************/

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"

namespace sdds {
    
    class Item : public iProduct {

    private:
        double m_price;
        int m_qtyOnHand;
        int m_qtyNeeded;
        char* m_description;
        bool m_isLinear;
    
    protected:
        int m_sku;
        Status m_state;

        bool linear() const;

    public:
        Item();
        Item(const Item& I);
        Item& operator=(const Item& I);
        ~Item();

        int qtyNeeded() const;
        int qty() const;
        operator double() const;
        operator bool() const;

        const char* description() const;

        int operator-=(int qty);
        int operator+=(int qty);
        void linear(bool isLinear);

        void clear();

        bool operator==(int sku) const;
        bool operator==(const char* description) const;

        ofstream& save(ofstream& ofs) const;
        ifstream& load(ifstream& ifs);
        ostream& display(ostream& os) const;

        virtual int readSku(istream& is);
        istream& read(istream& is);
    };
}
#endif