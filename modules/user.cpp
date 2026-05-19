#include "user.h"
#include "menu.h"
#include "csv_helper.h"
#include "utils.h"
#include "validator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tabulate/table.hpp>
using namespace std;
using namespace tabulate;

User daftarUser[MAX_USERS];
int jumlahUser = 0;

void loadUsers() {
    ifstream file("data/users.csv");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    jumlahUser = 0;
    while (getline(file, line) && jumlahUser < MAX_USERS) {
        vector<string> fields = splitCSVRow(line);
        if (fields.size() < 7) continue;

        daftarUser[jumlahUser].id = fields[0];
        daftarUser[jumlahUser].name = fields[1];
        daftarUser[jumlahUser].phone = fields[2];
        daftarUser[jumlahUser].username = fields[3];
        daftarUser[jumlahUser].password = fields[4];
        daftarUser[jumlahUser].role = fields[5];
        daftarUser[jumlahUser].isVIP = parseBoolean(fields[6]);
        jumlahUser++;
    }

    file.close();
}

void saveUsers() {
    ofstream file("data/users.csv");
    if (!file.is_open()) {
        cout << "Error: Tidak bisa membuka file users.csv!" << endl;
        return;
    }

    file << "id,name,phone,username,password,role,is_vip" << endl;

    for (int i = 0; i < jumlahUser; i++) {
        file << daftarUser[i].id << ","
             << daftarUser[i].name << ","
             << daftarUser[i].phone << ","
             << daftarUser[i].username << ","
             << daftarUser[i].password << ","
             << daftarUser[i].role << ","
             << (daftarUser[i].isVIP ? "true" : "false") << endl;
    }

    file.close();
}

int findUserByUsername(const string& username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].username == username) {
            return i;
        }
    }
    return -1;
}

int findUserIndexByID(const string& id) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].id == id) {
            return i;
        }
    }
    return -1;
}

void login() {
    string username, password;

    cout << "=================================" << endl;
    cout << "           LOGIN                 " << endl;
    cout << "=================================" << endl;
    cout << "Masukkan username: ";
    getline(cin, username);
    cout << "Masukkan password: ";
    getline(cin, password);

    int idx = findUserByUsername(username);
    if (idx == -1) {
        cout << "Username tidak ditemukan!" << endl;
        pressEnter();
        return;
    }

    if (daftarUser[idx].password != password) {
        cout << "Password salah!" << endl;
        pressEnter();
        return;
    }

    cout << "Selamat datang, " << daftarUser[idx].name << "!" << endl;

    if (daftarUser[idx].role == "admin") {
        showAdminMenu();
    } else {
        showCustomerMenu(daftarUser[idx].id);
    }
}

void registerUser() {
    if (jumlahUser >= MAX_USERS) {
        cout << "Maaf, kapasitas user penuh!" << endl;
        pressEnter();
        return;
    }

    string name, phone, username, password;

    cout << "=================================" << endl;
    cout << "        REGISTER CUSTOMER        " << endl;
    cout << "=================================" << endl;

    cout << "Nama: ";
    getline(cin, name);

    while (true) {
        cout << "Nomor HP: ";
        getline(cin, phone);
        if (isValidPhoneNumber(phone)) break;
        cout << "Nomor HP harus 10-14 digit angka!" << endl;
    }

    while (true) {
        cout << "Username: ";
        getline(cin, username);
        if (findUserByUsername(username) == -1) break;
        cout << "Username sudah digunakan!" << endl;
    }

    cout << "Password: ";
    getline(cin, password);

    int newID = jumlahUser + 1;
    string id = formatID("USR", newID);

    daftarUser[jumlahUser].id = id;
    daftarUser[jumlahUser].name = name;
    daftarUser[jumlahUser].phone = phone;
    daftarUser[jumlahUser].username = username;
    daftarUser[jumlahUser].password = password;
    daftarUser[jumlahUser].role = "customer";
    daftarUser[jumlahUser].isVIP = false;
    jumlahUser++;

    saveUsers();
    cout << "Registrasi berhasil! ID Anda: " << id << endl;
    pressEnter();
}

void displayAllUsers() {
    if (jumlahUser == 0) {
        cout << "Belum ada user terdaftar." << endl;
        pressEnter();
        return;
    }

    Table table;
    table.add_row({"No", "Nama", "No. HP", "Role", "VIP"});

    for (int i = 0; i < jumlahUser; i++) {
        table.add_row({
            intToString(i + 1),
            daftarUser[i].name,
            daftarUser[i].phone,
            daftarUser[i].role,
            daftarUser[i].isVIP ? "Ya" : "Tidak"
        });
    }

    table.column(0).format().width(5);
    table.column(1).format().width(20);
    table.column(2).format().width(15);
    table.column(3).format().width(10);
    table.column(4).format().width(5);

    cout << table << endl;
    pressEnter();
}

void deleteUser() {
    int customerIdx[MAX_USERS];
    int count = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].role == "customer") {
            customerIdx[count] = i;
            count++;
        }
    }

    if (count == 0) {
        cout << "Tidak ada customer yang terdaftar." << endl;
        pressEnter();
        return;
    }

    cout << "=================================" << endl;
    cout << "   PILIH CUSTOMER YANG DIHAPUS   " << endl;
    cout << "=================================" << endl;
    for (int i = 0; i < count; i++) {
        int idx = customerIdx[i];
        cout << (i + 1) << ". " << daftarUser[idx].name
             << " - " << daftarUser[idx].phone
             << (daftarUser[idx].isVIP ? " (VIP)" : "") << endl;
    }

    int pilihan;
    string input;
    while (true) {
        cout << "Pilih customer (1-" << count << "): ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> pilihan && ss.eof() && pilihan >= 1 && pilihan <= count) break;
        cout << "Masukkan angka 1 - " << count << "!" << endl;
    }

    int idx = customerIdx[pilihan - 1];

    cout << "Hapus customer " << daftarUser[idx].name << "? (y/n): ";
    string confirm;
    getline(cin, confirm);
    if (confirm != "y" && confirm != "Y") {
        cout << "Penghapusan dibatalkan." << endl;
        pressEnter();
        return;
    }

    for (int i = idx; i < jumlahUser - 1; i++) {
        daftarUser[i] = daftarUser[i + 1];
    }
    jumlahUser--;

    saveUsers();
    cout << "User berhasil dihapus!" << endl;
    pressEnter();
}

void setVIPStatus() {
    int customerIdx[MAX_USERS];
    int count = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].role == "customer") {
            customerIdx[count] = i;
            count++;
        }
    }

    if (count == 0) {
        cout << "Tidak ada customer yang terdaftar." << endl;
        pressEnter();
        return;
    }

    cout << "=================================" << endl;
    cout << "   PILIH CUSTOMER (ATUR VIP)     " << endl;
    cout << "=================================" << endl;
    for (int i = 0; i < count; i++) {
        int idx = customerIdx[i];
        cout << (i + 1) << ". " << daftarUser[idx].name
             << " - " << daftarUser[idx].phone
             << (daftarUser[idx].isVIP ? " (VIP)" : " (Reguler)") << endl;
    }

    int pilihan;
    string input;
    while (true) {
        cout << "Pilih customer (1-" << count << "): ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> pilihan && ss.eof() && pilihan >= 1 && pilihan <= count) break;
        cout << "Masukkan angka 1 - " << count << "!" << endl;
    }

    int idx = customerIdx[pilihan - 1];

    daftarUser[idx].isVIP = !daftarUser[idx].isVIP;
    saveUsers();

    cout << "Status VIP user " << daftarUser[idx].name
         << " sekarang: " << (daftarUser[idx].isVIP ? "VIP" : "Reguler") << endl;
    pressEnter();
}
