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

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds {

    class Perishable : public Item {
    private:
        Date m_expiryDate;   
        char* m_instructions;

    public:

        Perishable();
        Perishable(const Perishable& other);
        Perishable& operator=(const Perishable& other);
        ~Perishable();

        const Date& expiry() const;

        // Virtual Overrides
        int readSku(istream& is) override;
        ofstream& save(ofstream& ofs) const override;
        ifstream& load(ifstream& ifs) override;
        ostream& display(ostream& os) const override;
        istream& read(istream& is) override;
    };

}

#endif // SDDS_PERISHABLE_H
