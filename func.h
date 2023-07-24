#ifndef __FUNC_H_
#define __FUNC_H_

#include "main.h"
#include "bloom_filters.h"

struct Arrays {
    bool bitArray[SIZE] = {false};
    bool bitArrayPass[SIZE][SIZE] = {false};
    bool bitArrayWeak[SIZE] = {false};
};

struct Account {
    string username;
    string password;
};

void signUpfile(Account user);
void failFile(Account user);

void readFile(Arrays &arrays);
void readWeakPass(Arrays &arrays);

bool checkUsername(string username, Arrays &arrays);
void InvaidUsername();
bool checkPassword(string username, string password, Arrays &arrays);
void InvalidPassword();

bool isLogin(Account &user, Arrays &arrays, int &check);
bool checkRegister(Arrays arrays, Account user, int &check);
void changePassWord(Account &user, Arrays &arrays);
void changePassChoice(Account &user, Arrays &arrays);
void reGister(Arrays &arrays, Account &user, int &check);
void choice(Arrays &arrays);

#endif  // __FUNC_H