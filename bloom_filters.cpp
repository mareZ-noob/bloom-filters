#include "bloom_filters.h"

long long hash1(string s) {
    long long hash = 0;
    for (long unsigned int i = 0; i < s.size(); i++) {
        hash = (hash + ((int)s[i]));
        hash = hash % SIZE;
    }
    return hash;
}

long long hash2(string s) {
    long long hash = 1;
    for (long unsigned int i = 0; i < s.size(); i++) {
        hash = hash + pow(19, i) * s[i];
        hash = hash % SIZE;
    }
    return hash % SIZE;
}

long long hash3(string s) {
    long long hash = 7;
    for (long unsigned int i = 0; i < s.size(); i++) {
        hash = (hash * 31 + s[i]) % SIZE;
    }

    return hash % SIZE;
}

long long hash4(string s) {
    long long hash = 3;
    int p = 7;
    for (long unsigned int i = 0; i < s.size(); i++) {
        hash += hash * 7 + s[i] * pow(p, i);
        hash = hash % SIZE;
    }
    return hash;
}

long long doubleHash(int hash1, int hash2, int i) {
    return (hash1 + i * hash2) % SIZE;
}

long long hashPassword(string s) {
    long long hash = 0;

    for (int i = 0; i < 4; i++) {
        int h1 = hash1(s);
        int h2 = hash2(s);
        hash += doubleHash(h1, h2, i);
    }

    for (int i = 0; i < 4; i++) {
        int h3 = hash3(s);
        int h4 = hash4(s);
        hash += doubleHash(h3, h4, i);
    }

    return hash % SIZE;
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
        cout << s << " is Probably already present\n";
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