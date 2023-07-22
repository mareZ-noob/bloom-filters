#include "func.h"

// ghi ra tai khoan da tao thanh cong
void signUpfile(string username, string password){
    ofstream ofs("SignUp.txt", ios::app);
    ofs << username << " " << password << endl;
    ofs.close();
}

// ghi ra tai khoan tao bi loi
void failFile(string username){
    ofstream ofs("Fail.txt", ios::app);
    ofs << username << endl;
    ofs.close();
}

// doc file nguoi dung de tao bitarray
void readFile(bool bitarray[], int size){
    string data,tmp;
    ifstream ifs("SignUp.txt");
    while(!ifs.eof()){
        getline(ifs,data);
        if(data.empty())
            break;
        stringstream ss(data);
        getline(ss,tmp,' ');
        Insert(bitarray,tmp);
    }
    ifs.close();
}

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



bool checkPassword(string username, string password) {
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

bool isLogin(bool* bitarray){
    string tmp;
    string username , password;
    string un , pas ;

    system("cls");
    cout << "2. Login" << endl;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // chua kiem tra password
    if(LookUp(bitarray,username)){
        return true;
    }
    else    
        return false;
}

void choice(bool* bitarray, int size){
    int ch;
    string username , password;
    readFile(bitarray,size);

    cout << "Main Menu: " << endl;
    cout << "----------------------" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << endl;
    cout << "Your choice: ";
    cin >> ch;
    cin.ignore();

    if(ch == 1){
        system("cls");
        // signUp(bitarray,size, username,password);
        cout << "Enter your username: ";
        cin >> username ;
        while(!checkUsername(username,bitarray)){
            InvaidUsername();
            cout << "Enter your username: ";
            cin >> username;
        }
        cout << "Enter your password: ";
        cin >> password;
        while(!checkPassword(username,password)){
            system("cls");
            InvalidPassword();
            cout << "Enter you password: ";
            cin >> password;
        }
        Insert(bitarray,username);
        signUpfile(username, password);
        system("cls");
        cout << "2. Login" << endl;
        if(isLogin(bitarray)){
            system("cls");
            cout << "You can change your password!";
        }
        else{
            system("cls");
            cout << "Login fail!";
        }
    }
    else {
        if(isLogin(bitarray)){
            system("cls");
            cout << "You can change your password!";
        }
        else{
            system("cls");
            cout << "Login fail!";
        }        
    }
}