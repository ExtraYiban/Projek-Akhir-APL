#include "helpers.h"
#include <cctype>
#include <ctime>
using namespace std;

bool validasiTanggal(string tgl) {
    if (tgl.length() != 10 || tgl[2] != '/' || tgl[5] != '/') return false;
    for (int i = 0; i < 10; i++) if ((i != 2 && i != 5) && !isdigit(tgl[i])) return false;
    return true;
}

int tanggalToInt(string tgl) {
    return stoi(tgl.substr(6,4) + tgl.substr(3,2) + tgl.substr(0,2));
}

int selisihHari(string mulai, string selesai) {
    if (!validasiTanggal(mulai) || !validasiTanggal(selesai)) return 0;

    tm tMulai = {};
    tm tSelesai = {};

    tMulai.tm_mday = stoi(mulai.substr(0, 2));
    tMulai.tm_mon = stoi(mulai.substr(3, 2)) - 1;
    tMulai.tm_year = stoi(mulai.substr(6, 4)) - 1900;
    tMulai.tm_hour = 12;

    tSelesai.tm_mday = stoi(selesai.substr(0, 2));
    tSelesai.tm_mon = stoi(selesai.substr(3, 2)) - 1;
    tSelesai.tm_year = stoi(selesai.substr(6, 4)) - 1900;
    tSelesai.tm_hour = 12;

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
        if (s < jm) low = mid + 1;
        else if (m > js) high = mid - 1;
        else return true;
    }
    return false;
}


