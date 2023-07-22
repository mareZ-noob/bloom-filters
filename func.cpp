#include "bloom_filters.cpp"

// ghi ra tai khoan da tao thanh cong
void signUpfile(Account user){
    ofstream ofs("SignUp.txt", ios::app);
    ofs << user.username << " " << user.password << endl;
    ofs.close();
}

// ghi ra tai khoan tao bi loi
void failFile(Arrays &arrays, Account user){
    ofstream ofs("Fail.txt", ios::app);
    ofs << user.username << " " << user.password << endl;
    ofs.close();
}

// doc file nguoi dung de tao bitarray
void readFile(Arrays &arrays, int size){
    string data,tmp;
    string username;
    ifstream ifs("SignUp.txt");
    while(!ifs.eof()){
        getline(ifs,data);
        if(data.empty())
            break;
        stringstream ss(data);
        getline(ss,tmp,' ');
        Insert(arrays.bitarray,tmp);
        username = tmp;
        getline(ss,tmp);
        Insert(arrays.bitarrayPass[hashPassword(username)], tmp);
    }
    ifs.close();
}

void readWeakPass(Arrays &arrays){
    string data;
    ifstream ifs("WeakPass.txt");
    while(!ifs.eof()){
        getline(ifs,data);
        if(data.empty())
            break;
        if(!LookUp(arrays.bitarrayWeak,data))
            Insert(arrays.bitarrayWeak,data);
    }
}

bool checkUsername(string username, Arrays &arrays) {
    int n = username.length();
    for (auto x : username) {
        if (x == ' ') return false;
    }

    if (n >= 10 || n <= 5 || LookUp(arrays.bitarray, username)) return false;

    return true;
}

void InvaidUsername() {
    cout << "Your username is invalid. Note that:" << endl;
    cout << "\t- 5 < sizeof(Username) < 10." << endl;
    cout << "\t- Username must not contain spaces." << endl;
    cout << "\t- Username must not be the same as any registered Username."
         << endl;
}

bool checkPassword(string username, string password, Arrays &arrays) {
    if(LookUp(arrays.bitarrayWeak, password))
        return false;
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

// void changePassword(Account &user){
//     string data;
//     cout << "Enter your new password: ";
//     cin >> user.password;
//     ofstream ofs("SignUp.txt");
//     ifstream ifs("SignUp.txt");
//     while(!ifs.eof()){
//         getline(ifs, data, ' ');
//         if(data.empty())
//             break;
//         if(data == user.username){
//             ofs = ifs;
//             ofs << user.password;
//         }
//     }
//     ifs.close();
//     ofs.close();
// }

bool isLogin(Arrays &arrays, int &check){
    Account user, tmp;

    system("cls");
    cout << "2. Login" << endl;
    cout << "Enter your username: ";
    cin >> user.username;
    cout << "Enter your password: ";
    cin >> user.password;
    check = 0;

    ifstream ifs("SignUp.txt");
    while(!ifs.eof()){
        getline(ifs,tmp.username,' ');
        getline(ifs,tmp.password);
        if(tmp.username == user.username && tmp.password == user.password){
            cout << "Logged in successfully!" << endl;
            return true;
        }
        if(tmp.username == user.username)
            check = 1;
    }
    return false;
}

bool checkRegister(Arrays arrays, Account user){
    if(checkPassword(user.username, user.password, arrays) && checkUsername(user.username, arrays)){
        cout << "Login successfully";
        return true;
    }
    else
        return false;
}

void choice(Arrays &arrays, int size){
    int ch;
    readFile(arrays, size);
    Account user;
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
        bool flag = true;
        
        while(flag){
            cout << "Enter your username: ";
            cin >> user.username;
            cout << "Enter your password: ";
            cin >> user.password;
            if(checkRegister(arrays, user))
                flag = false;
            else    
                failFile(arrays, user);
        }

        Insert(arrays.bitarray,user.username);
        Insert(arrays.bitarrayPass[hashPassword(user.username)], user.password);
        signUpfile(user);
        
        system("cls");
        cout << "2. Login" << endl;
        int check;
        while (!isLogin(arrays, check))
        {
            cout << "Login fail!" << endl;
            if(check == 1)
                cout << "Wrong password!" << endl;
            else 
                cout << "Invalid account!" << endl;
        }
        system("cls");
        cout << "You can change your password!";
        
    }
    else {
        system("cls");
        int check;
        while (!isLogin(arrays, check))
        {
            cout << "Login fail!" << endl;
            if(check == 1)
                cout << "Wrong password!" << endl;
            else 
                cout << "Invalid account!" << endl;
        }
        system("cls");
        cout << "You can change your password!";        
    }
}