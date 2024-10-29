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

#include "AidMan.h"

namespace sdds {

	unsigned int AidMan::menu() const {
		cout << "Aid Management System" << endl;
		cout << "Date: " << Date() << endl;
		cout << "Data file: " << (m_fileName ? m_fileName : "No file") << endl;
		cout << "---------------------------------" << endl;
		return m_MainMenu.run();
	}
	
	AidMan::AidMan(const char* fileName) :
		m_MainMenu("List Items\t"
				   "Add Item\t"
				   "Remove Item\t"
				   "Update Quantity\t"
				   "Sort\t"
				   "Ship Items\t"
				   "New/Open Aid Database") {
		if (fileName) {
			ut.aloCpy(m_fileName, fileName);
		}
		else {		
			m_fileName = nullptr;
		}
		m_numItems = 0;
		for (int i = 0; i < sdds_max_num_items; i++) {
			m_items[i] = nullptr;
		}
	}

	AidMan::~AidMan() {
		deallocate();
	}

	void AidMan::run() {
		unsigned int option;
		do {
			option = menu();
			if (option != 0 && !m_fileName && option != 7) {
				option = 7;				
			}
			switch (option) {
				case 1:
					cout << endl << "****List Items****" << endl;					
					list();					
					break;
				case 2:
					cout << endl << "****Add Item****" << endl;
					addItem();
					break;
				case 3:
					cout << endl << "****Remove Item****" << endl;
					removeItem();
					break;
				case 4:
					cout << endl << "****Update Quantity****" << endl;
					updateQuantity();
					break;
				case 5:
					cout << endl << "****Sort****" << endl;
					sort();
					break;
				case 6:
					cout << endl << "****Ship Items****" << endl;
					shipItems();
					break;
				case 7:
					cout << endl << "****New/Open Aid Database****" << endl;				
					load();					
					break;	
			}
		} while (option != 0);
		save();
		cout << "Exiting Program!" << endl;
	}

	void AidMan::save() const {
		if (m_fileName != nullptr) {
			ofstream ofstr(m_fileName);
			for (int i = 0; i < m_numItems; i++) {
				m_items[i]->save(ofstr);
				ofstr << endl;
			};
			ofstr.close();
		};
	}

	void AidMan::deallocate() {
		for (int i = 0; i < m_numItems; i++) {
			delete m_items[i];
		};
		delete[] m_fileName;
		m_numItems = 0;
	};	

	bool AidMan::load() {
		save();
		deallocate();
		string tempName;

		cout << "Enter file name: ";
		getline(cin, tempName);
		ut.aloCpy(m_fileName, tempName.c_str()); 

		ifstream ifstr(m_fileName);
		int recordsLoaded = 0;

		if (!ifstr) {

			cout << "Failed to open " << m_fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;

			int option = ut.getInt(0, 1, "> ");
			if (option == 1) {
				ofstream(m_fileName).close();
			}
			return false; 
		}
		
		while (ifstr.peek() != EOF) {
			char c = ifstr.peek();
			int digit = c - '0';
			if (digit >= 1 && digit <= 3) {
				m_items[m_numItems] = new Perishable();
			}
			else if (digit >= 4 && digit <= 9) {
				m_items[m_numItems] = new Item();
			}
			else {
				cout << "Invalid record." << endl;
				continue; 
			}

			if (m_items[m_numItems]->load(ifstr)) {
				recordsLoaded++;
				m_numItems++;
			}
			else {
				delete m_items[m_numItems]; 
				m_items[m_numItems] = nullptr;
			}
		}
		cout << recordsLoaded << " records loaded!" << endl << endl;
		return recordsLoaded > 0;
	}


	int AidMan::list(const char* sub_desc) {
		int productsPrinted = 0;
		int indexesPrinted[sdds_max_num_items];

		if (m_numItems > 0) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			for (int i = 0; i < m_numItems; i++) {
				if (sub_desc == nullptr || strstr(m_items[i]->description(), sub_desc) != nullptr) {
					
					cout << " " << setw(3) << setfill(' ') << i + 1 << " | ";
					m_items[i]->linear(true);
					m_items[i]->display(cout);
					cout << endl;

					indexesPrinted[productsPrinted++] = i;
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		if (productsPrinted == 0) {
			cout << "The list is empty!" << endl;
		}
		if (productsPrinted > 0 && !sub_desc) {
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;
			cout << "> ";
			if (cin.peek() == '\n') {
				cin.get();
				cout << endl;
			}
			else {
				int option = ut.getInt(1, productsPrinted);
				m_items[indexesPrinted[option - 1]]->linear(false);
				m_items[indexesPrinted[option - 1]]->display(cout);
				cout << endl << endl;
			}
		}
		return productsPrinted;
	}

	int AidMan::search(int sku) const {
		for (int i = 0; i < m_numItems; i++) {
			if (*m_items[i] == sku) {
				return i;
			}
		}
		return -1;
	}

	void AidMan::addItem() {
		if (m_numItems >= sdds_max_num_items) {
			cout << "Database full!" << endl << endl;
			return;
		}

		int option = ut.getInt(0, 2, "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ");
		if (option == 0) {
			cout << "Aborted" << endl << endl;
			return;
		}

		iProduct* product {};
		if (option == 1) {
			product = new Perishable();
		}
		else if (option == 2) {
			product = new Item();
		}

		int sku = product->readSku(cin);

		int foundIndex = search(sku); 
		if (foundIndex != -1) { 
			cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl << endl;
			delete product;
			return;
		}
		
		product->read(cin); 

		if (*product) {
			m_items[m_numItems++] = product;
		}
		else {
			product->display(cout);
			delete product;
		}
	}

	void AidMan::remove(int index) {
		if (index >= 0 && index < m_numItems) {
			delete m_items[index];  

			for (int i = index; i < m_numItems - 1; i++) {
				m_items[i] = m_items[i + 1];
			}
			m_items[m_numItems - 1] = nullptr; 
			m_numItems--;  
		}
	}

	void AidMan::removeItem() {
		cout << "Item description: ";
		string description; 
		getline(cin, description);

		int listed = list(description.c_str());

		if (listed > 0) {

			int sku = ut.getInt(10000, 99999, "Enter SKU: ");
			
			int i = search(sku);
			if (i == -1) {
				cout << "SKU not found!" << endl;
				return;
			}

			cout << "Following item will be removed: " << endl;

			m_items[i]->linear(false);
			m_items[i]->display(cout);

			int option = ut.getInt(0, 1, "\nAre you sure?\n1- Yes!\n0- Exit\n> ");
			if (option == 1) {
				remove(i);
				cout << "Item removed!" << endl << endl;
			}
			else {
				cout << "Aborted!" << endl << endl;
			}
		}
		else {
			cout << "No items found with the given description." << endl << endl;
		}
	}

	void AidMan::updateQuantity() {
		cout << "Item description: ";
		string subDescription;
		getline(cin, subDescription); 

		if (list(subDescription.c_str()) == 0) { 
			cout << "No matches found!" << endl;
			return;
		}

		int sku = ut.getInt(10000, 99999, "Enter SKU: ");

		int index = search(sku); 
		if (index == -1) {
			cout << "SKU not found!" << endl;
			return;
		}
		
		int option = ut.getInt(0, 2, "1- Add\n2- Reduce\n0- Exit\n> ");

		if (option == 0) {
			cout << "Aborted!" << endl << endl;
			return;
		}
		else if (option == 1) {
			int diff = m_items[index]->qtyNeeded() - m_items[index]->qty();
			if (diff == 0) {
				cout << "Quantity Needed already fulfilled!" << endl << endl;
				return;
			}

			int add = ut.getInt(1, diff, "Quantity to add: ");			
			*m_items[index] += add; 
			cout << add << " items added!" << endl << endl;
		}
		else if (option == 2) {
			if (m_items[index]->qty() == 0) {
				cout << "Quantity on hand is zero" << endl << endl;
				return;
			}
			int reduce = ut.getInt(1, m_items[index]->qty(), "Quantity to reduce: ");
			*m_items[index] -= reduce; 
			cout << reduce << " items removed!" << endl << endl;
		}
	}
		
	void AidMan::sort() {
		int i = 0;
		int j = 0;
		for (i = 0; i < m_numItems - 1; i++) {
			for (j = 0; j < m_numItems - i - 1; j++) {
				if ((m_items[j]->qtyNeeded() - m_items[j]->qty()) < (m_items[j + 1]->qtyNeeded() - m_items[j + 1]->qty())) {
					iProduct* temp = m_items[j];
					m_items[j] = m_items[j + 1];
					m_items[j + 1] = temp;
				}
			}
		}
		cout << "Sort completed!" << endl << endl;
	}
	
	void AidMan::shipItems() {
		ofstream f("shippingOrder.txt");
		if (!f) {
			cout << "Failed to create file." << endl;
			return;
		}

		Date currDate;
		f << "Shipping Order, Date: " << currDate << endl;		
		f << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		f << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		int countShipped = 0;		
		for (int i = 0; i < m_numItems; i++) {			
			
			if (m_items[i]->qtyNeeded() == m_items[i]->qty()) { 
											
				m_items[i]->linear(true);
				f << setw(4) << right << countShipped + 1 << " | " << *m_items[i] << endl;
								
				delete m_items[i];
				for (int j = i; j < m_numItems - 1; j++) {
					m_items[j] = m_items[j + 1];
				}
				m_items[m_numItems - 1] = nullptr;
				m_numItems--;
				countShipped++;
				i--; 
			}
		}
		f << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		f.close();
		cout << "Shipping Order for " << countShipped << " times saved!" << endl << endl;
	}
}