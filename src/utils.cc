#include "utils.hh"
#include <iostream>

void error(string message) {
    cout << "\033[31m error\033[0m: " << message << endl;
}
