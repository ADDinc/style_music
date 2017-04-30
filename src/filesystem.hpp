#pragma once
#include <dirent.h>
#include <regex>
#include "common.hpp"

using namespace std;

void replace(string &source, string const &find, string const &replace);
void split(string const& source, string const& delimiter, vector<string>& out);
vector<string> getRegexMask(string&& strMask);
bool directoryExist(const string& directory);
bool checkFileMask(const vector<string>& regex_mask, const string& fileName);
void getFileList(const string& directory, vector<string>& fileList, const vector<string>& regex_mask, bool bSearchSubDir = false);
