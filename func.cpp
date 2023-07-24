#include "func.h"

// Write to "SignUp.txt" valid accounts
void signUpfile(Account user) {
    ofstream ofs("SignUp.txt", ios::app);
    ofs << user.username << " " << user.password << "\n";
    ofs.close();
    return;
}

// Write to "Fail.txt" invalid accounts
void failFile(Account user) {
    ofstream ofs("Fail.txt", ios::app);
    ofs << user.username << " " << user.password << "\n";
    ofs.close();
    return;
}

// Read "SignUp.txt" to bitArray
void readFile(Arrays &arrays) {
    string data, tmp;
    string username;
    ifstream ifs("SignUp.txt");
    while (!ifs.eof()) {
        getline(ifs, data);
        if (data.empty()) break;
        stringstream ss(data);
        getline(ss, tmp, ' ');
        Insert(arrays.bitArray, tmp);
        username = tmp;
        getline(ss, tmp);
        Insert(arrays.bitArrayPass[hashPassword(username)], tmp);
    }
    ifs.close();
    return;
}

// Read "WeakPass.txt" to bitArray
void readWeakPass(Arrays &arrays) {
    string data;
    ifstream ifs("WeakPass.txt");
    while (!ifs.eof()) {
        getline(ifs, data);
        if (data.empty()) break;
        if (!LookUp(arrays.bitArrayWeak, data))
            Insert(arrays.bitArrayWeak, data);
    }
    ifs.close();
    return;
}

// Check valid user
bool checkUsername(string username, Arrays &arrays) {
    int n = username.length();
    for (auto x : username) {
        if (x == ' ') return false;
    }

    if (n >= 10 || n <= 5 || LookUp(arrays.bitArray, username)) return false;

    return true;
}

// Print invalid username conditions
void InvaidUsername() {
    cerr << "Your username is invalid. Note that:\n";
    cerr << "\t- 5 < sizeof(Username) < 10.\n";
    cerr << "\t- Username must not contain spaces.\n";
    cerr << "\t- Username must not be the same as any registered Username.\n";
}

// Check valid password
bool checkPassword(string username, string password, Arrays &arrays) {
    if (LookUp(arrays.bitArrayWeak, password)) return false;
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
    if (n <= 10 || n >= 20) return false;

    if (password == username) return false;

    if (!cntUppercase || !cntLowercase || !cntNumber || !cntSpecial)
        return false;

    return true;
}

// Print invalid password conditions
void InvalidPassword() {
    cerr << "Your password is invalid. Note that: \n";
    cerr << "\t- 10 < sizeof(Password) < 20.\n";
    cerr << "\t- Password must not contain spaces and cannot be the same as "
            "username.\n";
    cerr << "\t- Password must include uppercase, lowercase, numbers and "
            "special characters.\n";
    cerr << "\t- Password must not match the weak password listed in the file "
            "<WeakPass.txt>.\n";
}

// Check if login
bool isLogin(Account &user, Arrays &arrays, int &check) {
    cout << "Enter your username: ";
    cin >> user.username;
    cout << "Enter your password: ";
    cin >> user.password;
    check = 0;

    bool uSer = LookUp(arrays.bitArray, user.username);
    bool pass =
        LookUp(arrays.bitArrayPass[hashPassword(user.username)], user.password);
    if (uSer && pass) {
        return true;
    } else if (uSer && !pass) {
        check = 1;
    }

    return false;
}

// Check if register
bool checkRegister(Arrays arrays, Account user, int &check) {
    if (!checkUsername(user.username, arrays))
        check = 0;
    else if (!checkPassword(user.username, user.password, arrays))
        check = 2;
    if (checkPassword(user.username, user.password, arrays) &&
        checkUsername(user.username, arrays)) {
        cout << "Login successfully\n\n";
        return true;
    } else
        return false;
}

// Change password and rewrite into "SignUp.txt"
void changePassWord(Account &user, Arrays &arrays) {
    vector<Account> list;
    Account tmp;
    string data;

    ifstream ifs("SignUp.txt");
    while (!ifs.eof()) {
        getline(ifs, data);
        if (data.empty()) break;
        stringstream ss(data);
        getline(ss, tmp.username, ' ');
        getline(ss, tmp.password);
        list.push_back(tmp);
    }
    ifs.close();

    int idx = 0;
    for (long unsigned int i = 0; i < list.size(); i++) {
        if (list[i].username == user.username) {
            idx = i;
            break;
        }
    }

    cout << "Enter your new password: ";
    cin >> tmp.password;

    while (!checkPassword(list[idx].username, tmp.password, arrays)) {
        failFile(user);
        InvalidPassword();
        cout << "\nEnter your new password: ";
        cin >> tmp.password;
    }

    list[idx].password = tmp.password;

    cout << "Your password has been changed successfully! ";

    ofstream ofs("SignUp.txt");
    for (long unsigned int i = 0; i < list.size(); i++) {
        ofs << list[i].username << " " << list[i].password << "\n";
    }
    ofs.close();

    memset(arrays.bitArray, 0, SIZE);
    memset(arrays.bitArrayPass, 0, SIZE * SIZE);
    readFile(arrays);
}

// If user choose change password
void changePassChoice(Account &user, Arrays &arrays) {
    int choice;
    cout << "Logged in successfully!\n";
    cout << "Menu: \n";
    cout << "----------------------\n";
    cout << "1. Change password\n";
    cout << "0. Quit\n";
    cout << "Your choice: ";
    cin >> choice;
    if (choice == 0) {
        cerr << "You exited the program!";
        return;
    } else {
        cin.ignore();
        cout << "1. Change password\n\n";
        changePassWord(user, arrays);
    }
}

// When user choose register
void reGister(Arrays &arrays, Account &user, int &check) {
    cout << "1. Register\n\n";
    bool flag = true;
    check = 0;
    while (flag) {
        cout << "Enter your username: ";
        cin >> user.username;
        cout << "Enter your password: ";
        cin >> user.password;
        if (checkRegister(arrays, user, check))
            return;
        else {
            failFile(user);
            if (check == 0 && LookUp(arrays.bitArray, user.username)) {
                cerr << "Account already exists!\n\n";
                cout << "Do you want to back to main menu ?\n";
                cout
                    << "Press '1' to back to main menu or '3' to continue.\n\n";
                cout << "Your choice: ";
                cin >> check;
                if (check == 1) return;
            }
            if (check == 0)  // Invalid username
                InvaidUsername();
            if (check == 2) {  // Invalid password
                InvalidPassword();
            }
            if (check == 3) {  // Continue to register
                cout << "1. Register";
            }
            cout << "\n\n";
        }
    }
}

// Main menu
void choice(Arrays &arrays) {
    memset(arrays.bitArray, 0, SIZE);
    memset(arrays.bitArrayPass, 0, SIZE * SIZE);
    memset(arrays.bitArrayWeak, 0, SIZE);

    int ch;
    readWeakPass(arrays);
    readFile(arrays);
    Account user;
    cout << "Main Menu: \n";
    cout << "----------------------\n";
    cout << "1. Register\n";
    cout << "2. Login\n\n";
    cout << "Your choice: ";
    cin >> ch;

    if (ch == 1) {
        int check = 0;
        reGister(arrays, user, check);

        if (check == 1) {
            choice(arrays);
        } else {
            Insert(arrays.bitArray, user.username);
            Insert(arrays.bitArrayPass[hashPassword(user.username)],
                   user.password);
            signUpfile(user);

            cout << "2. Login\n\n";

            while (!isLogin(user, arrays, check)) {
                cerr << "Login fail!\n";
                if (check == 1)
                    cerr << "Wrong password!\n\n";
                else
                    cerr << "Invalid account!\n\n";
            }
            changePassChoice(user, arrays);
        }
    } else {
        cout << "2. Login\n\n";
        int check = 0;
        while (!isLogin(user, arrays, check)) {
            cerr << "Login fail!\n";
            if (check == 1)
                cerr << "Wrong password!\n\n";
            else {
                cerr << "Login fail!\n";
                cerr << "Invalid account!\n\n";
                cout << "Do you want to create a new account? \n";
                cout << "Press '2' to back to main menu or '3' to continue "
                        ".\n\n";
                cout << "Your choice: ";
                cin >> check;
            }
            if (check == 2)
                break;
            else if (check == 3) {
                cout << "2. Login\n\n";
            }
        }
        if (check == 2) {
            choice(arrays);
        } else {
            changePassChoice(user, arrays);
        }
    }
}