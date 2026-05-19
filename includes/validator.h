#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
using namespace std;

bool isValidPhoneNumber(const string& phone);
bool isValidDate(const string& date);
int getValidInt(const string& prompt);
float getValidFloat(const string& prompt);
string getValidString(const string& prompt);
int getMenuChoice(int min, int max);

#endif
