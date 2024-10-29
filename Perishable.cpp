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

#include "Perishable.h"
#include "Utils.h"

namespace sdds {

    Perishable::Perishable() : Item() {
		m_instructions = nullptr;
	}
		
	Perishable::Perishable(const Perishable& P) : m_instructions(nullptr) {
		operator=(P);
	}
		
	Perishable& Perishable::operator=(const Perishable& other) {
		if (this != &other) {
			Item::operator=(other); 
			m_expiryDate = other.m_expiryDate;

			if (m_instructions) {
 				delete[] m_instructions; 
				m_instructions = nullptr;
			}
			
			if (other.m_instructions) {
				
				ut.aloCpy(m_instructions, other.m_instructions);				
			}			
		}   
		return *this;
	}	

	Perishable::~Perishable() {
		delete[] m_instructions;
		m_instructions = nullptr;		
	}

	const Date& Perishable::expiry() const {
		return m_expiryDate;
	}

	int Perishable::readSku(istream& is) {
		int sku;
		do {
			sku = ut.getInt(10000, 39999, "SKU: ");
		} while (sku < 10000 || sku > 39999);
		m_sku = sku;
		return sku;
	}

	ofstream& Perishable::save(ofstream& ofs) const {
		Item::save(ofs); 
		if ((*this)) { 
			ofs << '\t';
			if (m_instructions && m_instructions[0] != '\0') {
				ofs << m_instructions;
			}
			Date tempExpiry = m_expiryDate;
			tempExpiry.formatted(false);
			ofs << '\t' << tempExpiry;
		}
		return ofs;
	}

	ifstream& Perishable::load(ifstream& ifs) {
		Item::load(ifs);
		delete[] m_instructions;
		m_instructions = nullptr;
					
		if ('\t' == ifs.peek()) {			
			ut.peekIgnore(ifs);
			m_instructions = nullptr;
			ifs >> m_expiryDate;
			ut.peekIgnore(ifs);
		}
		else {
			m_state.clear();
			char tempInstructions[1001] {};
			ifs.get(tempInstructions, 1000, '\t');
			ut.peekIgnore(ifs);
						
			ut.aloCpy(m_instructions, tempInstructions);

			ifs >> m_expiryDate;
			ut.peekIgnore(ifs);
		}
		if (!ifs) { 
			m_state = "Input file stream read (perishable) failed!";
		}
		return ifs;
	}

	ostream& Perishable::display(ostream& os) const {	
		if (m_state) {
			if (linear()) {
				Item::display(os);
				os << (m_instructions && m_instructions[0] != '\0' ? '*' : ' ');
				os << m_expiryDate;
			}
			else {
				os << "Perishable ";
				Item::display(os);
				os << "Expiry date: " << m_expiryDate << endl;
				if (m_instructions && m_instructions[0] != '\0') {
					os << "Handling Instructions: " << m_instructions << endl;
				}
			}
		}
		else {
			os << m_state;
		}
		return os;
	}		

	istream& Perishable::read(istream& is) {
		Item::read(is);

		if (m_instructions) {
			delete[] m_instructions;
			m_instructions = nullptr;
		}

		cout << "Expiry date (YYMMDD): ";
		is >> m_expiryDate;
		ut.peekIgnore(is); 

		cout << "Handling Instructions, ENTER to skip: ";
		if (is.peek() != '\n') { 
			char tempInstructions[1001] {};
			is.getline(tempInstructions, 1000); 
			ut.aloCpy(m_instructions, tempInstructions);
		}
		else {
			ut.peekIgnore(is);
			cout << endl;
		}

		if (is.fail()) { 
			m_state = "Perishable console data entry failed!";
		}
		return is;
	}
}