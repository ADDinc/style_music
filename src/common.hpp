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

extern bool learn;
extern bool info;
extern std::string style;

void getFileListFromFile(const std::string &filename, std::vector<std::string> &fileList);
int input(int argc, char *argv[], std::vector<std::string> &files);

inline void exceptionPrint(std::exception &exception, const std::string& from = "")
{
    std::cout << "\033[1;31m" << from << ": " << exception.what() << "\033[0m" << std::endl;
}

inline std::string& stringToLower(std::string &&str)
{
    std::transform(str.cbegin(), str.cend(), str.begin(), ::tolower);
    return str;
}

inline void statusMsg(const std::string &string)
{
    std::cout << string << '\r' << std::flush;
}
