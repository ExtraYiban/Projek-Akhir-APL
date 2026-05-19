#ifndef IPHONE_H
#define IPHONE_H

#include <string>
using namespace std;

#define MAX_IPHONES 100

struct iPhone {
    string id;
    string name;
    string storage;
    float rentPrice;
    string status;
    int totalRented;
};

extern iPhone daftarIPhone[MAX_IPHONES];
extern int jumlahIPhone;

void tambahIPhone();
void editIPhone();
void hapusIPhone();
void displayAllIPhones();
void searchIPhone();
void displayAvailableIPhones();
int findiPhoneByID(const string& id);
void loadIPhones();
void saveIPhones();

#endif
