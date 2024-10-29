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

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"
#include "Perishable.h"
#include "Utils.h" 
#include "Date.h" 

#include <iostream>
#include <string>

using namespace std;

namespace sdds {

    class AidMan {

    private:

        static const int sdds_max_num_items = 100;

        iProduct* m_items[sdds_max_num_items] {}; 
        int m_numItems;


        char* m_fileName;
        Menu m_MainMenu;
        unsigned int menu() const;

        void save() const;
        void deallocate();
        bool load();

    public:
        AidMan(const char* fileName = nullptr);
        AidMan(const AidMan&) = delete;
        AidMan& operator=(const AidMan&) = delete;
        ~AidMan();
        void run();

        int list(const char* sub_desc = nullptr);
        int search(int sku) const;
        void addItem();
        void remove(int index);
        void removeItem();
        void updateQuantity();
        void sort();
        void shipItems();
    };
}
#endif // SDDS_AIDMAN_H
