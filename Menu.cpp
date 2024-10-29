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

#include "Menu.h"
#include "Utils.h"
#include <iostream>

using namespace std;

namespace sdds {

	int Menu::optionCount(const char* menuContent) const {
		int count = 1;
		int i = 0;
		while (menuContent[i] != '\0') {
			if (menuContent[i] == '\t') {
				count++;
			}
			i++;
		}
		return count;
	}


	void Menu::aloOptions() {
		if (m_menuContent == nullptr) {
			return;
		}
		m_options = new char* [m_nomOptions];

		int k = 0; 
		int j = 0; 
		for (int i = 0; i < m_nomOptions; i++) {
			int len = 0;
			while (m_menuContent[k] != '\t' && m_menuContent[k] != '\0') {
				len++;
				k++;
			}

			m_options[i] = new char[len + 1]; 
			ut.strCpyFromTo(m_options[i], m_menuContent, j, k);

			if (m_menuContent[k] == '\0') {
				break;
			}
			k++; 
			j = k;
		}
	}

	Menu::Menu(const char* menuContent) {
		m_nomOptions = optionCount(menuContent);
		if (menuContent != nullptr &&
			menuContent[0] != '\0' &&
			m_nomOptions <= MAX_OPTIONS) {
			
			ut.aloCpy(m_menuContent, menuContent);
			aloOptions();
		}
		else {
			m_menuContent = nullptr;
			m_nomOptions = 0;
		}
	}

	Menu::~Menu() {
		delete[] m_menuContent;
		m_menuContent = nullptr;
		if (m_options) {
			for (int i = 0; i < m_nomOptions; i++) {
				delete[] m_options[i];
				m_options[i] = nullptr;
			}
			delete[] m_options;
			m_options = nullptr;
		}		
	}

	unsigned int Menu::run() const {
		int choice = 0;

		if (m_menuContent) {
			for (int i = 0; i < m_nomOptions; ++i) {
				cout << (i + 1) << "- " << m_options[i] << endl;
			}
			cout << "---------------------------------" << endl
				 << "0- Exit" << endl;

			choice = ut.getInt(0, m_nomOptions, "> ");
		}
		else {
			cout << "Invalid Menu!" << endl;
		}
		return choice;
	}	
}