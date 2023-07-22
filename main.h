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

#include "bloom_filters.cpp"
#include "func.cpp"

using namespace std;

struct Account {
    string username;
    string password;
};

#endif  // _MAIN_H