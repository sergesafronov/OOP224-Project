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

#include "Utils.h"

namespace sdds {

   Utils ut;

   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }

   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }

   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
      
   void Utils::peekIgnore(istream& is)  {
       char nextChar = is.peek(); 
       if (nextChar == '\t' || nextChar == '\n') {
           is.ignore();
       }
   }

   void Utils::aloCpy(char*& destination, const char* source) {
       if (destination) {
           delete[] destination;
       }
       if (source) {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }       
   }

   void Utils::clearBuffer() {
       if (cin.fail()) {
           cin.clear();
       }      
       while (cin.get() != '\n') continue;
   }

   int Utils::getInt(const char* prompt) {
       if (prompt) {
           cout << prompt;
       }
       int value;
       while (true) {
           cin >> value;
           if (cin.fail()) {
               cout << "Invalid Integer, retry: ";
               clearBuffer();
           }
           else {
               clearBuffer();
               return value;
           }
       }
   }

   int Utils::getInt(int min, int max, const char* prompt, const char* errMes) {
       int value;
       do {
           value = getInt(prompt);
           if (errMes) {
               cout << errMes << ", retry: ";
           }
           if (value < min || value > max) {
               prompt = nullptr;
               cout << "Value out of range [" << fixed << setprecision(2) << min << "<=val<=" << max << "]: ";
           }
       } while (value < min || value > max);
       return value;
   }

   double Utils::getDouble(const char* prompt) {
       if (prompt) {
           cout << prompt;
       }
       double value;
       while (true) {
           cin >> value;
           if (cin.fail()) {
               cout << "Invalid number, retry: ";
               clearBuffer();
           }
           else {
               clearBuffer();
               return value;
           }
       }
   }

   double Utils::getDouble(double min, double max, const char* prompt, const char* errMes) {
       double value;
       do {
           value = getDouble(prompt);
           if (value < min || value > max) {
               if (errMes) {
                   cout << errMes << ", retry: ";
               }
               prompt = nullptr;
               cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
           }
       } while (value < min || value > max);
       return value;
   }


   void Utils::strCpyFromTo(char* s1, const char* s2, int start, int end) {
       if ((s2 && s1) && start >= 0 && start <= end) {
           
           int j = 0;
           for (int i = start; i < end; i++) {
               s1[j] = s2[i];
               j++;
           }
           s1[j] = '\0';
       }      
   }      
}