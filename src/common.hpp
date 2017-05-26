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
#include <iomanip>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

extern bool learn;

extern bool info;

extern std::string style;

void getFileListFromFile(const std::string &filename, std::vector <std::string> &fileList);
int input(int argc, char *argv[], std::vector <std::string> &files);
std::string getDirectoryFromFilePath(const std::string &filePath);
std::string getFilenameFromFilePath(const std::string &filePath);

inline void exceptionPrint(std::exception &exception, const std::string &from = "")
{
    std::cout << RED << from << ": " << exception.what() << RESET << std::endl;
}

inline std::string &stringToLower(std::string &&str)
{
    std::transform(str.cbegin(), str.cend(), str.begin(), ::tolower);
    return str;
}

inline void statusMsg(const std::string &string)
{
    static uint32_t width = 0;
    if (width < string.length())
        width = string.length();
    std::cout << std::setw(width) << std::left << string << '\r' << std::flush;
}

inline void clearStatusMsg()
{
    statusMsg("");
}