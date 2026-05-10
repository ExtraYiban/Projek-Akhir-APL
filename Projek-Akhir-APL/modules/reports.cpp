#include "../includes/helpers.h"
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

void laporanPendapatan(const vector<Transaksi>& histori) {
	header("LAPORAN PENDAPATAN");

	if (histori.empty()) {
		cout << "Belum ada data transaksi.\n";
		return;
	}

	double totalPendapatan = 0.0;
	double totalDenda = 0.0;
	int transaksiSelesai = 0;

	for (size_t i = 0; i < histori.size(); i++) {
		const bool selesai = !(histori[i].tglKembali.empty() || histori[i].tglKembali == "-");
		if (selesai) {
			transaksiSelesai++;
			totalPendapatan += histori[i].totalBayar;
			totalDenda += histori[i].denda;
		}
	}

	cout << "Jumlah transaksi selesai : " << transaksiSelesai << endl;
	cout << fixed << setprecision(0);
	cout << "Total pendapatan         : Rp " << totalPendapatan << endl;
	cout << "Total denda              : Rp " << totalDenda << endl;
	cout.unsetf(ios::floatfield);

	if (transaksiSelesai == 0) {
		cout << "Belum ada transaksi yang selesai dikembalikan.\n";
	}
}

void laporaniPhonePopuler(const vector<Transaksi>& histori) {
	header("LAPORAN IPHONE POPULER");

	if (histori.empty()) {
		cout << "Belum ada data transaksi.\n";
		return;
	}

	map<string, int> frekuensi;
	for (size_t i = 0; i < histori.size(); i++) {
		frekuensi[histori[i].iPhoneId]++;
	}

	vector<pair<string, int>> ranking(frekuensi.begin(), frekuensi.end());
	sort(ranking.begin(), ranking.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second > b.second;
	});

	cout << "Peringkat iPhone berdasarkan frekuensi transaksi:\n";
	for (size_t i = 0; i < ranking.size(); i++) {
		cout << i + 1 << ". " << ranking[i].first << " | total disewa: " << ranking[i].second << " kali" << endl;
	}
}

void laporanUserAktif(const vector<Transaksi>& histori, const vector<User>& users) {
	header("LAPORAN USER AKTIF");

	if (histori.empty()) {
		cout << "Belum ada data transaksi.\n";
		return;
	}

	map<string, int> frekuensiSewa;
	for (size_t i = 0; i < histori.size(); i++) {
		frekuensiSewa[histori[i].userId]++;
	}

	vector<pair<string, int>> ranking(frekuensiSewa.begin(), frekuensiSewa.end());
	sort(ranking.begin(), ranking.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second > b.second;
	});

	cout << "Peringkat user berdasarkan jumlah transaksi:\n";
	for (size_t i = 0; i < ranking.size(); i++) {
		string username = "(unknown)";
		string role = "-";

		for (size_t j = 0; j < users.size(); j++) {
			if (users[j].id == ranking[i].first) {
				username = users[j].username;
				role = users[j].role;
				break;
			}
		}

		cout << i + 1 << ". " << ranking[i].first
			 << " | " << username
			 << " | " << role
			 << " | total transaksi: " << ranking[i].second << endl;
	}
}

void laporanPendapatanPerBulan(const vector<Transaksi>& histori) {
	header("LAPORAN PENDAPATAN PER BULAN");

	map<string, double> pendapatanBulanan;
	map<string, int> transaksiBulanan;

	for (size_t i = 0; i < histori.size(); i++) {
		const bool selesai = !(histori[i].tglKembali.empty() || histori[i].tglKembali == "-");
		if (!selesai || histori[i].tglMulai.size() < 7) {
			continue;
		}

		string bulan = histori[i].tglMulai.substr(0, 7);
		pendapatanBulanan[bulan] += histori[i].totalBayar;
		transaksiBulanan[bulan] += 1;
	}

	if (pendapatanBulanan.empty()) {
		cout << "Belum ada transaksi selesai untuk dihitung per bulan.\n";
		return;
	}

	cout << fixed << setprecision(0);
	cout << "Bulan | Jumlah Transaksi | Total Pendapatan\n";
	for (map<string, double>::const_iterator it = pendapatanBulanan.begin(); it != pendapatanBulanan.end(); ++it) {
		cout << it->first << " | " << transaksiBulanan[it->first] << " | Rp " << it->second << endl;
	}
	cout.unsetf(ios::floatfield);
}

void laporanOkupansiIphone(const vector<Transaksi>& histori, const vector<iPhone>& iphones) {
	header("LAPORAN OKUPANSI IPHONE");

	map<string, int> hariSewaPerIphone;
	int totalHariSewa = 0;

	for (size_t i = 0; i < histori.size(); i++) {
		int durasi = histori[i].durasi;
		if (durasi <= 0 && !histori[i].tglMulai.empty() && !histori[i].tglSelesai.empty()) {
			durasi = selisihHari(histori[i].tglMulai, histori[i].tglSelesai);
		}
		if (durasi <= 0) durasi = 1;

		hariSewaPerIphone[histori[i].iPhoneId] += durasi;
		totalHariSewa += durasi;
	}

	if (iphones.empty()) {
		cout << "Data iPhone kosong.\n";
		return;
	}

	cout << "ID iPhone | Model | Total Hari Disewa | Kontribusi\n";
	cout << fixed << setprecision(2);
	for (size_t i = 0; i < iphones.size(); i++) {
		int hariSewa = hariSewaPerIphone[iphones[i].id];
		double kontribusi = (totalHariSewa > 0) ? (100.0 * hariSewa / totalHariSewa) : 0.0;

		cout << iphones[i].id
			 << " | " << iphones[i].model
			 << " | " << hariSewa
			 << " | " << kontribusi << "%" << endl;
	}
	cout.unsetf(ios::floatfield);
}

void laporanKonversiReservasi(const vector<Reservasi>& reservasi, const vector<Transaksi>& histori) {
	header("LAPORAN KONVERSI RESERVASI");

	const int totalReservasi = (int)reservasi.size();
	const int totalTransaksi = (int)histori.size();

	int reservasiAktif = 0;
	for (size_t i = 0; i < reservasi.size(); i++) {
		if (reservasi[i].isActive) reservasiAktif++;
	}

	const int reservasiSelesaiAtauBatal = totalReservasi - reservasiAktif;
	const int estimasiBatal = max(0, reservasiSelesaiAtauBatal - totalTransaksi);

	double conversionRate = 0.0;
	if (totalReservasi > 0) {
		conversionRate = 100.0 * totalTransaksi / totalReservasi;
	}

	cout << "Total reservasi                : " << totalReservasi << endl;
	cout << "Total transaksi tercatat       : " << totalTransaksi << endl;
	cout << "Reservasi aktif                : " << reservasiAktif << endl;
	cout << "Estimasi reservasi batal       : " << estimasiBatal << endl;
	cout << fixed << setprecision(2);
	cout << "Conversion rate (estimasi)     : " << conversionRate << "%" << endl;
	cout.unsetf(ios::floatfield);

	cout << "Catatan: conversion dihitung dari total transaksi dibanding total reservasi.\n";
}

void laporanTopUserBySpending(const vector<Transaksi>& histori, const vector<User>& users) {
	header("LAPORAN TOP USER BY SPENDING");

	map<string, double> totalBelanja;
	for (size_t i = 0; i < histori.size(); i++) {
		totalBelanja[histori[i].userId] += histori[i].totalBayar;
	}

	if (totalBelanja.empty()) {
		cout << "Belum ada data transaksi.\n";
		return;
	}

	vector<pair<string, double> > ranking(totalBelanja.begin(), totalBelanja.end());
	sort(ranking.begin(), ranking.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second > b.second;
	});

	cout << fixed << setprecision(0);
	for (size_t i = 0; i < ranking.size(); i++) {
		string username = "(unknown)";
		for (size_t j = 0; j < users.size(); j++) {
			if (users[j].id == ranking[i].first) {
				username = users[j].username;
				break;
			}
		}

		cout << i + 1 << ". " << ranking[i].first
			 << " | " << username
			 << " | total spending: Rp " << ranking[i].second << endl;
	}
	cout.unsetf(ios::floatfield);
}


