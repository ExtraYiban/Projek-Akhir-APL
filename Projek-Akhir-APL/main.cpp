#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "helpers.h"

using namespace std;

vector<iPhone> iphonesDB;
vector<Reservasi> reservasiDB;
vector<Transaksi> transaksiDB;

void showWelcomeScreen() {
	cout << endl;
	cout << "=======================================" << endl;
	cout << "   Welcome to iPhone Rental System" << endl;
	cout << "=======================================" << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Exit" << endl;
	cout << "=======================================" << endl;
	cout << "Please select an option: ";
}

void mainApplicationMenu() {
	int choice;
	do {
		cout << endl;
		cout << "=======================================" << endl;
		cout << "             MENU CUSTOMER" << endl;
		cout << "=======================================" << endl;
		cout << "1. Informasi iPhone" << endl;
		cout << "2. Reservasi" << endl;
		cout << "3. Penyewaan Aktif" << endl;
		cout << "4. Riwayat" << endl;
		cout << "5. Logout" << endl;
		cout << "Pilihan: ";

		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input tidak valid. Silakan masukkan angka: ";
		}

		switch (choice) {
			case 1:
				cout << "Membuka Informasi iPhone..." << endl;
				break;
			case 2:
				cout << "Membuka Reservasi..." << endl;
				break;
			case 3:
				cout << "Membuka Penyewaan Aktif..." << endl;
				break;
			case 4:
				cout << "Membuka Riwayat..." << endl;
				break;
			case 5:
				cout << "Logging out..." << endl;
				break;
			default:
				cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
		}
	} while (choice != 5);
}

int main() {
	loadData(iphonesDB, usersDB, reservasiDB, transaksiDB);

	int choice;
	bool isAuthenticated = false;

	while (true) {
		while (!isAuthenticated) {
			showWelcomeScreen();

			while (!(cin >> choice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number: ";
			}

			switch (choice) {
				case 1:
					isAuthenticated = login();
					break;
				case 2:
					registerUser();
					simpanData(iphonesDB, usersDB, reservasiDB, transaksiDB);
					break;
				case 3:
					simpanData(iphonesDB, usersDB, reservasiDB, transaksiDB);
					cout << "Exiting the application. Goodbye!" << endl;
					return 0;
				default:
					cout << "Invalid option. Please try again." << endl;
			}
		}

		if (isAuthenticated) {
			mainApplicationMenu();
			// Once they logout from the main menu, require authentication again
			isAuthenticated = false; 
		}
	}

	return 0;
}




