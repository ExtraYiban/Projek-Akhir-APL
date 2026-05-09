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
    cin >> pilihanAdmin;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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




