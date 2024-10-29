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

#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H
#include <iostream>
#include <fstream>

using namespace std;

namespace sdds {

    class iProduct {

    public:

        // Pure virtual functions of an abstract class
        virtual int readSku(istream& istr) = 0;
        virtual int operator-=(int qty) = 0;
        virtual int operator+=(int qty) = 0;

        virtual const char* description() const = 0;
        
        virtual operator double() const = 0;
        virtual operator bool() const = 0;
       
        virtual int qtyNeeded() const = 0;
        virtual int qty() const = 0;
        virtual void linear(bool isLinear) = 0;
        
        virtual ofstream& save(ofstream& ofstr) const = 0;
        virtual ifstream& load(ifstream& ifstr) = 0;
        virtual ostream& display(ostream& ostr) const = 0;
        virtual istream& read(istream& istr) = 0;
        
        virtual bool operator==(int sku) const = 0;
        virtual bool operator==(const char* description) const = 0;

        virtual ~iProduct();
    };

    ostream& operator<<(ostream& os, const iProduct& p);
    istream& operator>>(istream& is, iProduct& p);
}
#endif
