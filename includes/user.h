#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

#define MAX_USERS 100

struct User {
    string id;
    string name;
    string phone;
    string username;
    string password;
    string role;
    bool isVIP;
};

extern User daftarUser[MAX_USERS];
extern int jumlahUser;

void login();
void registerUser();
void loadUsers();
void saveUsers();
int findUserByUsername(const string& username);
int findUserIndexByID(const string& id);
void displayAllUsers();
void deleteUser();
void setVIPStatus();

#endif
