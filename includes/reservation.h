#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

#define MAX_RESERVATIONS 100

struct Reservation {
    string reservationID;
    string userID;
    string iphoneID;
    string reservationDate;
    string priority;
    string status;
};

extern Reservation daftarReservasi[MAX_RESERVATIONS];
extern int jumlahReservasi;

void buatReservasi(const string& userID);
void processReservations(const string& iphoneID);
void displayAllReservations();
void displayUserReservations(const string& userID);
void sortReservationsByPriority();
int findReservasiByID(const string& id);
void loadReservations();
void saveReservations();

#endif
