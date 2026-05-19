#ifndef RENTAL_H
#define RENTAL_H

#include <string>
using namespace std;

#define MAX_RENTALS 200

struct Rental {
    string rentalID;
    string userID;
    string iphoneID;
    string startDate;
    int duration;
    float totalPrice;
    string status;
};

extern Rental daftarRental[MAX_RENTALS];
extern int jumlahRental;

void sewaIPhone(const string& userID);
void returnIPhone();
void displayAllRentals();
void displayUserRentals(const string& userID);
void generateReport();
void loadRentals();
void saveRentals();

#endif
