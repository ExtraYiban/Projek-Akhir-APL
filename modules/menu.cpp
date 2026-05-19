#include "menu.h"
#include "user.h"
#include "iphone.h"
#include "rental.h"
#include "reservation.h"
#include "validator.h"
#include "utils.h"
#include <iostream>
using namespace std;

void showMainMenu() {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "   SISTEM PENYEWAAN IPHONE       " << endl;
        cout << "=================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register Customer" << endl;
        cout << "3. Keluar" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 3);

        switch (pilihan) {
            case 1:
                login();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                cout << "Terima kasih telah menggunakan sistem." << endl;
                break;
        }
    } while (pilihan != 3);
}

void showCustomerMenu(const string& userID) {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "        MENU CUSTOMER            " << endl;
        cout << "=================================" << endl;
        cout << "1. Lihat Daftar iPhone" << endl;
        cout << "2. Cari iPhone" << endl;
        cout << "3. Sewa iPhone" << endl;
        cout << "4. Reservasi iPhone" << endl;
        cout << "5. Status Reservasi Saya" << endl;
        cout << "6. Riwayat Penyewaan Saya" << endl;
        cout << "7. Logout" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 7);

        switch (pilihan) {
            case 1:
                customerLihatIPhone(userID);
                break;
            case 2:
                customerCariIPhone(userID);
                break;
            case 3:
                customerSewa(userID);
                break;
            case 4:
                customerReservasi(userID);
                break;
            case 5:
                customerStatusReservasi(userID);
                break;
            case 6:
                customerRiwayat(userID);
                break;
            case 7:
                cout << "Logout berhasil." << endl;
                break;
        }
    } while (pilihan != 7);
}

void showAdminMenu() {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "         MENU ADMIN              " << endl;
        cout << "=================================" << endl;
        cout << "1. Manajemen iPhone" << endl;
        cout << "2. Manajemen User" << endl;
        cout << "3. Manajemen Penyewaan" << endl;
        cout << "4. Manajemen Reservasi" << endl;
        cout << "5. Laporan" << endl;
        cout << "6. Logout" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 6);

        switch (pilihan) {
            case 1:
                adminManageIPhones();
                break;
            case 2:
                adminManageUsers();
                break;
            case 3:
                adminManageRentals();
                break;
            case 4:
                adminManageReservations();
                break;
            case 5:
                adminViewReports();
                break;
            case 6:
                cout << "Logout berhasil." << endl;
                break;
        }
    } while (pilihan != 6);
}

void customerLihatIPhone(const string&) {
    displayAllIPhones();
}

void customerCariIPhone(const string&) {
    searchIPhone();
}

void customerSewa(const string& userID) {
    sewaIPhone(userID);
}

void customerReservasi(const string& userID) {
    buatReservasi(userID);
}

void customerRiwayat(const string& userID) {
    displayUserRentals(userID);
}

void customerStatusReservasi(const string& userID) {
    displayUserReservations(userID);
}

void adminManageIPhones() {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "     MANAJEMEN IPHONE            " << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah iPhone" << endl;
        cout << "2. Edit iPhone" << endl;
        cout << "3. Hapus iPhone" << endl;
        cout << "4. Lihat Semua iPhone" << endl;
        cout << "5. Cari iPhone" << endl;
        cout << "6. Kembali" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 6);

        switch (pilihan) {
            case 1:
                tambahIPhone();
                break;
            case 2:
                editIPhone();
                break;
            case 3:
                hapusIPhone();
                break;
            case 4:
                displayAllIPhones();
                break;
            case 5:
                searchIPhone();
                break;
            case 6:
                break;
        }
    } while (pilihan != 6);
}

void adminManageUsers() {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "     MANAJEMEN USER              " << endl;
        cout << "=================================" << endl;
        cout << "1. Lihat Semua User" << endl;
        cout << "2. Hapus User" << endl;
        cout << "3. Atur Status VIP" << endl;
        cout << "4. Kembali" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 4);

        switch (pilihan) {
            case 1:
                displayAllUsers();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                setVIPStatus();
                break;
            case 4:
                break;
        }
    } while (pilihan != 4);
}

void adminManageRentals() {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "   MANAJEMEN PENYEWAAN           " << endl;
        cout << "=================================" << endl;
        cout << "1. Lihat Semua Penyewaan" << endl;
        cout << "2. Pengembalian iPhone" << endl;
        cout << "3. Kembali" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 3);

        switch (pilihan) {
            case 1:
                displayAllRentals();
                break;
            case 2:
                returnIPhone();
                break;
            case 3:
                break;
        }
    } while (pilihan != 3);
}

void adminManageReservations() {
    int pilihan;

    do {
        clearScreen();
        cout << "=================================" << endl;
        cout << "   MANAJEMEN RESERVASI           " << endl;
        cout << "=================================" << endl;
        cout << "1. Lihat Semua Reservasi" << endl;
        cout << "2. Kembali" << endl;
        cout << "=================================" << endl;

        pilihan = getMenuChoice(1, 2);

        switch (pilihan) {
            case 1:
                displayAllReservations();
                break;
            case 2:
                break;
        }
    } while (pilihan != 2);
}

void adminViewReports() {
    clearScreen();
    cout << "=================================" << endl;
    cout << "         LAPORAN                 " << endl;
    cout << "=================================" << endl;

    generateReport();

    cout << "=================================" << endl;
    cout << "   DAFTAR RESERVASI (Laporan)    " << endl;
    cout << "=================================" << endl;

    displayAllReservations();
}
