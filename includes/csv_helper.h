#ifndef CSV_HELPER_H
#define CSV_HELPER_H

#include <string>
#include <vector>
using namespace std;

vector<string> splitCSVRow(const string& row);
string trimString(const string& str);
bool parseBoolean(const string& str);

#endif
