#pragma once
#include "structs.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Role Routing
void menuAdmin(vector<iPhone> &ip, vector<User> &usr, vector<Reservasi> &res,
               vector<Transaksi> &trx);
void menuCustomer(string userId, vector<iPhone> &ip, vector<User> &usr, vector<Reservasi> &res,
                  vector<Transaksi> &trx);

// Core Rental (Admin & Customer)
void tambahiPhone(vector<iPhone> &data);
void editiPhone(vector<iPhone> &data);
void hapusiPhone(vector<iPhone> &data);
void tampilkaniPhone(const vector<iPhone> &data);
void tampilkanDetailiPhone(const iPhone &ip);
void filteriPhoneByStatus(const vector<iPhone> &data, StatusiPhone status);
iPhone *cariiPhone(const vector<iPhone> &data, string keyword);
void updateStatusiPhone(iPhone *ptr, StatusiPhone baru);

// User Manager (Admin & Customer)
extern vector<User> usersDB;
bool login();
void registerUser();
void tambahUser(vector<User> &data);
void editUser(vector<User> &data);
void hapusUser(vector<User> &data);
void registerUser(vector<User> &data);
User *cariUser(const vector<User> &data, string id);
void tampilkanRiwayatUser(const vector<Transaksi> &trx, const vector<Reservasi> &res,
                          string userId);
void lihatPosisiAntrian(const vector<Reservasi> &res, string userId);
void tampilkanDetailUser(const User &u);
void tampilkanDetailReservasi(const Reservasi &r);
void tampilkanDetailTransaksi(const Transaksi &t);

// Priority & Queue (Admin & Customer)
void urutkanAntrian(vector<Reservasi> &antrian, vector<User> &usr);
void prosesAntrianOtomatis(vector<Reservasi> &antrian, vector<iPhone> &stok,
                           vector<Transaksi> &histori, vector<User> &usr);

// Transaction & Cost
void checkOutiPhone(vector<Reservasi> &antrian, vector<iPhone> &stok, vector<Transaksi> &histori,
                    vector<User> &usr);
void checkIniPhone(vector<Transaksi> &histori, vector<iPhone> &stok, vector<User> &usr);
void batalkanReservasi(vector<Reservasi> &antrian, vector<iPhone> &stok, string userId);
void batalkanReservasiByAdmin(vector<Reservasi> &antrian, vector<iPhone> &stok);
double hitungBiaya(const iPhone &ip, int durasi, int terlambat, UserLevel level);

// Reports (Admin Only)
void laporanPendapatan(const vector<Transaksi> &histori);
void laporaniPhonePopuler(const vector<Transaksi> &histori);
void laporanUserAktif(const vector<Transaksi> &histori, const vector<User> &users);

// Validator & I/O
bool validasiTanggal(string tgl);
int tanggalToInt(string tgl);
int selisihHari(string mulai, string selesai);
bool cekBentrok(const vector<JadwalSewa> &jadwal, string mulai, string selesai);
void loadData(vector<iPhone> &ip, vector<User> &usr, vector<Reservasi> &res,
              vector<Transaksi> &trx);
void simpanData(const vector<iPhone> &ip, const vector<User> &usr, const vector<Reservasi> &res,
                const vector<Transaksi> &trx);

// UI
void header(const string &judul);
string prosesLogin(vector<User> &users);

