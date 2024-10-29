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

#include "Item.h"
#include "Utils.h"

namespace sdds {

	Item::Item() {
		m_price = 0.0;
		m_qtyOnHand = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_isLinear = false;
		m_sku = 0;
		m_state = "New object";
	}

	Item::Item(const Item& I) {
		operator=(I);
	}

	Item& Item::operator=(const Item& I) {
		if (this != &I) {
			m_sku = I.m_sku;
			m_qtyOnHand = I.m_qtyOnHand;
			m_qtyNeeded = I.m_qtyNeeded;
			m_isLinear = I.m_isLinear;
			m_price = I.m_price;
			ut.aloCpy(m_description, I.m_description);
			m_state = I.m_state;
		}
		return *this;
	}
	
	
	Item::~Item() {
		delete[] m_description;
	}

	int Item::qtyNeeded() const {
		return m_qtyNeeded;
	}

	int Item::qty() const {
		return m_qtyOnHand;
	}

	Item::operator double() const {
		return m_price;
	}

	Item::operator bool() const {
		return m_state;
	}

	const char* Item::description() const {
		return m_description;;
	}

	int Item::operator-=(int qty) {
		if (m_qtyOnHand >= qty) {
			m_qtyOnHand -= qty;
		}		
		return m_qtyOnHand;
	}

	int Item::operator+=(int qty) {
		m_qtyOnHand += qty;
		return m_qtyOnHand;
	}

	bool Item::linear() const {
		return m_isLinear;
	}

	void Item::linear(bool isLinear) {
		m_isLinear = isLinear;
	}

	void Item::clear() {
		m_state.clear();
	}

	bool Item::operator==(int sku) const {
		return m_sku == sku;
	}

	bool Item::operator==(const char* description) const {
		if (description == nullptr || m_description == nullptr) {
			return false;
		}
		return strstr(m_description, description) != nullptr;
	}

	ofstream& Item::save(ofstream& ofs) const {
		if (*this) {
			ofs << m_sku << '\t'
				<< m_description << '\t'
				<< m_qtyOnHand << '\t'
				<< m_qtyNeeded << '\t'
				<< fixed << setprecision(2) << m_price;
		}
		return ofs;
	}

	ifstream& Item::load(ifstream& ifs) {
		delete[] m_description; 
		m_description = nullptr;
				
		ifs >> m_sku;
		ut.peekIgnore(ifs);

		char tempDesc[1000] {};
		ifs.get(tempDesc, 1001, '\t');
		ut.peekIgnore(ifs);
		
		ifs >> m_qtyOnHand;
		ut.peekIgnore(ifs);
		
		ifs >> m_qtyNeeded;
		ut.peekIgnore(ifs);
		
		ifs >> m_price;
		ut.peekIgnore(ifs);

		if (!ifs) {
			m_state = "Input file stream read failed!";
		}
		else {
			m_state.clear();
			ut.aloCpy(m_description, tempDesc);
		}
		return ifs;
	}

	ostream& Item::display(ostream& ostr) const {
		if (m_state) {
			if (m_isLinear) {
				ostr << m_sku << " | ";
				int i;
				for (i = 0; i < 35 && m_description[i]; ostr << m_description[i++]);
				for (; i < 35; ostr << ' ', i++);
				ostr << " | " << setw(4) << m_qtyOnHand << " | " << setw(4) << m_qtyNeeded << " | ";
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << setw(7) << m_price << " |";
			}
			else {
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_description << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qtyOnHand << endl;
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << "Unit Price: $" << m_price << endl;
				ostr << "Needed Purchase Fund: $" << (m_qtyNeeded - m_qtyOnHand) * m_price << endl;
			}
		}
		else {
			ostr << m_state;
		}
		return ostr;
	}

	int Item::readSku(istream& is) {
		int sku;
		do {
			sku = ut.getInt(40000, 99999, "SKU: ");
		} while (sku < 40000 || sku > 99999);
		m_sku = sku;
		return sku;
	}

	istream& Item::read(istream& is) {
		if (m_description) {
			delete[] m_description;
			m_description = nullptr;
		}
		m_state.clear();
		
		char tempDesc[1001]; 

		cout << "AMA Item:" << endl
			 << "SKU: " << m_sku << endl
		     << "Description: ";
		is.get(tempDesc, 1000, '\n');
		ut.clearBuffer();

		cout << "Quantity Needed: ";
		m_qtyNeeded = ut.getInt(1, 9999);

		cout << "Quantity On Hand: ";
		m_qtyOnHand = ut.getInt(0, m_qtyNeeded);

		cout << "Unit Price: $";
		m_price = ut.getDouble(0.0, 9999.0);

		if (is.fail()) {
			m_state = "Console entry failed!";
			ut.clearBuffer();
		}
		else {
			ut.aloCpy(m_description, tempDesc);
		}
		return is;
	}
}