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

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>

using namespace std;

namespace sdds {

    class Status {
    private:
        char* m_desc;
        int m_code;   

    public:
        Status(const char* desc = nullptr);          
        Status(const Status& other);          
        ~Status();

        Status& operator=(const Status& other);      
        Status& operator=(int code);                 
        Status& operator=(const char* desc);         
       
        // Type Conversion overloads
        operator int() const;
        operator const char* () const;
        operator bool() const;

        Status& clear();                             

        // Friend insertion operator
        friend ostream& operator<<(ostream& os, const Status& status);
    };
}
#endif // STATUS_H
