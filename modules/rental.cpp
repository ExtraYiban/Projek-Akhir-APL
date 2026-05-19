#include "rental.h"
#include "iphone.h"
#include "user.h"
#include "reservation.h"
#include "csv_helper.h"
#include "utils.h"
#include "validator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tabulate/table.hpp>
using namespace std;
using namespace tabulate;

Rental daftarRental[MAX_RENTALS];
int jumlahRental = 0;

void loadRentals() {
    ifstream file("data/rentals.csv");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    jumlahRental = 0;
    while (getline(file, line) && jumlahRental < MAX_RENTALS) {
        vector<string> fields = splitCSVRow(line);
        if (fields.size() < 7) continue;

        daftarRental[jumlahRental].rentalID = fields[0];
        daftarRental[jumlahRental].userID = fields[1];
        daftarRental[jumlahRental].iphoneID = fields[2];
        daftarRental[jumlahRental].startDate = fields[3];
        daftarRental[jumlahRental].duration = stringToInt(fields[4]);
        daftarRental[jumlahRental].totalPrice = stringToFloat(fields[5]);
        daftarRental[jumlahRental].status = fields[6];
        jumlahRental++;
    }

    file.close();
}

void saveRentals() {
    ofstream file("data/rentals.csv");
    if (!file.is_open()) {
        cout << "Error: Tidak bisa membuka file rentals.csv!" << endl;
        return;
    }

    file << "rental_id,user_id,iphone_id,start_date,duration,total_price,status" << endl;

    for (int i = 0; i < jumlahRental; i++) {
        file << daftarRental[i].rentalID << ","
             << daftarRental[i].userID << ","
             << daftarRental[i].iphoneID << ","
             << daftarRental[i].startDate << ","
             << intToString(daftarRental[i].duration) << ","
             << floatToString(daftarRental[i].totalPrice) << ","
             << daftarRental[i].status << endl;
    }

    file.close();
}

void sewaIPhone(const string& userID) {
    int availIdx[MAX_IPHONES];
    int availCount = 0;
    for (int i = 0; i < jumlahIPhone; i++) {
        if (daftarIPhone[i].status == "available") {
            availIdx[availCount] = i;
            availCount++;
        }
    }

    if (availCount == 0) {
        cout << "Tidak ada iPhone yang tersedia saat ini." << endl;
        pressEnter();
        return;
    }

    cout << "=================================" << endl;
    cout << "    PILIH iPhone TERSEDIA        " << endl;
    cout << "=================================" << endl;
    for (int i = 0; i < availCount; i++) {
        int idx = availIdx[i];
        cout << (i + 1) << ". " << daftarIPhone[idx].name << " ("
             << daftarIPhone[idx].storage << ") - Rp"
             << floatToString(daftarIPhone[idx].rentPrice) << "/hari" << endl;
    }

    int pilihan;
    string input;
    while (true) {
        cout << "Pilih iPhone (1-" << availCount << "): ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> pilihan && ss.eof() && pilihan >= 1 && pilihan <= availCount) break;
        cout << "Masukkan angka 1 - " << availCount << "!" << endl;
    }

    int idx = availIdx[pilihan - 1];

    string startDate;
    while (true) {
        cout << "Tanggal mulai sewa (YYYY-MM-DD): ";
        getline(cin, startDate);
        if (isValidDate(startDate)) break;
        cout << "Format tanggal salah! Gunakan YYYY-MM-DD" << endl;
    }

    int duration = getValidInt("Durasi sewa (hari): ");
    if (duration < 1) {
        cout << "Durasi minimal 1 hari!" << endl;
        pressEnter();
        return;
    }

    float totalPrice = daftarIPhone[idx].rentPrice * duration;

    cout << "=================================" << endl;
    cout << "RINCIAN SEWA:" << endl;
    cout << "iPhone: " << daftarIPhone[idx].name << " (" << daftarIPhone[idx].storage << ")" << endl;
    cout << "Durasi: " << duration << " hari" << endl;
    cout << "Harga/hari: Rp" << floatToString(daftarIPhone[idx].rentPrice) << endl;
    cout << "Total: Rp" << floatToString(totalPrice) << endl;
    cout << "=================================" << endl;
    cout << "Konfirmasi sewa? (y/n): ";
    string confirm;
    getline(cin, confirm);
    if (confirm != "y" && confirm != "Y") {
        cout << "Penyewaan dibatalkan." << endl;
        pressEnter();
        return;
    }

    int newID = jumlahRental + 1;
    string rentalID = formatID("RNT", newID);

    daftarRental[jumlahRental].rentalID = rentalID;
    daftarRental[jumlahRental].userID = userID;
    daftarRental[jumlahRental].iphoneID = daftarIPhone[idx].id;
    daftarRental[jumlahRental].startDate = startDate;
    daftarRental[jumlahRental].duration = duration;
    daftarRental[jumlahRental].totalPrice = totalPrice;
    daftarRental[jumlahRental].status = "active";
    jumlahRental++;

    daftarIPhone[idx].status = "rented";
    daftarIPhone[idx].totalRented++;

    saveRentals();
    saveIPhones();

    cout << "Penyewaan berhasil! ID Rental: " << rentalID << endl;
    pressEnter();
}

void returnIPhone() {
    int activeIdx[MAX_RENTALS];
    int activeCount = 0;
    for (int i = 0; i < jumlahRental; i++) {
        if (daftarRental[i].status == "active") {
            activeIdx[activeCount] = i;
            activeCount++;
        }
    }

    if (activeCount == 0) {
        cout << "Tidak ada penyewaan aktif saat ini." << endl;
        pressEnter();
        return;
    }

    cout << "=================================" << endl;
    cout << "   PILIH PENYEWAAN AKTIF         " << endl;
    cout << "=================================" << endl;
    for (int i = 0; i < activeCount; i++) {
        int idx = activeIdx[i];
        int phoneIdx = findiPhoneByID(daftarRental[idx].iphoneID);
        string phoneName = phoneIdx != -1 ? daftarIPhone[phoneIdx].name : daftarRental[idx].iphoneID;
        int userIdx = findUserIndexByID(daftarRental[idx].userID);
        string userName = userIdx != -1 ? daftarUser[userIdx].name : daftarRental[idx].userID;
        cout << (i + 1) << ". " << phoneName << " - " << userName
             << " - " << daftarRental[idx].startDate
             << " (" << daftarRental[idx].duration << " hari)"
             << " - Rp" << floatToString(daftarRental[idx].totalPrice) << endl;
    }

    int pilihan;
    string input;
    while (true) {
        cout << "Pilih penyewaan (1-" << activeCount << "): ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> pilihan && ss.eof() && pilihan >= 1 && pilihan <= activeCount) break;
        cout << "Masukkan angka 1 - " << activeCount << "!" << endl;
    }

    int idx = activeIdx[pilihan - 1];

    daftarRental[idx].status = "completed";

    int phoneIdx = findiPhoneByID(daftarRental[idx].iphoneID);
    if (phoneIdx != -1) {
        daftarIPhone[phoneIdx].status = "available";
    }

    saveRentals();
    saveIPhones();

    cout << "iPhone berhasil dikembalikan!" << endl;

    processReservations(daftarRental[idx].iphoneID);

    pressEnter();
}

void displayAllRentals() {
    if (jumlahRental == 0) {
        cout << "Belum ada transaksi penyewaan." << endl;
        pressEnter();
        return;
    }

    Table table;
    table.add_row({"No", "User", "iPhone", "Tgl Mulai", "Durasi", "Total", "Status"});

    for (int i = 0; i < jumlahRental; i++) {
        int phoneIdx = findiPhoneByID(daftarRental[i].iphoneID);
        string phoneName = phoneIdx != -1 ? daftarIPhone[phoneIdx].name : daftarRental[i].iphoneID;
        int userIdx = findUserIndexByID(daftarRental[i].userID);
        string userName = userIdx != -1 ? daftarUser[userIdx].name : daftarRental[i].userID;
        table.add_row({
            intToString(i + 1),
            userName,
            phoneName,
            daftarRental[i].startDate,
            intToString(daftarRental[i].duration) + " hari",
            "Rp" + floatToString(daftarRental[i].totalPrice),
            daftarRental[i].status == "active" ? "Aktif" : "Selesai"
        });
    }

    table.column(0).format().width(5);
    table.column(1).format().width(16);
    table.column(2).format().width(20);
    table.column(3).format().width(12);
    table.column(4).format().width(8);
    table.column(5).format().width(14);
    table.column(6).format().width(8);

    cout << table << endl;
    pressEnter();
}

void displayUserRentals(const string& userID) {
    Table table;
    table.add_row({"No", "iPhone", "Tgl Mulai", "Durasi", "Total", "Status"});

    int num = 0;
    for (int i = 0; i < jumlahRental; i++) {
        if (daftarRental[i].userID == userID) {
            num++;
            int phoneIdx = findiPhoneByID(daftarRental[i].iphoneID);
            string phoneName = phoneIdx != -1 ? daftarIPhone[phoneIdx].name : "Unknown";

            table.add_row({
                intToString(num),
                phoneName,
                daftarRental[i].startDate,
                intToString(daftarRental[i].duration) + " hari",
                "Rp" + floatToString(daftarRental[i].totalPrice),
                daftarRental[i].status == "active" ? "Aktif" : "Selesai"
            });
        }
    }

    if (num == 0) {
        cout << "Anda belum memiliki riwayat penyewaan." << endl;
    } else {
        table.column(0).format().width(5);
        table.column(1).format().width(20);
        table.column(2).format().width(12);
        table.column(3).format().width(8);
        table.column(4).format().width(14);
        table.column(5).format().width(8);

        cout << table << endl;
    }

    pressEnter();
}

void generateReport() {
    float totalPendapatan = 0;
    int totalAktif = 0;
    int totalSelesai = 0;
    int maxRented = -1;
    int maxRentedIdx = -1;

    for (int i = 0; i < jumlahRental; i++) {
        if (daftarRental[i].status == "completed") {
            totalPendapatan += daftarRental[i].totalPrice;
            totalSelesai++;
        } else {
            totalAktif++;
        }
    }

    for (int i = 0; i < jumlahIPhone; i++) {
        if (daftarIPhone[i].totalRented > maxRented) {
            maxRented = daftarIPhone[i].totalRented;
            maxRentedIdx = i;
        }
    }

    Table table;
    table.add_row({"Metrik", "Nilai"});

    table.add_row({"Total Pendapatan", "Rp" + floatToString(totalPendapatan)});
    table.add_row({"Total Transaksi", intToString(jumlahRental)});
    table.add_row({"  - Aktif", intToString(totalAktif)});
    table.add_row({"  - Selesai", intToString(totalSelesai)});
    table.add_row({"Total iPhone", intToString(jumlahIPhone)});

    float rataRata = jumlahRental > 0 ? totalPendapatan / jumlahRental : 0;
    table.add_row({"Rata-rata/Transaksi", "Rp" + floatToString(rataRata)});

    if (maxRentedIdx != -1 && maxRented > 0) {
        table.add_row({"iPhone Terpopuler", daftarIPhone[maxRentedIdx].name + " (" + intToString(maxRented) + "x)"});
    } else {
        table.add_row({"iPhone Terpopuler", "Belum ada data"});
    }

    table.column(0).format().width(24);
    table.column(1).format().width(26);

    cout << table << endl;
    pressEnter();
}
