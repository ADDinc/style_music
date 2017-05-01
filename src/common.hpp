#pragma once
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>
#include <map>
#include <unistd.h>

inline void exceptionPrint(std::exception &excep, const std::string& from = "")
{
    std::cout << "\033[1;31m" << from<< ": " << excep.what() << "\033[0m" << std::endl;
}

inline std::string& stringTolower(std::string &str)
{
    std::transform(str.cbegin(), str.cend(), str.begin(), ::tolower);
    return str;
}
