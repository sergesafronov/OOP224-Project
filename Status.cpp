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
#include "Status.h"
#include "Utils.h"

namespace sdds {	

	Status::Status(const char* desc) {
		this->m_code = 0;
		if (desc) {
			delete[] m_desc;
			ut.aloCpy(this->m_desc, desc);
		}
		else {
			this->m_desc = nullptr;
		}
	}

	Status::Status(const Status& other) {
		this->m_code = other.m_code;
		if (other.m_desc) {
			delete[] m_desc;
			ut.aloCpy(this->m_desc, other.m_desc);
		}
		else {
			this->m_desc = nullptr;
		}
	}

	Status& Status::operator=(const Status& other) {
		if (this != &other) {
			this->m_code = other.m_code;
			delete[] m_desc;
			m_desc = nullptr;
			if (other.m_desc) {
				ut.aloCpy(this->m_desc, other.m_desc);
			}
		}
		return *this;
	}

	Status& Status::operator=(const char* desc) {
		if (desc != m_desc) {
			delete[] m_desc;
			m_desc = nullptr;
			if (desc) {
				ut.aloCpy(this->m_desc, desc);
			}
		}
		return *this;
	}
	

	Status& Status::operator=(int code) {
		m_code = code;
		return *this;
	}

	Status::~Status() {
		delete[] m_desc;
		m_desc = nullptr;
	}

	Status::operator int() const {
		return m_code;
	}

	Status::operator const char* () const {
		return m_desc;
	}

	Status::operator bool() const {
		return m_desc == nullptr;
	}

	Status& Status::clear() {
		delete[] m_desc;
		m_desc = nullptr;
		m_code = 0;
		return *this;
	}

	ostream& operator<<(ostream& os, const Status& status) {
		if (!status) {
			if (status.m_code != 0) {
				os << "ERR#" << status.m_code << ": ";
			}
			if (status.m_desc) {
				os << status.m_desc;
			}
		}
		return os;
	}
}