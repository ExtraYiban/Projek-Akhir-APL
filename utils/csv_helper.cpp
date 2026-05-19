#include "csv_helper.h"
#include <sstream>

vector<string> splitCSVRow(const string& row) {
    vector<string> fields;
    stringstream ss(row);
    string field;

    while (getline(ss, field, ',')) {
        fields.push_back(trimString(field));
    }

    return fields;
}

string trimString(const string& str) {
    int start = 0;
    int end = str.length() - 1;

    while (start <= end && (str[start] == ' ' || str[start] == '\r')) {
        start++;
    }

    while (end >= start && (str[end] == ' ' || str[end] == '\r')) {
        end--;
    }

    return str.substr(start, end - start + 1);
}

bool parseBoolean(const string& str) {
    string lower = "";
    for (char c : str) {
        lower += tolower(c);
    }
    return lower == "true";
}
