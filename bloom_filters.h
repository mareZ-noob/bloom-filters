#ifndef _BLOOM_FILTERS_H_
#define _BLOOM_FILTERS_H_

#include "main.h"
#define ll long long
#define SIZE 1000
using namespace std;
// Hash
ll int hash1(string s);
ll int hash2(string s);
ll int hash3(string s);
ll int hash4(string s);

bool LookUp(bool *bitArray, string s);
void Insert(bool *bitArray, string s);

#endif  // _BLOOM_FILTERS_H