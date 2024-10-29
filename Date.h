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

#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Status.h"

using namespace std;

namespace sdds {
    
    class Date {

        const int sdds_maxYear = 2030;
    
    private:
        int m_year;
        int m_month;
        int m_day;
        Status m_state;
        bool m_formatted = true;

        bool validate();
        int uniqueDateValue() const;

    public:
        Date();
        Date(int year, int month, int day);
        Date& operator=(const Date& other);

        bool operator==(const Date& rhs) const;
        bool operator!=(const Date& rhs) const;
        bool operator<(const Date& rhs) const;
        bool operator<=(const Date& rhs) const;
        bool operator>(const Date& rhs) const;
        bool operator>=(const Date& rhs) const;

        const Status& state() const;
        Date& formatted(bool format);
        operator bool() const;
        ostream& write(ostream& os) const;
        istream& read(istream& is);

        friend ostream& operator<<(ostream& os, const Date& date);
        friend istream& operator>>(istream& is, Date& date);    
    };
    
    ostream& operator<<(ostream& os, const Date& date);
    istream& operator>>(istream& is, Date& date);
}
#endif // SDDS_DATE_H