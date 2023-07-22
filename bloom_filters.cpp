#include "main.h"
using namespace std;

ll int hash1(string s) {
    ll int hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash + ((int)s[i]));
        hash = hash % SIZE;
    }
    return hash;
}

ll int hash2(string s) {
    ll int hash = 1;
    for (int i = 0; i < s.size(); i++) {
        hash = hash + pow(19, i) * s[i];
        // hash = hash * 19 + s[i];
        hash = hash % SIZE;
    }
    return hash % SIZE;
}

ll int hash3(string s) {
    ll int hash = 7;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash * 31 + s[i]) % SIZE;
    }

    return hash % SIZE;
}

ll int hash4(string s) {
    ll int hash = 3;
    int p = 7;
    for (int i = 0; i < s.size(); i++) {
        hash += hash * 7 + s[i] * pow(p, i);
        hash = hash % SIZE;
    }
    return hash;
}

bool LookUp(bool *bitArray, string s) {
    int a = hash1(s);
    int b = hash2(s);
    int c = hash3(s);
    int d = hash4(s);

    if (bitArray[a] && bitArray[b] && bitArray[c] && bitArray[d])
        return true;
    else
        return false;
}

void Insert(bool *bitArray, string s) {
    if (LookUp(bitArray, s)) {
        cout << s << " is Probably already present" << endl;
    } else {
        int a = hash1(s);
        int b = hash2(s);
        int c = hash3(s);
        int d = hash4(s);

        bitArray[a] = true;
        bitArray[b] = true;
        bitArray[c] = true;
        bitArray[d] = true;
    }
}

int hashPassword(string s)
{
    ll hash = hash1(s) * pow(257.0, 4.0); 
    hash = hash % SIZE; 
    hash += hash2(s) * pow(257, 3); 
    hash = hash % SIZE; 
    hash += hash3(s) * pow(257, 2);
    hash = hash % SIZE;  
    hash += hash4(s) * 257;
    hash = hash % SIZE; 

    return hash;
}

// int main() {
//     bool bitArray[100] = {false};
//     int size = 100;
//     string strArr[33] = {
//         "abound",   "abounds",       "abundance",  "abundant", "accessable",
//         "bloom",    "blossom",       "bolster",    "bonny",    "bonus",
//         "bonuses",  "coherent",      "cohesive",   "colorful", "comely",
//         "comfort",  "gems",          "generosity", "generous", "generously",
//         "genial",   "bluff",         "cheater",    "hate",     "war",
//         "humanity", "racism",        "hurt",       "nuke",     "gloomy",
//         "facebook", "geeksforgeeks", "twitter"};
//     for (auto s : strArr) insert(bitArray, s);

//     bool found = lookup(bitArray, "Comely1");
//     bool notFound = lookup(bitArray, "comely");

//     cout << found << endl;
//     cout << notFound << endl;

//     return 0;
//     cout << 1 + 3;
//     return 0;
// }