#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <dirent.h>
#include <regex>
#include "common.hpp"

using namespace std;

void find_and_replace(string& source, string const& find, string const& replace);
string getRegexMask(const string& strMask);
bool checkFileMask(const string& regex_mask, const string& fileName);
void getFileList(const string& directory, vector<string>& fileList, const string& regex_mask = ".*", bool bSearchSubDir = false);

#endif
