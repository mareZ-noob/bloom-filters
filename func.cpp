#include "func.h"

bool checkUsername(string username, bool *bitArray) {
    int n = username.length();
    for (auto x : username) {
        if (x == ' ') return false;
    }

    if (n >= 10 || n <= 5 || LookUp(bitArray, username)) return false;

    return true;
}

void InvaidUsername() {
    cout << "Your username is invalid. Note that:" << endl;
    cout << "\t- 5 < sizeof(Username) < 10." << endl;
    cout << "\t- Username must not contain spaces." << endl;
    cout << "\t- Username must not be the same as any registered Username."
         << endl;
}



bool checkPassword(string username, string password, char *bitArray) {
    int n = password.length();
    int cntUppercase, cntLowercase, cntNumber, cntSpecial;
    cntUppercase = cntLowercase = cntNumber = cntSpecial = 0;
    for (auto x : password) {
        if (x == ' ') return false;
        if (x >= 'A' && x <= 'Z')
            cntUppercase++;
        else if (x >= 'a' && x <= 'z')
            cntLowercase++;
        else if (x >= '0' && x <= '9')
            cntNumber++;
        else
            cntSpecial++;
    }

    if (password == username) return false;

    if (!cntUppercase || !cntLowercase || !cntNumber || !cntSpecial)
        return false;

    return true;
}

void InvalidPassword() {
    cout << "Your password is invalid. Note that: " << endl;
    cout << "\t- 10 < sizeof(Password) < 20." << endl;
    cout << "\t- Password must not contain spaces and cannot be the same as "
            "username."
         << endl;
    cout << "\t- Password must include uppercase, lowercase, numbers and "
            "special characters."
         << endl;
    cout << "\t- Password must not match the weak password listed in the file "
            "<WeakPass.txt>."
         << endl;
}