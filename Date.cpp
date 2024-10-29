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

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include "Status.h"
#include "Utils.h"
#include "Date.h"
#include <stdlib.h>

using namespace std;

namespace sdds {
	
	bool Date::validate() {
        int currentYear;
        ut.getSystemDate(&currentYear);        
        
        if (m_year < currentYear || m_year > sdds_maxYear) {
            m_state = "Invalid year in date";
            m_state = 1;
            return false;
        }

        if (m_month < 1 || m_month > 12) {
            m_state = "Invalid month in date";
            m_state = 2;
            return false;
        }

        int maxDays = ut.daysOfMon(m_month, m_year);
        if (m_day < 1 || m_day > maxDays) {
            m_state = "Invalid day in date";
            m_state = 3;
            return false;
        }

        m_state.clear();
        return true;
    }

    int Date::uniqueDateValue() const {
        return m_year * 372 + m_month * 31 + m_day;;
    }

    Date::Date() {
        ut.getSystemDate(&m_year, &m_month, &m_day);
        validate();
    }

    Date::Date(int year, int month, int day) {
        this->m_year = year;
        this->m_month = month;
        this->m_day = day;
        validate();
    }

    Date& Date::operator=(const Date& other) {
        if (this != &other) {
            m_year = other.m_year;
            m_month = other.m_month;
            m_day = other.m_day;
            m_state = other.m_state;
            m_formatted = other.m_formatted;
        }
        return *this;
    }

    bool Date::operator==(const Date& other) const {
        return this->uniqueDateValue() == other.uniqueDateValue();
    }

    bool Date::operator!=(const Date& other) const {
        return this->uniqueDateValue() != other.uniqueDateValue();
    }

    bool Date::operator<(const Date& other) const {
        return this->uniqueDateValue() < other.uniqueDateValue();
    }

    bool Date::operator>(const Date& other) const {
        return this->uniqueDateValue() > other.uniqueDateValue();
    }

    bool Date::operator<=(const Date& other) const {
        return this->uniqueDateValue() <= other.uniqueDateValue();
    }

    bool Date::operator>=(const Date& other) const {
        return this->uniqueDateValue() >= other.uniqueDateValue();
    }

    const Status& Date::state() const {
        return m_state;
    }

    Date& Date::formatted(bool value) {
        this->m_formatted = value;
        return *this;
    }

    Date::operator bool() const {
        return m_state;
    }

    ostream& Date::write(ostream& os) const {
        if (m_formatted) {
            os << right << m_year
                << "/" << setw(2) << setfill('0') << m_month
                << "/" << setw(2) << setfill('0') << m_day;
        }
        else {
            os << right << (m_year % 100)
                << setw(2) << setfill('0') << m_month
                << setw(2) << setfill('0') << m_day;
        }
        os << setfill(' ');
        return os;
    }

    istream& Date::read(istream& is) {
        int date;

        // Remove '/' from date.
        char rawData[12];
        is.get(rawData, 11, '\n');
        if (is.fail()) {
            is.setstate(ios::badbit);
            return is;
        }

        char noSlashDate[7];
        int j = 0;

        if (strlen(rawData) > 7) {
            for (int i = 2; i < (int)strlen(rawData); i++) {
                if (rawData[i] != '/') { 
                    noSlashDate[j] = rawData[i];
                    j++;
                }
            }
            noSlashDate[j] = '\0';
            date = atoi(noSlashDate);
        }
        else {
            date = atoi(rawData);
        }

        // Check if reading an int failed.
        if (is.fail()) {
            cout << "Invalid date value";
            is.setstate(ios::badbit);
            return is;
        }
        // MMDD format.
        if (date >= 0 && date <= 9999) {
            m_day = date % 100;
            m_month = (date / 100) % 100;
            ut.getSystemDate(&m_year);
        }
        // YYMMDD format.
        else if (date >= 100000 && date <= 999999) {
            m_day = date % 100;
            m_month = (date / 100) % 100;

            int year;
            ut.getSystemDate(&year);
            int century = year - (year % 100);  // Extract the century.
            m_year = century + (date / 10000) % 100;
        }
        // No match with the formats is invalid.
        // The istream object will be set to a fail state.
        // istream::setstate(ios::badbit)
        else {
            cout << "Invalid date value";
            is.setstate(ios::badbit);
            return is;
        }
        // Validate the calculated date.       
        if (!validate()) {
            is.setstate(ios::badbit);
        }
        return is;
    }

    ostream& operator<<(ostream& os, const Date& date) {
        return date.write(os);
    }

    istream& operator>>(istream& is, Date& date) {
        return date.read(is);
    }
}