#include "bloom_filters.cpp"

// ghi ra tai khoan da tao thanh cong
void signUpfile(Account user){
    ofstream ofs("SignUp.txt", ios::app);
    ofs << user.username << " " << user.password << endl;
    ofs.close();
}

// ghi ra tai khoan tao bi loi
void failFile(Account user){
    ofstream ofs("Fail.txt", ios::app);
    ofs << user.username << " " << user.password << endl;
    ofs.close();
}

// doc file nguoi dung de tao bitarray
void readFile(Arrays &arrays){
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

bool isLogin(Account &user, Arrays &arrays, int &check){
    Account tmp;

    // system("cls");
    // cout << "2. Login" << endl;
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

bool checkRegister(Arrays arrays, Account user, int &check){
    if(!checkUsername(user.username,arrays)) check = 1;
    else if(!checkPassword(user.username,user.password,arrays)) check = 2;
    if(checkPassword(user.username, user.password, arrays) && checkUsername(user.username, arrays)){
        cout << "Login successfully";
        return true;
    }
    else
        return false;
}

void changePassWord(Account user, Arrays &arrays){
    vector<Account> list;
    Account tmp;
    string data;

    ifstream ifs("SignUp.txt");
    while(!ifs.eof()){
        getline(ifs,data);
        if(data.empty())
            break;
        stringstream ss(data);
        getline(ss,tmp.username, ' ');
        getline(ss,tmp.password);
        list.push_back(tmp);
    }

    ifs.close();

    int index = 0;

    for( ; index < list.size(); index++){
        if(list[index].username == user.username)
            break;
    }

    cout << "Enter your new password: ";
    cin >> tmp.password;

    while(!checkPassword(list[index].username, tmp.password, arrays)){
        failFile(user);
        InvalidPassword();
        cout << endl << "Enter your new password: ";
        cin >> tmp.password;
    }

    list[index].password = tmp.password;

    cout << "Your password has been changed successfully! ";

    ofstream ofs("SignUp.txt");
    for(int i = 0 ; i < list.size() ; i++){
        ofs << list[i].username << " " << list[i].password << endl;
    }
    ofs.close();

    memset(arrays.bitarray, 0, SIZE);
    memset(arrays.bitarrayPass, 0, SIZE*SIZE);

    readFile(arrays);
}

void changePass(Account user, Arrays &arrays){
    int choice;
    system("cls");
    cout << "Logged in successfully!" << endl;
    cout << "Menu: " << endl;
    cout << "----------------------" << endl;
    cout << "1. Change password" << endl;
    cout << "0. Quit" << endl;
    cout << "Your choice: ";
    cin >> choice ;
    if(choice == 0){
        system("cls");
        cout << "You exited the program!";
        return;
    }
    else{
        system("cls");
        cout << "1. Change password" << endl << endl;
        changePassWord(user,arrays);
    }
}

void choice(Arrays &arrays){
    int ch;
    readWeakPass(arrays);
    readFile(arrays);
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
        cout << "1. Register" << endl << endl;
        bool flag = true;
        int check;
        while(flag){
            cout << "Enter your username: ";
            cin >> user.username;
            cout << "Enter your password: ";
            cin >> user.password;
            if(checkRegister(arrays, user,check))
                flag = false;
            else{
                failFile(user);
                if(check == 1)
                    InvaidUsername();
                if(check == 2)
                    InvalidPassword();
                cout << endl << endl;
            }
        }

        Insert(arrays.bitarray,user.username);
        Insert(arrays.bitarrayPass[hashPassword(user.username)], user.password);
        signUpfile(user);

        system("cls");
        cout << "2. Login" << endl << endl;

        while (!isLogin(user,arrays, check))
        {
            cout << "Login fail!" << endl;
            if(check == 1)
                cout << "Wrong password!" << endl << endl;
            else 
                cout << "Invalid account!" << endl << endl;
        }
        changePass(user, arrays);
    }
    else {
        system("cls");
        cout << "2. Login" << endl << endl;
        int check;
        while (!isLogin(user, arrays, check))
        {
            cout << "Login fail!" << endl;
            if(check == 1)
                cout << "Wrong password!" << endl << endl;
            else 
                cout << "Invalid account!" << endl << endl;
        }   
        changePass(user, arrays);
    }
}