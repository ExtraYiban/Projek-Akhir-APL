#pragma once
#include "constants.h"
#include <string>
#include <vector>
using namespace std;

struct JadwalSewa {
    string tglMulai;
    string tglSelesai;
};

struct iPhone {
    string id;
    string model;
    double hargaPerHari;
    StatusiPhone status;
    string kondisi;
    vector<JadwalSewa> jadwal;
};

struct User {
    string id;
    string username;
    string password;
    string role; // "Admin" atau "Customer"
    UserLevel level;
    int totalSewa;
};

struct Reservasi {
    string idReservasi;
    string userId;
    string iPhoneId;
    string tglMulai;
    string tglSelesai;
    bool isActive;
    int waktuBooking;
};

struct Transaksi {
    string idTransaksi;
    string userId;
    string iPhoneId;
    string tglMulai;
    string tglSelesai;
    string tglKembali;
    int durasi;
    double biayaSewa;
    double denda;
    double totalBayar;
};
