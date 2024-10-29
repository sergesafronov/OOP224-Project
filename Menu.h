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

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {

    class Menu {

        const int MAX_OPTIONS = 15;

    private:
        char* m_menuContent {};
        char** m_options {};
        int m_nomOptions;
        int optionCount(const char* menuContent) const;
        void aloOptions();


    public:
        Menu(const char* menuContent);
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;
        ~Menu();

        unsigned int run() const;
    };
}
#endif // SDDS_MENU_H
