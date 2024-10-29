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

#include "iProduct.h"

namespace sdds {
    
    ostream& operator<<(ostream& os, const iProduct& p) {
        return p.display(os);
    }

    istream& operator>>(istream& is, iProduct& p) {
        return p.read(is);
    }

    iProduct::~iProduct() {}
}