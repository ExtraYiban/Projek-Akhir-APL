#include "helpers.h"
using namespace std;

vector<User> usersDB = {
    // default admin
    {"U001", "admin", "admin", "Admin", UserLevel::BARU, 0}
};

string prosesLogin(vector<User>& users) {
    header("LOGIN");
    string u, p;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;
    for(auto& usr : users) {
        if(usr.username == u && usr.password == p) {
            cout << "Login berhasil. Role: " << usr.role << "\n";
            return usr.id;
        }
    }
    cout << "Username atau Password salah.\n";
    return "";
}

bool login() {
    string id = prosesLogin(usersDB);
    if (id != "") {
        return true;
    }
    return false;
}

void tambahUser(vector<User>& data) {
    header("TAMBAH USER");
    User u;
    // Auto-generate user ID (U1, U2...)
    int idx = data.size() + 1; string genId; bool unique=false;
    while(!unique) { genId = string("U") + to_string(idx); unique = true; for(auto& x: data) if(x.id==genId){ unique=false; break;} if(!unique) idx++; }
    u.id = genId; cout << "Assigned ID: " << u.id << "\n";
    cout << "Username: "; cin >> u.username;
    cout << "Password: "; cin >> u.password;
    cout << "Role:\n1. Admin\n2. Customer\nPilihan: "; int r; cin >> r; u.role = (r==1?"Admin":"Customer");
    int lv; cout << "Level (0=VIP, 1=Regular, 2=Baru): "; cin >> lv;
    u.level = (UserLevel)lv; u.totalSewa = 0;
    data.push_back(u);
}

void editUser(vector<User>& data) {
    header("EDIT USER");
    if (data.empty()) { cout << "Tidak ada user.\n"; return; }
    cout << "Pilih User untuk diedit:\n";
    for (size_t i=0;i<data.size();++i) cout << i+1 << ". " << data[i].id << " - " << data[i].username << " | " << data[i].role << "\n";
    cout << "Nomor (0 = batal): "; int pick; cin >> pick; if (pick<=0 || pick>(int)data.size()) { cout<<"Batal.\n"; return; }
    User* ptr = &data[pick-1];
    cout << "Username Baru: "; cin.ignore(); getline(cin, ptr->username);
    int lv; cout << "Level Baru (0/1/2): "; cin >> lv; ptr->level = (UserLevel)lv;
}

void hapusUser(vector<User>& data) {
    header("HAPUS USER");
    if (data.empty()) { cout << "Tidak ada user.\n"; return; }
    cout << "Pilih User untuk dihapus:\n";
    for (size_t i=0;i<data.size();++i) cout << i+1 << ". " << data[i].id << " - " << data[i].username << " | " << data[i].role << "\n";
    cout << "Nomor (0 = batal): "; int pick; cin >> pick; if (pick<=0 || pick>(int)data.size()) { cout<<"Batal.\n"; return; }
    data.erase(data.begin() + (pick-1)); cout << "Berhasil.\n";
}

User* cariUser(const vector<User>& data, string id) {
    for (auto& u : data) if (u.id == id) return (User*)&u;
    return nullptr;
}

void tampilkanRiwayatUser(const vector<Transaksi>& trx, const vector<Reservasi>& res, string userId) {
    header("RIWAYAT USER");
    bool found = false;
    for (auto& t : trx) if (t.userId == userId) { tampilkanDetailTransaksi(t); cout << "------------------------------\n"; found = true; }
    for (auto& r : res) if (r.userId == userId && r.isActive) { tampilkanDetailReservasi(r); cout << "------------------------------\n"; found = true; }
    if (!found) cout << "Belum ada riwayat.\n";
}

void lihatPosisiAntrian(const vector<Reservasi>& res, string userId) {
    header("POSISI ANTRIAN");
    int posisi = 1;
    for (auto& r : res) {
        if (r.isActive) {
            if (r.userId == userId) { cout << "Reservasi Anda: " << r.idReservasi << " berada di posisi ke-" << posisi << "\n"; return; }
            posisi++;
        }
    }
    cout << "Tidak ada reservasi aktif.\n";
}

void tampilkanDetailUser(const User& u) {
    cout << "ID      : " << u.id << "\n";
    cout << "Username: " << u.username << "\n";
    cout << "Role    : " << u.role << "\n";
    string lvl = (u.level==VIP?"VIP":(u.level==REGULAR?"Regular":"Baru"));
    cout << "Level   : " << lvl << "\n";
    cout << "TotalSewa: " << u.totalSewa << "\n";
}

void tampilkanDetailReservasi(const Reservasi& r) {
    cout << "ID Res   : " << r.idReservasi << "\n";
    cout << "User ID  : " << r.userId << "\n";
    cout << "iPhone ID: " << r.iPhoneId << "\n";
    cout << "Mulai    : " << r.tglMulai << "\n";
    cout << "Selesai  : " << r.tglSelesai << "\n";
    cout << "Aktif    : " << (r.isActive?"Ya":"Tidak") << "\n";
    cout << "WaktuBkng: " << r.waktuBooking << "\n";
}

void registerUser(vector<User>& data) {
    header("REGISTER");
    User u;
    // Auto-generate unique ID like U1, U2, ...
    int idx = data.size() + 1;
    string genId;
    bool unique = false;
    while (!unique) {
        genId = string("U") + to_string(idx);
        unique = true;
        for (auto& x : data) if (x.id == genId) { unique = false; break; }
        if (!unique) idx++;
    }
    u.id = genId;
    cout << "Assigned ID: " << u.id << "\n";
    cout << "Username: "; cin >> u.username;
    cout << "Password: "; cin >> u.password;
    u.role = "Customer";
    u.level = UserLevel::BARU;
    u.totalSewa = 0;
    data.push_back(u);
    cout << "Registrasi berhasil. ID Anda: " << u.id << "\n";
}

void registerUser() {
    registerUser(usersDB);
}


