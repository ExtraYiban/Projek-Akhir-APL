#include "user.h"
#include "iphone.h"
#include "rental.h"
#include "reservation.h"
#include "menu.h"
#include <iostream>
using namespace std;

int main() {
    loadIPhones();
    loadUsers();
    loadRentals();
    loadReservations();

    showMainMenu();

    return 0;
}
