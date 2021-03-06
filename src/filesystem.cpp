#include "filesystem.hpp"

void replace(string &source, string const &find, string const &replace)
{
    for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;) {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

void split(string const &source, string const &delimiter, vector <string> &out)
{
    string::size_type last_pos = 0, i = 0;
    while ((i = source.find(delimiter, i)) != string::npos) {
        out.push_back(source.substr(last_pos, i - last_pos)), last_pos = ++i;
    }
    out.push_back(source.substr(last_pos, source.length() - last_pos));
}

vector <string> getRegexMask(string &&strMask)
{
    vector <string> regexMasks;
    if (!strMask.empty()) {
        replace(strMask, ".", "\\.");
        replace(strMask, "?", ".?");
        replace(strMask, "*", ".*");
        split(strMask, "|", regexMasks);
    }
    return regexMasks;
}

bool checkFileMask(const vector <string> &regexMask, const string &fileName)
{
    for (const string &mask : regexMask) {
        regex reg(mask);
        if (regex_search(fileName.cbegin(), fileName.cend(), reg))
            return true;
    }
    return false;
}

bool directoryExist(const string &directory)
{
    if (!directory.empty()) {
        DIR *dir = opendir(directory.c_str());
        if (dir == nullptr) {
            if (errno == ENOENT)
                return false;
        }
        else
            closedir(dir);
    }
    return true;
}

bool fileExist(const string &filename)
{
    return (access(filename.c_str(), 0) != -1);
}

bool createDirectory(const string &directory)
{
    return (mkdir(directory.c_str(), 0733) == 0);
}

void
getFileList(const string &directory, vector <string> &fileList, const vector <string> &regexMask, bool bSearchSubDir)
{
    DIR *WorkDir = opendir(directory.c_str());
    if (WorkDir == nullptr) {
        throw logic_error("Error opening directory");
    }
    struct dirent *file_info;
    while ((file_info = readdir(WorkDir)) != nullptr) {
        if (file_info->d_type == DT_DIR) {
            if (!strcmp(".", file_info->d_name) || !strcmp("..", file_info->d_name))
                continue;
            if (bSearchSubDir) {
                getFileList(directory + file_info->d_name + "/", fileList, regexMask, bSearchSubDir);
            }
        }
        else {
            if (checkFileMask(regexMask, file_info->d_name))
                fileList.push_back(directory + file_info->d_name);
        }
    }
    closedir(WorkDir);
}
