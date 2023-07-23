#include "bloom_filters.cpp"

// ghi ra tai khoan da tao thanh cong
void signUpfile(Account user){
    ofstream ofs("SignUp.txt", ios::app);
    ofs << user.username << " " << user.password << endl;
    ofs.close();
    return;
}

// ghi ra tai khoan tao bi loi
void failFile(Account user){
    ofstream ofs("Fail.txt", ios::app);
    ofs << user.username << " " << user.password << endl;
    ofs.close();
    return;
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
    return;
}

// doc file mk yeu vao bitarray
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
    ifs.close();
    return;
}

// kiem tra ten hop le
bool checkUsername(string username, Arrays &arrays) {
    int n = username.length();
    for (auto x : username) {
        if (x == ' ') return false;
    }

    if (n >= 10 || n <= 5 || LookUp(arrays.bitarray, username)) return false;

    return true;
}

// in ra man hinh nhung dieu kien cua mot ten hop le
void InvaidUsername() {
    cout << "Your username is invalid. Note that:" << endl;
    cout << "\t- 5 < sizeof(Username) < 10." << endl;
    cout << "\t- Username must not contain spaces." << endl;
    cout << "\t- Username must not be the same as any registered Username."
         << endl;
}

// kiem tra password hop le
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

// in ra man hinh dieu kien password hop le
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

// kiem tra dang nhap
bool isLogin(Account &user, Arrays &arrays, int &check){

    cout << "Enter your username: ";
    cin >> user.username;
    cout << "Enter your password: ";
    cin >> user.password;
    check = 0;

    bool uSer = LookUp(arrays.bitarray,user.username);
    bool pass = LookUp(arrays.bitarrayPass[hashPassword(user.username)], user.password);
    if(uSer && pass){
        return true;
    }
    else if(uSer && !pass){
        check = 1;
    }

    return false;
}

// kiem tra dang ky
bool checkRegister(Arrays arrays, Account user, int &check){
    if(!checkUsername(user.username,arrays)) check = 0;
    else if(!checkPassword(user.username,user.password,arrays)) check = 2;
    if(checkPassword(user.username, user.password, arrays) && checkUsername(user.username, arrays)){
        cout << "Login successfully";
        return true;
    }
    else
        return false;
}

// thay doi mat khau va ghi ra file mk moi
void changePassWord(Account &user, Arrays &arrays){
    vector<Account> list ;
    Account tmp;
    string data;

    ifstream ifs("SignUp.txt");
    while(!ifs.eof()){
        getline(ifs,data);
        if(data.empty())
            break;
        stringstream ss(data);
        getline(ss,tmp.username,' ');
        getline(ss,tmp.password);
        list.push_back(tmp);
    }
    ifs.close();

    int idx = 0;
    for(int i = 0; i < list.size(); i++){
        if(list[i].username == user.username){
            idx = i;
            break;
        }
    }

    cout << "Enter your new password: ";
    cin >> tmp.password;

    while(!checkPassword(list[idx].username, tmp.password, arrays)){
        failFile(user);
        InvalidPassword();
        cout << endl << "Enter your new password: ";
        cin >> tmp.password;
    }

    list[idx].password = tmp.password;

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

// khi nguoi dung chon lua chon thay doi mat khau
void changePassChoice(Account &user, Arrays &arrays){
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
        cin.ignore();
        system("cls");
        cout << "1. Change password" << endl << endl;
        changePassWord(user,arrays);
    }
}

// khi nguoi dung chon dang ki
void reGister(Arrays &arrays, Account &user, int &check){
    system("cls");
    cout << "1. Register" << endl << endl;
    bool flag = true;
    check = 0;
    while(flag){
        cout << "Enter your username: ";
        cin >> user.username;
        cout << "Enter your password: ";
        cin >> user.password;
        if(checkRegister(arrays, user,check))
            return;
        else{
            failFile(user);
            if(check == 0 && LookUp(arrays.bitarray,user.username)){ // kiem tra xem nguoi dung co muon quay lai trang dang nhap ko
                system("cls");
                cout << "Account already exists!" << endl << endl;
                cout << "Do you want to back to main menu ?" << endl;
                cout << "Press '1' to back to main menu or '3' to continue." << endl << endl;
                cout << "Your choice: ";
                cin >> check;
                if(check == 1)
                    return;
            }
            if(check == 0) // Ten sai dieu kien
                InvaidUsername();
            if(check == 2){ // Mat khau sai dieu kien
                InvalidPassword();
            }
            if(check == 3){ // Neu nguoi dung chon tiep tuc dang ky tai khoan
                system("cls");
                cout << "1. Register" ;
            }
            cout << endl << endl;
        }
    }
}

// main menu
void choice(Arrays &arrays){
    
    memset(arrays.bitarray, 0, SIZE);
    memset(arrays.bitarrayPass, 0, SIZE*SIZE);
    memset(arrays.bitarrayWeak, 0, SIZE);
    
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

    if(ch == 1){
        int check = 0;
        reGister(arrays, user, check);

        if(check == 1){
            system("cls");
            choice(arrays);
        }
        else{
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
            changePassChoice(user, arrays);
        }
    }
    else {
        system("cls");
        cout << "2. Login" << endl << endl;
        int check = 0;
        while (!isLogin(user, arrays, check))
        {
            cout << "Login fail!" << endl;
            if(check == 1)
                cout << "Wrong password!" << endl << endl;
            else {
                system("cls");
                cout << "Login fail!" << endl;
                cout << "Invalid account!" << endl << endl;
                cout << "Do you want to create a new account? " << endl;
                cout << "Press '2' to back to main menu or '3' to continue ." << endl << endl;
                cout << "Your choice: ";
                cin >> check;
            }
            if(check == 2)
                break;
            else if(check == 3){
                system("cls");
                cout << "2. Login" << endl << endl;
            }
        }
        if(check == 2){
            system("cls");
            choice(arrays);
        }
        else{
            changePassChoice(user, arrays);
        }
    }
}