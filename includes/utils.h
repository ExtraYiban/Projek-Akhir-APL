#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>
using namespace std;

void clearScreen();
void pressEnter();
string getCurrentDate();
int stringToInt(const string& str);
float stringToFloat(const string& str);
string intToString(int val);
string floatToString(float val);
string formatID(const string& prefix, int num);

#endif
