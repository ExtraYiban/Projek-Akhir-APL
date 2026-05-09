#include "../includes/helpers.h"
#include <iostream>
#include <limits>

using namespace std;

bool login(string& outUserId) {
    string username, password;
    cout << "=== LOGIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (size_t i = 0; i < usersDB.size(); i++) {
        if (usersDB[i].username == username && usersDB[i].password == password) {
            cout << "Login berhasil! Selamat datang " << username << endl;
            outUserId = usersDB[i].id;
            return true;
        }
    }

    cout << "Login gagal! Username atau password salah." << endl;
    return false;
}

void registerUser() {
    registerUser(usersDB);
}

void registerUser(vector<User>& data) {
    User newUser;
    newUser.id = "U" + to_string(data.size() + 1);

    cout << "=== REGISTER ===" << endl;
    cout << "Username: ";
    cin >> newUser.username;
    cout << "Password: ";
    cin >> newUser.password;
    newUser.role = "Customer";

    newUser.level = BARU;
    newUser.totalSewa = 0;

    data.push_back(newUser);
    cout << "Jumlah user sekarang " << data.size() << endl;
    cout << "Registrasi berhasil! ID User: " << newUser.id << endl;
}

User* cariUser(const vector<User>& data, string id) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].id == id) {
            return const_cast<User*>(&data[i]);
        }
    }
    return nullptr;
}

void tampilkanDetailUser(const User& u) {
    cout << "ID: " << u.id << endl;
    cout << "Username: " << u.username << endl;
    cout << "Role: " << u.role << endl;
    cout << "Level: ";
    switch (u.level) {
    case VIP: cout << "VIP"; break;
    case REGULAR: cout << "Regular"; break;
    case BARU: cout << "Baru"; break;
    }
    cout << endl;
    cout << "Total Sewa: " << u.totalSewa << " kali" << endl;
}

void tampilkanRiwayatUser(const vector<Transaksi>& trx, const vector<Reservasi>& res, string userId) {
    header("RIWAYAT PENGGUNA");

    cout << "\n=== Transaksi Selesai ===" << endl;
    bool adaTransaksi = false;
    for (size_t i = 0; i < trx.size(); i++) {
        if (trx[i].userId == userId && trx[i].tglKembali != "-" && !trx[i].tglKembali.empty()) {
            cout << "ID: " << trx[i].idTransaksi
                << " | iPhone: " << trx[i].iPhoneId
                << " | " << trx[i].tglMulai << " - " << trx[i].tglSelesai
                << " | Total: Rp " << trx[i].totalBayar << endl;
            adaTransaksi = true;
        }
    }

    if (!adaTransaksi) {
        cout << "Belum ada transaksi selesai." << endl;
    }

    cout << "\n=== Reservasi Aktif ===" << endl;
    bool adaAktif = false;
    for (size_t i = 0; i < res.size(); i++) {
        if (res[i].userId == userId && res[i].isActive) {
            cout << "ID: " << res[i].idReservasi
                << " | iPhone: " << res[i].iPhoneId
                << " | " << res[i].tglMulai << " - " << res[i].tglSelesai
                << " | Status: Aktif" << endl;
            adaAktif = true;
        }
    }

    if (!adaAktif) {
        cout << "Tidak ada reservasi aktif." << endl;
    }
}

void lihatPosisiAntrian(const vector<Reservasi>& res, string userId) {
    header("POSISI ANTRIAN");

    vector<Reservasi> antrianUser;
    for (size_t i = 0; i < res.size(); i++) {
        if (res[i].userId == userId && res[i].isActive) {
            antrianUser.push_back(res[i]);
        }
    }

    if (antrianUser.empty()) {
        cout << "Anda tidak memiliki reservasi dalam antrian." << endl;
        return;
    }

    cout << "\nReservasi Anda dalam Antrian:" << endl;
    for (size_t i = 0; i < antrianUser.size(); i++) {
        cout << (i + 1) << ". ID: " << antrianUser[i].idReservasi
            << " | iPhone: " << antrianUser[i].iPhoneId
            << " | Waktu Booking: " << antrianUser[i].waktuBooking << endl;
    }
}

void tampilkanDetailReservasi(const Reservasi& r) {
    cout << "Reservasi: " << r.idReservasi << endl;
    cout << "iPhone: " << r.iPhoneId << endl;
    cout << "Periode: " << r.tglMulai << " - " << r.tglSelesai << endl;
    cout << "Status: " << (r.isActive ? "Aktif" : "Tidak Aktif") << endl;
}

void tambahUser(vector<User>& data) {
    User newUser;
    newUser.id = "U" + to_string(data.size() + 1);

    cout << "Username: ";
    cin >> newUser.username;
    cout << "Password: ";
    cin >> newUser.password;
    cout << "Role (Admin/Customer): ";
    cin >> newUser.role;

    int levelChoice;
    cout << "Level (1=VIP, 2=Regular, 3=Baru): ";
    cin >> levelChoice;

    switch (levelChoice) {
    case 1: newUser.level = VIP; break;
    case 2: newUser.level = REGULAR; break;
    default: newUser.level = BARU; break;
    }

    newUser.totalSewa = 0;
    data.push_back(newUser);
    cout << "User berhasil ditambahkan!" << endl;
}

void editUser(vector<User>& data) {
    string id;
    cout << "Masukkan ID User yang akan diedit: ";
    cin >> id;

    User* user = cariUser(data, id);
    if (user == nullptr) {
        cout << "User tidak ditemukan!" << endl;
        return;
    }

    cout << "Username baru: ";
    cin >> user->username;
    cout << "Password baru: ";
    cin >> user->password;

    cout << "User berhasil diupdate!" << endl;
}

void hapusUser(vector<User>& data) {
    string id;
    cout << "Masukkan ID User yang akan dihapus: ";
    cin >> id;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].id == id) {
            data.erase(data.begin() + i);
            cout << "User berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "User tidak ditemukan!" << endl;
}
