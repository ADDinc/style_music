#pragma once
#include <dirent.h>
#include <sys/stat.h>
#include <regex>
#include "common.hpp"

using namespace std;

void replace(string &source, string const &find, string const &replace);
void split(string const &source, string const &delimiter, vector<string> &out);
vector<string> getRegexMask(string&& strMask);
bool directoryExist(const string &directory);
bool createDirectory(const string &directory);
bool fileExist(const string &file);
bool checkFileMask(const vector<string> &regexMask, const string &fileName);
void getFileList(const string &directory, vector<string> &fileList, const vector<string> &regexMask, bool bSearchSubDir = true);
