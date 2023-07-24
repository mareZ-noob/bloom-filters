#ifndef __BLOOM_FILTERS_H_
#define __BLOOM_FILTERS_H_

#include "main.h"

// Hash
long long hash1(string s);
long long hash2(string s);
long long hash3(string s);
long long hash4(string s);
long long doubleHash(int hash1, int hash2, int i);
long long hashPassword(string s);

// Method
bool LookUp(bool *bitArray, string s);
void Insert(bool *bitArray, string s);

#endif  // __BLOOM_FILTERS_H