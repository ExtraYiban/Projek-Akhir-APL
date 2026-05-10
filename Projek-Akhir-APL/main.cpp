#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "includes/helpers.h"

using namespace std;

vector<iPhone> iphonesDB;
vector<User> usersDB;
vector<Reservasi> reservasiDB;
vector<Transaksi> transaksiDB;

string statusToString(StatusiPhone status) {
    if (status == StatusiPhone::Tersedia) return "Tersedia";
    if (status == StatusiPhone::Disewa) return "Disewa";
    if (status == StatusiPhone::Maintenance) return "Maintenance";
    if (status == StatusiPhone::Rusak) return "Rusak";
    return "Tidak diketahui";
}

void tekanEnterLanjut() {
    cout << "\nTekan Enter untuk lanjut...";
    cin.get();
}

void menuManajemenIphone(vector<iPhone>& ip) {
    while (true) {
        cout << "\n===========================================" << endl;
        cout << "            MANAJEMEN IPHONE              " << endl;
        cout << "===========================================" << endl;
        cout << "1. Lihat Semua iPhone" << endl;
        cout << "2. Cari Detail iPhone" << endl;
        cout << "3. Tambah iPhone" << endl;
        cout << "4. Edit iPhone" << endl;
        cout << "5. Hapus iPhone" << endl;
        cout << "6. Kembali" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan: ";

        int pilihan;
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
        case 1: {
            if (ip.empty()) {
                cout << "Belum ada data iPhone.\n";
            }
            else {
                for (size_t i = 0; i < ip.size(); ++i) {
                    cout << i + 1 << ". " << ip[i].id << " | " << ip[i].model
                         << " | Rp " << ip[i].hargaPerHari
                         << " | " << statusToString(ip[i].status)
                         << " | " << ip[i].kondisi << endl;
                }
            }
            tekanEnterLanjut();
            break;
        }
        case 2: {
            cout << "Masukkan keyword (ID/model): ";
            string keyword;
            getline(cin, keyword);

            iPhone* hasil = cariiPhone(ip, keyword);
            if (hasil) {
                tampilkanDetailiPhone(*hasil);
            }
            else {
                cout << "iPhone tidak ditemukan.\n";
            }
            tekanEnterLanjut();
            break;
        }
        case 3:
            tambahiPhone(ip);
            tekanEnterLanjut();
            break;
        case 4:
            editiPhone(ip);
            tekanEnterLanjut();
            break;
        case 5:
            hapusiPhone(ip);
            tekanEnterLanjut();
            break;
        case 6:
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            tekanEnterLanjut();
        }
    }
}

void menuManajemenUser(vector<User>& usr) {
    while (true) {
        cout << "\n===========================================" << endl;
        cout << "              MANAJEMEN USER              " << endl;
        cout << "===========================================" << endl;
        cout << "1. Lihat Semua User" << endl;
        cout << "2. Lihat Detail User" << endl;
        cout << "3. Tambah User" << endl;
        cout << "4. Edit User" << endl;
        cout << "5. Hapus User" << endl;
        cout << "6. Kembali" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan: ";

        int pilihan;
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
        case 1: {
            if (usr.empty()) {
                cout << "Belum ada data user.\n";
            }
            else {
                for (size_t i = 0; i < usr.size(); ++i) {
                    cout << i + 1 << ". " << usr[i].id << " | " << usr[i].username
                         << " | " << usr[i].role << " | total sewa: " << usr[i].totalSewa << endl;
                }
            }
            tekanEnterLanjut();
            break;
        }
        case 2: {
            cout << "Masukkan ID user: ";
            string id;
            getline(cin, id);

            User* target = cariUser(usr, id);
            if (target) {
                tampilkanDetailUser(*target);
            }
            else {
                cout << "User tidak ditemukan.\n";
            }
            tekanEnterLanjut();
            break;
        }
        case 3:
            tambahUser(usr);
            tekanEnterLanjut();
            break;
        case 4:
            editUser(usr);
            tekanEnterLanjut();
            break;
        case 5:
            hapusUser(usr);
            tekanEnterLanjut();
            break;
        case 6:
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            tekanEnterLanjut();
        }
    }
}

void menuLaporanAdmin(const vector<Transaksi>& trx, const vector<User>& usr, const vector<iPhone>& ip, const vector<Reservasi>& res) {
    while (true) {
        cout << "\n===========================================" << endl;
        cout << "                 LAPORAN                  " << endl;
        cout << "===========================================" << endl;
        cout << "1. Laporan Pendapatan" << endl;
        cout << "2. Laporan iPhone Populer" << endl;
        cout << "3. Laporan User Aktif" << endl;
        cout << "4. Laporan Pendapatan per Bulan" << endl;
        cout << "5. Laporan Okupansi iPhone" << endl;
        cout << "6. Laporan Konversi Reservasi" << endl;
        cout << "7. Laporan Top User by Spending" << endl;
        cout << "8. Kembali" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan: ";

        int pilihan;
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
        case 1:
            laporanPendapatan(trx);
            tekanEnterLanjut();
            break;
        case 2:
            laporaniPhonePopuler(trx);
            tekanEnterLanjut();
            break;
        case 3:
            laporanUserAktif(trx, usr);
            tekanEnterLanjut();
            break;
        case 4:
            laporanPendapatanPerBulan(trx);
            tekanEnterLanjut();
            break;
        case 5:
            laporanOkupansiIphone(trx, ip);
            tekanEnterLanjut();
            break;
        case 6:
            laporanKonversiReservasi(res, trx);
            tekanEnterLanjut();
            break;
        case 7:
            laporanTopUserBySpending(trx, usr);
            tekanEnterLanjut();
            break;
        case 8:
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            tekanEnterLanjut();
        }
    }
}

void showWelcomeScreen() {
	cout << endl;
	cout << "=======================================" << endl;
	cout << "   Welcome to iPhone Rental System" << endl;
	cout << "=======================================" << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Exit" << endl;
	cout << "=======================================" << endl;
	cout << "Please select an option: ";
}

void menuCustomer(string userId, vector<iPhone>& ip, vector<User>& usr,
    vector<Reservasi>& res, vector<Transaksi>& trx) {

    while (true) {
        cout << "===========================================" << endl;
        cout << "               MENU CUSTOMER               " << endl;
        cout << "===========================================" << endl;
        cout << "1. Lihat Daftar iPhone Tersedia" << endl;
        cout << "2. Cari iPhone" << endl;
        cout << "3. Buat Reservasi Baru" << endl;
        cout << "4. Lihat Reservasi Aktif & Posisi Antrian" << endl;
        cout << "5. Batalkan Reservasi" << endl;
        cout << "6. Check-In (Kembalikan iPhone)" << endl;
        cout << "7. Riwayat Transaksi Saya" << endl;
        cout << "8. Profil Saya" << endl;
        cout << "9. Logout" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan: ";

        int pilihan;
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
        case 1: {
            filteriPhoneByStatus(ip, StatusiPhone::Tersedia);
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 2: {
            cout << "\nMasukkan keyword (model/ID): ";
            string keyword;
            getline(cin, keyword);

            iPhone* hasil = cariiPhone(ip, keyword);
            if (hasil) {
                tampilkanDetailiPhone(*hasil);
            }
            else {
                cout << "iPhone tidak ditemukan.\n";
            }
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 3: {
            filteriPhoneByStatus(ip, StatusiPhone::Tersedia);

            cout << "\nMasukkan ID iPhone yang ingin disewa: ";
            string iphoneId;
            getline(cin, iphoneId);

            iPhone* target = cariiPhone(ip, iphoneId);
            if (!target || target->status != StatusiPhone::Tersedia) {
                cout << "iPhone tidak tersedia atau tidak ditemukan.\n";
                break;
            }

            cout << "Tanggal Mulai (DD-MM-YYYY): ";
            string tglMulai;
            getline(cin, tglMulai);

            cout << "Tanggal Selesai (DD-MM-YYYY): ";
            string tglSelesai;
            getline(cin, tglSelesai);

            if (!validasiTanggal(tglMulai) || !validasiTanggal(tglSelesai)) {
                cout << "Format tanggal tidak valid.\n";
                break;
            }
            if (cekBentrok(target->jadwal, tglMulai, tglSelesai)) {
                cout << "Jadwal bentrok dengan reservasi lain.\n";
                break;
            }

            Reservasi baru;
            baru.idReservasi = "RES-" + to_string(res.size() + 1);
            baru.userId = userId;
            baru.iPhoneId = iphoneId;
            baru.tglMulai = tglMulai;
            baru.tglSelesai = tglSelesai;
            baru.isActive = true;
            baru.waktuBooking = tanggalToInt(tglMulai);

            res.push_back(baru);

            JadwalSewa js{ tglMulai, tglSelesai };
            target->jadwal.push_back(js);

            urutkanAntrian(res, usr);
            prosesAntrianOtomatis(res, ip, trx, usr);

            cout << "Reservasi berhasil dibuat!\n";
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 4: {
            cout << "\nReservasi Aktif Anda:\n";
            bool ada = false;
            for (auto& r : res) {
                if (r.userId == userId && r.isActive) {
                    tampilkanDetailReservasi(r);
                    ada = true;
                }
            }
            if (!ada) cout << "Tidak ada reservasi aktif.\n";
            cout << "\nPosisi Antrian Anda:\n";
            lihatPosisiAntrian(res, userId);

            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 5: {
            batalkanReservasi(res, ip, userId);
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 6: {
            checkIniPhone(trx, ip, usr);
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 7: {
            tampilkanRiwayatUser(trx, res, userId);
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 8: {
            User* u = cariUser(usr, userId);
            if (u) tampilkanDetailUser(*u);
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
            break;
        }
        case 9: {
            simpanData(ip, usr, res, trx);
            cout << "\nLogout berhasil.\n";
            return;
        }
        default:
            cout << "Pilihan tidak valid.\n";
            cin.get();
        }
    }
}

void mainApplicationMenu(string userId) {
	int choice;
	do {
		cout << endl;
		cout << "=======================================" << endl;
		cout << "             MENU CUSTOMER" << endl;
		cout << "=======================================" << endl;
		cout << "1. Informasi iPhone" << endl;
		cout << "2. Reservasi" << endl;
		cout << "3. Penyewaan Aktif" << endl;
		cout << "4. Riwayat" << endl;
		cout << "5. Logout" << endl;
		cout << "Pilihan: ";

		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input tidak valid. Silakan masukkan angka: ";
		}

		switch (choice) {
		case 1:
			cout << "Membuka Informasi iPhone..." << endl;
			tampilkaniPhone(iphonesDB);
			break;
		case 2:
			cout << "Membuka Reservasi..." << endl;
			checkOutiPhone(reservasiDB, iphonesDB, transaksiDB, usersDB);
			simpanData(iphonesDB, usersDB, reservasiDB, transaksiDB);
			break;
		case 3:
			cout << "Membuka Penyewaan Aktif..." << endl;
			checkIniPhone(transaksiDB, iphonesDB, usersDB);
			simpanData(iphonesDB, usersDB, reservasiDB, transaksiDB);
			break;
		case 4:
			cout << "Membuka Riwayat..." << endl;
			tampilkanRiwayatUser(transaksiDB, reservasiDB, userId);
			cout << endl;
			lihatPosisiAntrian(reservasiDB, userId);
			break;
		case 5:
			cout << "Logging out..." << endl;
			break;
		default:
			cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
		}
	} while (choice != 5);
}

void menuAdmin(vector<iPhone>& ip, vector<User>& usr, vector<Reservasi>& res, vector<Transaksi>& trx) {
    while (true) {
        cout << "===========================================" << endl;
	    cout << "               MENU ADMIN                  " << endl;
	    cout << "===========================================" << endl;
        cout << "1. Manajemen Iphone" << endl;
        cout << "2. Manajemen User" << endl;
        cout << "3. Kelola Transaksi" << endl;
        cout << "4. Transaksi" << endl;
        cout << "5. Laporan" << endl;
        cout << "6. Logout" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan: ";

        int pilihanAdmin;
        while (!(cin >> pilihanAdmin)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihanAdmin) {
        case 1:
            menuManajemenIphone(ip);
            simpanData(ip, usr, res, trx);
            break;
        case 2:
            menuManajemenUser(usr);
            simpanData(ip, usr, res, trx);
            break;
        case 3:
            batalkanReservasiByAdmin(res, ip);
            simpanData(ip, usr, res, trx);
            tekanEnterLanjut();
            break;
        case 4:
            checkIniPhone(trx, ip, usr);
            simpanData(ip, usr, res, trx);
            tekanEnterLanjut();
            break;
        case 5:
            menuLaporanAdmin(trx, usr, ip, res);
            break;
        case 6:
            simpanData(ip, usr, res, trx);
            cout << "Logout admin berhasil.\n";
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            tekanEnterLanjut();
        }
    }
}

int main() {
	loadData(iphonesDB, usersDB, reservasiDB, transaksiDB);

	int choice;
	bool isAuthenticated = false;
    string currentUserId = "";
    string currentRole = "";

	while (true) {
		while (!isAuthenticated) {
			showWelcomeScreen();

			while (!(cin >> choice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number: ";
			}

			switch (choice) {
			case 1:
                isAuthenticated = login(currentUserId, currentRole);
				break;
			case 2:
				registerUser();
                cout << "Jumlah user sekarang " << usersDB.size() << endl;
				simpanData(iphonesDB, usersDB, reservasiDB, transaksiDB);
				break;
			case 3:
				simpanData(iphonesDB, usersDB, reservasiDB, transaksiDB);
				cout << "Exiting the application. Goodbye!" << endl;
				return 0;
			default:
				cout << "Invalid option. Please try again." << endl;
			}
		}

        if (isAuthenticated) {
       
            if (currentRole == "Admin") {

                menuAdmin(
                    iphonesDB,
                    usersDB,
                    reservasiDB,
                    transaksiDB
                );

            }
            else if (currentRole == "Customer") {

                menuCustomer(
                    currentUserId,
                    iphonesDB,
                    usersDB,
                    reservasiDB,
                    transaksiDB
                );
            }

            isAuthenticated = false;
            currentUserId = "";
            currentRole = "";
        }
	}

	return 0;
}




