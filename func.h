#ifndef _FUNC_H_
#define _FUNC_H_

#include "main.h"
using namespace std;
void choice(bool* bitarray, int size);
bool isLogin(bool*);
void readFile(bool* bitarray, int size);
void failFile(string username);
void signUpfile(string username, string password);
bool checkUsername(string username, bool *bitArray);
void InvaidUsername();
bool checkPassword(string username, string password);
void InvalidPassword();
#endif  // _FUNC_H