#include <iostream>

#include "test.h"

#include <sdbus-c++/IConnection.h>

int main(int argv, char **argc)
{
    std::cout << "hello from permissions\n";
    TEST::run();
    return 0;
}