#include "iphone.h"
#include "csv_helper.h"
#include "utils.h"
#include "validator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tabulate/table.hpp>
using namespace std;
using namespace tabulate;

iPhone daftarIPhone[MAX_IPHONES];
int jumlahIPhone = 0;

void loadIPhones() {
    ifstream file("data/iphones.csv");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    jumlahIPhone = 0;
    while (getline(file, line) && jumlahIPhone < MAX_IPHONES) {
        vector<string> fields = splitCSVRow(line);
        if (fields.size() < 6) continue;

        daftarIPhone[jumlahIPhone].id = fields[0];
        daftarIPhone[jumlahIPhone].name = fields[1];
        daftarIPhone[jumlahIPhone].storage = fields[2];
        daftarIPhone[jumlahIPhone].rentPrice = stringToFloat(fields[3]);
        daftarIPhone[jumlahIPhone].status = fields[4];
        daftarIPhone[jumlahIPhone].totalRented = stringToInt(fields[5]);
        jumlahIPhone++;
    }

    file.close();
}

void saveIPhones() {
    ofstream file("data/iphones.csv");
    if (!file.is_open()) {
        cout << "Error: Tidak bisa membuka file iphones.csv!" << endl;
        return;
    }

    file << "id,name,storage,rent_price,status,total_rented" << endl;

    for (int i = 0; i < jumlahIPhone; i++) {
        file << daftarIPhone[i].id << ","
             << daftarIPhone[i].name << ","
             << daftarIPhone[i].storage << ","
             << floatToString(daftarIPhone[i].rentPrice) << ","
             << daftarIPhone[i].status << ","
             << intToString(daftarIPhone[i].totalRented) << endl;
    }

    file.close();
}

int findiPhoneByID(const string& id) {
    for (int i = 0; i < jumlahIPhone; i++) {
        if (daftarIPhone[i].id == id) {
            return i;
        }
    }
    return -1;
}

void tambahIPhone() {
    if (jumlahIPhone >= MAX_IPHONES) {
        cout << "Kapasitas iPhone penuh!" << endl;
        pressEnter();
        return;
    }

    string name, storage;
    float price;

    cout << "Nama iPhone: ";
    getline(cin, name);
    cout << "Storage: ";
    getline(cin, storage);
    price = getValidFloat("Harga sewa per hari: ");

    int newID = jumlahIPhone + 1;
    string id = formatID("IP", newID);

    daftarIPhone[jumlahIPhone].id = id;
    daftarIPhone[jumlahIPhone].name = name;
    daftarIPhone[jumlahIPhone].storage = storage;
    daftarIPhone[jumlahIPhone].rentPrice = price;
    daftarIPhone[jumlahIPhone].status = "available";
    daftarIPhone[jumlahIPhone].totalRented = 0;
    jumlahIPhone++;

    saveIPhones();
    cout << "iPhone " << name << " berhasil ditambahkan dengan ID " << id << endl;
    pressEnter();
}

void editIPhone() {
    if (jumlahIPhone == 0) {
        cout << "Belum ada iPhone terdaftar." << endl;
        pressEnter();
        return;
    }

    cout << "=================================" << endl;
    cout << "    PILIH IPHONE YANG DIEDIT     " << endl;
    cout << "=================================" << endl;
    for (int i = 0; i < jumlahIPhone; i++) {
        cout << (i + 1) << ". " << daftarIPhone[i].name << " ("
             << daftarIPhone[i].storage << ") - "
             << (daftarIPhone[i].status == "available" ? "Tersedia" : "Disewa") << endl;
    }

    int pilihan;
    string input;
    while (true) {
        cout << "Pilih iPhone (1-" << jumlahIPhone << "): ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> pilihan && ss.eof() && pilihan >= 1 && pilihan <= jumlahIPhone) break;
        cout << "Masukkan angka 1 - " << jumlahIPhone << "!" << endl;
    }

    int idx = pilihan - 1;

    cout << "Edit iPhone: " << daftarIPhone[idx].name << endl;
    cout << "Nama baru (kosongkan jika tidak diubah): ";
    string name;
    getline(cin, name);
    if (name != "") {
        daftarIPhone[idx].name = name;
    }

    cout << "Storage baru (kosongkan jika tidak diubah): ";
    string storage;
    getline(cin, storage);
    if (storage != "") {
        daftarIPhone[idx].storage = storage;
    }

    cout << "Harga sewa baru (0 jika tidak diubah): ";
    string priceStr;
    getline(cin, priceStr);
    if (priceStr != "0" && priceStr != "") {
        daftarIPhone[idx].rentPrice = stringToFloat(priceStr);
    }

    saveIPhones();
    cout << "iPhone berhasil diedit!" << endl;
    pressEnter();
}

void hapusIPhone() {
    if (jumlahIPhone == 0) {
        cout << "Belum ada iPhone terdaftar." << endl;
        pressEnter();
        return;
    }

    cout << "=================================" << endl;
    cout << "   PILIH IPHONE YANG DIHAPUS     " << endl;
    cout << "=================================" << endl;
    for (int i = 0; i < jumlahIPhone; i++) {
        cout << (i + 1) << ". " << daftarIPhone[i].name << " ("
             << daftarIPhone[i].storage << ") - "
             << (daftarIPhone[i].status == "available" ? "Tersedia" : "Disewa") << endl;
    }

    int pilihan;
    string input;
    while (true) {
        cout << "Pilih iPhone (1-" << jumlahIPhone << "): ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> pilihan && ss.eof() && pilihan >= 1 && pilihan <= jumlahIPhone) break;
        cout << "Masukkan angka 1 - " << jumlahIPhone << "!" << endl;
    }

    int idx = pilihan - 1;

    cout << "Apakah Anda yakin ingin menghapus " << daftarIPhone[idx].name << "? (y/n): ";
    string confirm;
    getline(cin, confirm);
    if (confirm != "y" && confirm != "Y") {
        cout << "Penghapusan dibatalkan." << endl;
        pressEnter();
        return;
    }

    for (int i = idx; i < jumlahIPhone - 1; i++) {
        daftarIPhone[i] = daftarIPhone[i + 1];
    }
    jumlahIPhone--;

    saveIPhones();
    cout << "iPhone berhasil dihapus!" << endl;
    pressEnter();
}

void displayAllIPhones() {
    if (jumlahIPhone == 0) {
        cout << "Belum ada iPhone terdaftar." << endl;
        pressEnter();
        return;
    }

    Table table;
    table.add_row({"No", "Nama iPhone", "Storage", "Harga", "Status", "Disewa"});

    for (int i = 0; i < jumlahIPhone; i++) {
        table.add_row({
            intToString(i + 1),
            daftarIPhone[i].name,
            daftarIPhone[i].storage,
            intToString(daftarIPhone[i].rentPrice),
            daftarIPhone[i].status == "available" ? "Tersedia" : "Disewa",
            intToString(daftarIPhone[i].totalRented)
        });
    }

    table.column(0).format().width(5);
    table.column(1).format().width(20);
    table.column(2).format().width(10);
    table.column(3).format().width(10);
    table.column(4).format().width(10);
    table.column(5).format().width(8);

    cout << table << endl;
    pressEnter();
}

void searchIPhone() {
    cout << "Masukkan nama iPhone yang dicari: ";
    string keyword;
    getline(cin, keyword);

    Table table;
    table.add_row({"No", "Nama iPhone", "Storage", "Harga/Hari", "Status"});

    int count = 0;
    for (int i = 0; i < jumlahIPhone; i++) {
        string lowerName = "";
        string lowerKeyword = "";
        for (char c : daftarIPhone[i].name) lowerName += tolower(c);
        for (char c : keyword) lowerKeyword += tolower(c);

        if (lowerName.find(lowerKeyword) != string::npos) {
            count++;
            table.add_row({
                intToString(count),
                daftarIPhone[i].name,
                daftarIPhone[i].storage,
                "Rp" + intToString(daftarIPhone[i].rentPrice),
                daftarIPhone[i].status == "available" ? "Tersedia" : "Disewa"
            });
        }
    }

    if (count == 0) {
        cout << "Tidak ada iPhone yang cocok dengan \"" << keyword << "\"" << endl;
    } else {
        table.column(0).format().width(5);
        table.column(1).format().width(20);
        table.column(2).format().width(10);
        table.column(3).format().width(14);
        table.column(4).format().width(10);

        cout << table << endl;
    }

    pressEnter();
}

void displayAvailableIPhones() {
    int count = 0;
    int availIdx[MAX_IPHONES];
    for (int i = 0; i < jumlahIPhone; i++) {
        if (daftarIPhone[i].status == "available") {
            availIdx[count] = i;
            count++;
        }
    }

    if (count == 0) {
        cout << "Tidak ada iPhone yang tersedia saat ini." << endl;
        return;
    }

    Table table;
    table.add_row({"No", "Nama iPhone", "Storage", "Harga/Hari"});

    for (int i = 0; i < count; i++) {
        int idx = availIdx[i];
        table.add_row({
            intToString(i + 1),
            daftarIPhone[idx].name,
            daftarIPhone[idx].storage,
            "Rp" + intToString(daftarIPhone[idx].rentPrice)
        });
    }

    table.column(0).format().width(5);
    table.column(1).format().width(20);
    table.column(2).format().width(10);
    table.column(3).format().width(14);

    cout << table << endl;
}

