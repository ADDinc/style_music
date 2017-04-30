#pragma once
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>

inline void exceptionPrint(std::exception &excep, const std::string& from = "")
{
    std::cout << "\033[1;31m" << from<< ": " << excep.what() << "\033[0m" << std::endl;
}
