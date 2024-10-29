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
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include <cstring>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

namespace sdds {
   
   const int sdds_testYear = 2023;
   const int sdds_testMon = 12;
   const int sdds_testDay = 9;
   
   class Utils {
   private:
       bool m_testMode = false;
   
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);

      void peekIgnore(istream& is);
      void aloCpy(char*& destination, const char* source);
      void clearBuffer();
      int getInt(const char* prompt = nullptr);
      int getInt(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      double getDouble(const char* prompt);
      double getDouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr);
      void strCpyFromTo(char* s1, const char* s2, int start, int end);
   };
   extern Utils ut;
}
#endif // !SDDS_UTILS_H
