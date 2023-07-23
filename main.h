#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>

#define ll long long
#define SIZE 500

#include "bloom_filters.h"
#include "func.h"

using namespace std;

struct Arrays {
    bool bitarray[SIZE] = {false};
    bool bitarrayPass[SIZE][SIZE] = {false};
    bool bitarrayWeak[SIZE] = {false};
};

struct Account {
    string username;
    string password;
};

#endif  // _MAIN_H