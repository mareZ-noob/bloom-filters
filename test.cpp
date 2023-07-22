#include <bits/stdc++.h>
using namespace std;

bool checkUsername(string username) {
    int n = username.length();
    for (auto x : username) {
        if (x == ' ') return false;
    }
    if (n >= 10 || n <= 5) return false;

    return true;
}

int main() {
    string user = "123456789";
    cout << checkUsername(user);
    return 0;
}