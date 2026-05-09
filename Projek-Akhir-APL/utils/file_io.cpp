#include "../includes/helpers.h"
#include <fstream>
#include <sstream>
using namespace std;

void loadData(vector<iPhone>& ip, vector<User>& usr, vector<Reservasi>& res, vector<Transaksi>& trx) {
    auto safe_stod = [](const string& s)->double { try { if (s.empty()) return 0.0; return stod(s); } catch(...) { return 0.0; } };
    auto safe_stoi = [](const string& s)->int { try { if (s.empty()) return 0; return stoi(s); } catch(...) { return 0; } };
    auto safe_bool = [](const string& s)->bool { return (s == "1" || s=="true" || s=="TRUE"); };
    // Load iPhones
    {
        ifstream fin(DATA_FOLDER + "iphones.csv");
        if (!fin.is_open()) { cout << "[INFO] iphones.csv not found. Using empty iPhone list.\n"; }
        else {
            string line; bool first=true;
            while (getline(fin, line)) {
                if (first) { first=false; continue; } // skip header
                if (line.empty()) continue;
                stringstream ss(line);
                iPhone i; string tmp;
                getline(ss, i.id, ','); getline(ss, i.model, ','); getline(ss, tmp, ','); i.hargaPerHari = safe_stod(tmp);
                getline(ss, tmp, ','); i.status = (StatusiPhone)safe_stoi(tmp);
                getline(ss, i.kondisi, ',');
                ip.push_back(i);
            }
            fin.close();
        }
    }
    // Load Users
    {
        ifstream fin(DATA_FOLDER + "users.csv");
        if (!fin.is_open()) { cout << "[INFO] users.csv not found. Using empty user list.\n"; }
        else {
            string line; bool first=true;
            while (getline(fin, line)) {
                if (first) { first=false; continue; }
                if (line.empty()) continue;
                stringstream ss(line);
                User u; string tmp;
                getline(ss, u.id, ','); getline(ss, u.username, ','); getline(ss, u.password, ','); getline(ss, u.role, ',');
                getline(ss, tmp, ','); u.level = (UserLevel)safe_stoi(tmp);
                getline(ss, tmp, ','); u.totalSewa = safe_stoi(tmp);
                usr.push_back(u);
            }
            fin.close();
        }
    }
    // Load Reservations
    {
        ifstream fin(DATA_FOLDER + "reservations.csv");
        if (!fin.is_open()) { cout << "[INFO] reservations.csv not found. Using empty reservations list.\n"; }
        else {
            string line; bool first=true;
            while (getline(fin, line)) {
                if (first) { first=false; continue; }
                if (line.empty()) continue;
                stringstream ss(line);
                Reservasi r; string tmp;
                getline(ss, r.idReservasi, ','); getline(ss, r.userId, ','); getline(ss, r.iPhoneId, ',');
                getline(ss, r.tglMulai, ','); getline(ss, r.tglSelesai, ','); getline(ss, tmp, ','); r.isActive = safe_bool(tmp); getline(ss, tmp, ','); r.waktuBooking = safe_stoi(tmp);
                res.push_back(r);
            }
            fin.close();
        }
    }
    // Load Transactions
    {
        ifstream fin(DATA_FOLDER + "transactions.csv");
        if (!fin.is_open()) { cout << "[INFO] transactions.csv not found. Using empty transactions list.\n"; }
        else {
            string line; bool first=true;
            while (getline(fin, line)) {
                if (first) { first=false; continue; }
                if (line.empty()) continue;
                stringstream ss(line);
                Transaksi t; string tmp;
                getline(ss, t.idTransaksi, ','); getline(ss, t.userId, ','); getline(ss, t.iPhoneId, ',');
                getline(ss, t.tglMulai, ','); getline(ss, t.tglSelesai, ','); getline(ss, t.tglKembali, ',');
                getline(ss, tmp, ','); t.durasi = safe_stoi(tmp);
                getline(ss, tmp, ','); t.biayaSewa = safe_stod(tmp);
                getline(ss, tmp, ','); t.denda = safe_stod(tmp);
                getline(ss, tmp, ','); t.totalBayar = safe_stod(tmp);
                trx.push_back(t);
            }
            fin.close();
        }
    }
}

void simpanData(const vector<iPhone>& ip, const vector<User>& usr, const vector<Reservasi>& res, const vector<Transaksi>& trx) {
    // Save iPhones
    {
        ofstream fout(DATA_FOLDER + "iphones.csv");
        fout << "id,model,hargaPerHari,status,kondisi\n";
        for (auto& i : ip) fout << i.id << "," << i.model << "," << i.hargaPerHari << "," << (int)i.status << "," << i.kondisi << "\n";
        fout.close();
    }
    // Save Users
    {
        ofstream fout(DATA_FOLDER + "users.csv");
        fout << "id,username,password,role,level,totalSewa\n";
        for (auto& u : usr) fout << u.id << "," << u.username << "," << u.password << "," << u.role << "," << (int)u.level << "," << u.totalSewa << "\n";
        fout.close();
    }
    // Save Reservations
    {
        ofstream fout(DATA_FOLDER + "reservations.csv");
        fout << "idReservasi,userId,iPhoneId,tglMulai,tglSelesai,isActive,waktuBooking\n";
        for (auto& r : res) fout << r.idReservasi << "," << r.userId << "," << r.iPhoneId << "," << r.tglMulai << "," << r.tglSelesai << "," << (r.isActive?"1":"0") << "," << r.waktuBooking << "\n";
        fout.close();
    }
    // Save Transactions
    {
        ofstream fout(DATA_FOLDER + "transactions.csv");
        fout << "idTransaksi,userId,iPhoneId,tglMulai,tglSelesai,tglKembali,durasi,biayaSewa,denda,totalBayar\n";
        for (auto& t : trx) fout << t.idTransaksi << "," << t.userId << "," << t.iPhoneId << "," << t.tglMulai << "," << t.tglSelesai << "," << t.tglKembali << "," << t.durasi << "," << t.biayaSewa << "," << t.denda << "," << t.totalBayar << "\n";
        fout.close();
    }
}
