#define _CRT_SECURE_NO_WARNINGS
#include "helpers.h"
#include <algorithm>
#include <ctime>
#include <limits>

using namespace std;

void header(const string& judul) {
    cout << "=== " << judul << " ===" << endl;
}

void tampilkanDetailTransaksi(const Transaksi& t) {
    cout << "Transaksi: " << t.idTransaksi << " - " << t.iPhoneId << endl;
}

double hitungBiaya(const iPhone& ip, int durasi, int terlambat, UserLevel level) {
    double total = ip.hargaPerHari * durasi;
    if (level == VIP) {
        total = total * (1.0 - DISKON_VIP);
    }
    total = total + (terlambat * DENDA_PER_HARI);
    return total;
}

void checkOutiPhone(vector<Reservasi>& antrian, vector<iPhone>& stok, vector<Transaksi>& histori, vector<User>& usr) {
    header("BUAT RESERVASI");

    if (stok.empty()) {
        cout << "Tidak ada iPhone tersedia." << endl;
        return;
    }

    cout << "\nDaftar iPhone:" << endl;
    for (size_t i = 0; i < stok.size(); i++) {
        cout << i + 1 << ". " << stok[i].model
            << " | Harga: " << stok[i].hargaPerHari
            << " | Status: " << (stok[i].status == TERSEDIA ? "Tersedia" : "Tidak tersedia") << endl;
    }

    int pilih;
    cout << "Pilih iPhone: ";
    cin >> pilih;

    if (cin.fail() || pilih < 1 || pilih >(int)stok.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    iPhone& selected = stok[pilih - 1];
    if (selected.status != TERSEDIA) {
        cout << "iPhone tidak tersedia!" << endl;
        return;
    }

    string mulai, selesai;
    cout << "Tanggal mulai (YYYY-MM-DD): ";
    cin >> mulai;
    if (!validasiTanggal(mulai)) {
        cout << "Format tanggal salah!" << endl;
        return;
    }

    cout << "Tanggal selesai (YYYY-MM-DD): ";
    cin >> selesai;
    if (!validasiTanggal(selesai)) {
        cout << "Format tanggal salah!" << endl;
        return;
    }

    if (tanggalToInt(mulai) > tanggalToInt(selesai)) {
        cout << "Tanggal tidak valid!" << endl;
        return;
    }

    if (cekBentrok(selected.jadwal, mulai, selesai)) {
        cout << "Jadwal bentrok!" << endl;
        return;
    }

    JadwalSewa j;
    j.tglMulai = mulai;
    j.tglSelesai = selesai;
    selected.jadwal.push_back(j);

    string userId = usr.empty() ? "UNKNOWN" : usr[0].id;

    Reservasi r;
    r.idReservasi = "R" + to_string(antrian.size() + 1);
    r.userId = userId;
    r.iPhoneId = selected.id;
    r.tglMulai = mulai;
    r.tglSelesai = selesai;
    r.isActive = true;
    r.waktuBooking = (int)antrian.size() + 1;

    antrian.push_back(r);
    cout << "\nReservasi berhasil dibuat!" << endl;
}

void checkIniPhone(vector<Transaksi>& histori, vector<iPhone>& stok, vector<User>& usr) {
    header("PENGEMBALIAN IPHONE");

    bool adaTransaksiAktif = false;
    for (size_t i = 0; i < histori.size(); i++) {
        if (histori[i].tglKembali == "-" || histori[i].tglKembali.empty()) {
            adaTransaksiAktif = true;
            break;
        }
    }

    if (!adaTransaksiAktif) {
        cout << "Tidak ada penyewaan aktif yang perlu dikembalikan." << endl;
        return;
    }

    cout << "\nDaftar Penyewaan Aktif:" << endl;
    int no = 1;
    vector<int> indeksAktif;

    for (size_t i = 0; i < histori.size(); i++) {
        if (histori[i].tglKembali == "-" || histori[i].tglKembali.empty()) {
            cout << no << ". ID: " << histori[i].idTransaksi
                << " | iPhone: " << histori[i].iPhoneId
                << " | User: " << histori[i].userId
                << " | Selesai: " << histori[i].tglSelesai << endl;
            indeksAktif.push_back((int)i);
            no++;
        }
    }

    int pilih;
    cout << "\nPilih nomor penyewaan untuk dikembalikan: ";
    cin >> pilih;

    if (cin.fail() || pilih < 1 || pilih >(int)indeksAktif.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    int idx = indeksAktif[pilih - 1];
    Transaksi& trx = histori[idx];

    string tglKembali;
    cout << "Tanggal kembali (YYYY-MM-DD) [kosongkan untuk hari ini]: ";
    cin.ignore();
    getline(cin, tglKembali);

    if (tglKembali.empty()) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
        tglKembali = string(buffer);
    }

    if (!validasiTanggal(tglKembali)) {
        cout << "Format tanggal salah!" << endl;
        return;
    }

    trx.tglKembali = tglKembali;
    int terlambat = 0;
    if (tanggalToInt(tglKembali) > tanggalToInt(trx.tglSelesai)) {
        terlambat = selisihHari(trx.tglSelesai, tglKembali);
    }

    User* u = cariUser(usr, trx.userId);
    UserLevel lvl = u ? u->level : BARU;

    iPhone* ip = cariiPhone(stok, trx.iPhoneId);
    if (ip != nullptr) {
        trx.durasi = selisihHari(trx.tglMulai, trx.tglSelesai);
        if (trx.durasi <= 0) trx.durasi = 1;

        trx.biayaSewa = hitungBiaya(*ip, trx.durasi, 0, lvl);
        trx.denda = terlambat * DENDA_PER_HARI;
        trx.totalBayar = trx.biayaSewa + trx.denda;

        ip->status = TERSEDIA;

        cout << "\n=== STRUK PENGEMBALIAN ===" << endl;
        cout << "ID Transaksi: " << trx.idTransaksi << endl;
        cout << "iPhone: " << trx.iPhoneId << endl;
        cout << "Tanggal Kembali: " << trx.tglKembali << endl;
        cout << "Keterlambatan: " << terlambat << " hari" << endl;
        cout << "Biaya Sewa: Rp " << trx.biayaSewa << endl;
        cout << "Denda: Rp " << trx.denda << endl;
        cout << "Total Bayar: Rp " << trx.totalBayar << endl;
        cout << "==========================" << endl;
        cout << "Pengembalian berhasil. iPhone " << trx.iPhoneId << " tersedia kembali." << endl;
    }
    else {
        cout << "iPhone tidak ditemukan dalam stok!" << endl;
    }
}

void batalkanReservasi(vector<Reservasi>& antrian, vector<iPhone>& stok, string userId) {
    header("BATALKAN RESERVASI");

    bool adaReservasi = false;
    for (size_t i = 0; i < antrian.size(); i++) {
        if (antrian[i].userId == userId && antrian[i].isActive) {
            adaReservasi = true;
            break;
        }
    }

    if (!adaReservasi) {
        cout << "Tidak ada reservasi aktif untuk dibatalkan." << endl;
        return;
    }

    cout << "\nReservasi Aktif Anda:" << endl;
    vector<int> indeksRes;
    int no = 1;
    for (size_t i = 0; i < antrian.size(); i++) {
        if (antrian[i].userId == userId && antrian[i].isActive) {
            cout << no << ". ID: " << antrian[i].idReservasi
                << " | iPhone: " << antrian[i].iPhoneId
                << " | " << antrian[i].tglMulai << " - " << antrian[i].tglSelesai << endl;
            indeksRes.push_back((int)i);
            no++;
        }
    }

    int pilih;
    cout << "\nPilih nomor reservasi untuk dibatalkan: ";
    cin >> pilih;

    if (cin.fail() || pilih < 1 || pilih >(int)indeksRes.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    int idx = indeksRes[pilih - 1];
    string iphoneId = antrian[idx].iPhoneId;

    iPhone* ip = cariiPhone(stok, iphoneId);
    if (ip != nullptr) {
        for (size_t j = 0; j < ip->jadwal.size(); j++) {
            if (ip->jadwal[j].tglMulai == antrian[idx].tglMulai &&
                ip->jadwal[j].tglSelesai == antrian[idx].tglSelesai) {
                ip->jadwal.erase(ip->jadwal.begin() + j);
                break;
            }
        }
        if (ip->status == DISEWA && ip->jadwal.empty()) {
            ip->status = TERSEDIA;
        }
    }

    antrian[idx].isActive = false;
    cout << "Reservasi " << antrian[idx].idReservasi << " berhasil dibatalkan." << endl;
}

void batalkanReservasiByAdmin(vector<Reservasi>& antrian, vector<iPhone>& stok) {
    header("BATALKAN RESERVASI (ADMIN)");

    if (antrian.empty()) {
        cout << "Antrian reservasi kosong." << endl;
        return;
    }

    cout << "\nSemua Reservasi:" << endl;
    for (size_t i = 0; i < antrian.size(); i++) {
        if (antrian[i].isActive) {
            cout << i + 1 << ". ID: " << antrian[i].idReservasi
                << " | User: " << antrian[i].userId
                << " | iPhone: " << antrian[i].iPhoneId
                << " | " << antrian[i].tglMulai << " - " << antrian[i].tglSelesai << endl;
        }
    }

    int pilih;
    cout << "\nPilih nomor reservasi untuk dibatalkan (0 untuk batal): ";
    cin >> pilih;

    if (pilih < 1 || pilih >(int)antrian.size()) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    if (antrian[pilih - 1].isActive) {
        string iphoneId = antrian[pilih - 1].iPhoneId;
        iPhone* ip = cariiPhone(stok, iphoneId);
        if (ip != nullptr) {
            for (size_t j = 0; j < ip->jadwal.size(); j++) {
                if (ip->jadwal[j].tglMulai == antrian[pilih - 1].tglMulai &&
                    ip->jadwal[j].tglSelesai == antrian[pilih - 1].tglSelesai) {
                    ip->jadwal.erase(ip->jadwal.begin() + j);
                    break;
                }
            }
            if (ip->status == DISEWA && ip->jadwal.empty()) {
                ip->status = TERSEDIA;
            }
        }
        antrian[pilih - 1].isActive = false;
        cout << "Reservasi " << antrian[pilih - 1].idReservasi << " berhasil dibatalkan oleh admin." << endl;
    }
    else {
        cout << "Reservasi sudah tidak aktif." << endl;
    }
}

void tampilkaniPhone(const vector<iPhone>& data) {
    cout << "\n=== DAFTAR IPHONE ===" << endl;
    if (data.empty()) {
        cout << "Tidak ada iPhone tersedia." << endl;
        return;
    }

    for (size_t i = 0; i < data.size(); i++) {
        cout << (i + 1) << ". " << data[i].model << endl;
        cout << "   ID: " << data[i].id << endl;
        cout << "   Harga/Hari: Rp " << data[i].hargaPerHari << endl;
        cout << "   Status: ";
        switch (data[i].status) {
        case TERSEDIA: cout << "Tersedia"; break;
        case DISEWA: cout << "Disewa"; break;
        case MAINTENANCE: cout << "Maintenance"; break;
        }
        cout << endl;
        cout << "   Kondisi: " << data[i].kondisi << endl;
        cout << "-------------------" << endl;
    }
}

void tampilkanDetailiPhone(const iPhone& ip) {
    cout << "=== DETAIL IPHONE ===" << endl;
    cout << "ID: " << ip.id << endl;
    cout << "Model: " << ip.model << endl;
    cout << "Harga/Hari: Rp " << ip.hargaPerHari << endl;
    cout << "Status: ";
    switch (ip.status) {
    case TERSEDIA: cout << "Tersedia"; break;
    case DISEWA: cout << "Disewa"; break;
    case MAINTENANCE: cout << "Maintenance"; break;
    }
    cout << endl;
    cout << "Kondisi: " << ip.kondisi << endl;
}

iPhone* cariiPhone(const vector<iPhone>& data, string keyword) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].id == keyword || data[i].model == keyword) {
            return const_cast<iPhone*>(&data[i]);
        }
    }
    return nullptr;
}

void tambahiPhone(vector<iPhone>& data) {
    iPhone newIP;
    newIP.id = "IPH" + to_string(data.size() + 1);

    cout << "Model: ";
    cin.ignore();
    getline(cin, newIP.model);
    cout << "Harga per hari: ";
    cin >> newIP.hargaPerHari;
    cout << "Kondisi: ";
    cin.ignore();
    getline(cin, newIP.kondisi);

    newIP.status = TERSEDIA;
    data.push_back(newIP);
    cout << "iPhone berhasil ditambahkan! ID: " << newIP.id << endl;
}

void editiPhone(vector<iPhone>& data) {
    string id;
    cout << "Masukkan ID iPhone yang akan diedit: ";
    cin >> id;

    iPhone* ip = cariiPhone(data, id);
    if (ip == nullptr) {
        cout << "iPhone tidak ditemukan!" << endl;
        return;
    }

    cout << "Model baru: ";
    cin.ignore();
    getline(cin, ip->model);
    cout << "Harga baru: ";
    cin >> ip->hargaPerHari;

    cout << "iPhone berhasil diupdate!" << endl;
}

void hapusiPhone(vector<iPhone>& data) {
    string id;
    cout << "Masukkan ID iPhone yang akan dihapus: ";
    cin >> id;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].id == id) {
            data.erase(data.begin() + i);
            cout << "iPhone berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "iPhone tidak ditemukan!" << endl;
}

void filteriPhoneByStatus(const vector<iPhone>& data, StatusiPhone status) {
    cout << "\n=== IPHONE ";
    switch (status) {
    case TERSEDIA: cout << "TERSEDIA ===" << endl; break;
    case DISEWA: cout << "DISEWA ===" << endl; break;
    case MAINTENANCE: cout << "MAINTENANCE ===" << endl; break;
    }

    bool found = false;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].status == status) {
            cout << (i + 1) << ". " << data[i].model << " (ID: " << data[i].id << ")" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Tidak ada iPhone dengan status ini." << endl;
    }
}

void updateStatusiPhone(iPhone* ptr, StatusiPhone baru) {
    if (ptr != nullptr) {
        ptr->status = baru;
    }
}