#pragma once
#include <string>
using namespace std;

enum StatusiPhone { Tersedia, Disewa, Maintenance, Rusak };
enum UserLevel { VIP, REGULAR, BARU };

const double HARGA_DASAR_PER_HARI = 50000.0;
const double HARGA_PRO_PER_HARI = 80000.0;
const double DENDA_PER_HARI = 20000.0;
const double DISKON_VIP = 0.10;
const string DATA_FOLDER = "";
