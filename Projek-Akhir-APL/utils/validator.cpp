#include "../includes/helpers.h"
#include <cctype>
#include <ctime>
using namespace std;

bool validasiTanggal(string tgl) {
	if (tgl.length() != 10 || tgl[4] != '-' || tgl[7] != '-') 
        return false;

    for (int i = 0; i < 10;i++) {
    if (i != 4 && i != 7 && !isdigit(tgl[i]))
        return false;
    }
    return true;
}

int tanggalToInt(string tgl) {
    return stoi(tgl.substr(0,4) + tgl.substr(5,2) + tgl.substr(8,2));
}

int selisihHari(string mulai, string selesai) {
    if (!validasiTanggal(mulai) || !validasiTanggal(selesai)) return 0;

    tm tMulai = {};
    tm tSelesai = {};

    tMulai.tm_year = stoi(mulai.substr(0, 4)) - 1900;
    tMulai.tm_mon = stoi(mulai.substr(5, 2)) - 1;
    tMulai.tm_mday = stoi(mulai.substr(0, 2));

    tSelesai.tm_year = stoi(mulai.substr(0, 4)) - 1900;
    tSelesai.tm_mon = stoi(mulai.substr(5, 2)) - 1;
    tSelesai.tm_mday = stoi(mulai.substr(8, 2));


    time_t a = mktime(&tMulai);
    time_t b = mktime(&tSelesai);
    if (a == (time_t)-1 || b == (time_t)-1) return 0;

    double diff = difftime(b, a) / (60 * 60 * 24);
    return (int)diff;
}

bool cekBentrok(const vector<JadwalSewa>& jadwal, string mulai, string selesai) {
    int low = 0, high = jadwal.size() - 1;
    int m = tanggalToInt(mulai), s = tanggalToInt(selesai);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int jm = tanggalToInt(jadwal[mid].tglMulai);
        int js = tanggalToInt(jadwal[mid].tglSelesai);
        if (s < jm)
            high = mid - 1;
        else if (m > js)
            low = mid + 1;
        else 
            return true;
    }
    return false;
}


