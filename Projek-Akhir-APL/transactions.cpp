#include "helpers.h"



void tampilkanDetailTransaksi(const Transaksi &t) {
    cout << "Transaksi: " << t.idTransaksi << " - " << t.iPhoneId << endl;
}
void header(const string &judul) {
    cout << "=== " << judul << " ===\n";
}

