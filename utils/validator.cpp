#include "validator.h"
#include "utils.h"
#include <iostream>
#include <sstream>
using namespace std;

bool isValidPhoneNumber(const string& phone) {
    if (phone.length() < 10 || phone.length() > 14) {
        return false;
    }

    for (char c : phone) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}

bool isValidDate(const string& date) {
    if (date.length() != 10) {
        return false;
    }

    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }

    int month = stringToInt(date.substr(5, 2));
    int day = stringToInt(date.substr(8, 2));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

int getValidInt(const string& prompt) {
    int val;
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        stringstream ss(input);
        if (ss >> val && ss.eof()) {
            return val;
        }

        cout << "Input harus berupa angka!" << endl;
    }
}

float getValidFloat(const string& prompt) {
    float val;
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        stringstream ss(input);
        if (ss >> val && ss.eof()) {
            return val;
        }

        cout << "Input harus berupa angka!" << endl;
    }
}

string getValidString(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int getMenuChoice(int min, int max) {
    int choice;
    string input;

    while (true) {
        cout << "Pilih: ";
        getline(cin, input);

        stringstream ss(input);
        if (ss >> choice && ss.eof() && choice >= min && choice <= max) {
            return choice;
        }

        cout << "Pilihan tidak valid! Masukkan " << min << "-" << max << endl;
    }
}
