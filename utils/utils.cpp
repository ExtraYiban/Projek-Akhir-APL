#include "utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

void clearScreen() {
    for (int i = 0; i < 40; i++) {
        cout << endl;
    }
}

void pressEnter() {
    cout << endl << "Tekan Enter untuk melanjutkan..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate() {
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

int stringToInt(const string& str) {
    stringstream ss(str);
    int val = 0;
    ss >> val;
    return val;
}

float stringToFloat(const string& str) {
    stringstream ss(str);
    float val = 0;
    ss >> val;
    return val;
}

string intToString(int val) {
    stringstream ss;
    ss << val;
    return ss.str();
}

string floatToString(float val) {
    stringstream ss;
    ss << fixed << setprecision(0) << val;
    return ss.str();
}

string formatID(const string& prefix, int num) {
    stringstream ss;
    ss << prefix;
    ss << setw(3) << setfill('0') << num;
    return ss.str();
}
