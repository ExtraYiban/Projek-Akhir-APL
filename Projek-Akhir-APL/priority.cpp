#include "helpers.h"
#include <algorithm>

using namespace std;

int getPriorityLevel(UserLevel level) {
    switch (level) {
    case VIP:     return 1;
    case REGULAR: return 2;
    case BARU:    return 3;
    default:      return 4;
    }
}

void urutkanAntrian(vector<Reservasi>& antrian, vector<User>& usr) {
    if (antrian.empty()) return;

    sort(antrian.begin(), antrian.end(), [&usr](const Reservasi& a, const Reservasi& b) {
        User* userA = nullptr;
        User* userB = nullptr;

        for (size_t i = 0; i < usr.size(); i++) {
            if (usr[i].id == a.userId) userA = &usr[i];
            if (usr[i].id == b.userId) userB = &usr[i];
            if (userA != nullptr && userB != nullptr) break;
        }

        UserLevel levelA = userA ? userA->level : BARU;
        UserLevel levelB = userB ? userB->level : BARU;

        int priorityA = getPriorityLevel(levelA);
        int priorityB = getPriorityLevel(levelB);

        if (priorityA != priorityB) {
            return priorityA < priorityB;
        }

        return a.waktuBooking < b.waktuBooking;
        });
}

void prosesAntrianOtomatis(vector<Reservasi>& antrian, vector<iPhone>& stok,
    vector<Transaksi>& histori, vector<User>& usr) {

    header("PROSES ANTRIAN OTOMATIS");

    if (antrian.empty()) {
        cout << "Antrian kosong." << endl;
        return;
    }

    urutkanAntrian(antrian, usr);

    bool adaDiproses = false;

    for (size_t i = 0; i < antrian.size(); ) {
        Reservasi& res = antrian[i];

        if (!res.isActive) {
            i++;
            continue;
        }

        iPhone* targetIP = nullptr;
        for (size_t j = 0; j < stok.size(); j++) {
            if (stok[j].id == res.iPhoneId) {
                targetIP = &stok[j];
                break;
            }
        }

        if (targetIP != nullptr && targetIP->status == TERSEDIA) {
            targetIP->status = DISEWA;

            Transaksi trx;
            trx.idTransaksi = "T" + to_string(histori.size() + 1);
            trx.userId = res.userId;
            trx.iPhoneId = res.iPhoneId;
            trx.tglMulai = res.tglMulai;
            trx.tglSelesai = res.tglSelesai;
            trx.tglKembali = "-";

            trx.durasi = selisihHari(res.tglMulai, res.tglSelesai);
            if (trx.durasi <= 0) trx.durasi = 1;

            User* u = cariUser(usr, res.userId);
            UserLevel lvl = u ? u->level : BARU;

            trx.biayaSewa = hitungBiaya(*targetIP, trx.durasi, 0, lvl);
            trx.denda = 0;
            trx.totalBayar = trx.biayaSewa;

            histori.push_back(trx);
            res.isActive = false;

            cout << "[BERHASIL] Reservasi " << res.idReservasi
                << " (User: " << res.userId << ") diproses. iPhone "
                << targetIP->model << " sekarang disewa." << endl;

            adaDiproses = true;
            antrian.erase(antrian.begin() + i);
        }
        else {
            i++;
        }
    }

    if (!adaDiproses) {
        cout << "Tidak ada reservasi yang dapat diproses saat ini (Stok habis atau iPhone tidak tersedia)." << endl;
    }
}