#include "filesystem.hpp"

void replace(string &source, string const &find, string const &replace)
{
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

void split(string const& source, string const& delimiter, vector<string>& out)
{
    string::size_type last_pos = 0, i = 0;
    while((i = source.find(delimiter, i)) != string::npos)
    {
        out.push_back(source.substr(last_pos, i - last_pos)), last_pos = ++i;
    }
    out.push_back(source.substr(last_pos, source.length() - last_pos));
}

vector<string> getRegexMask(string&& strMask)
{
    vector<string> regexMasks;
    if (!strMask.empty())
    {
        replace(strMask, ".", "\\.");
        replace(strMask, "?", ".?");
        replace(strMask, "*", ".*");
        split(strMask, "|", regexMasks);
    }
    return regexMasks;
}

bool checkFileMask(const vector<string>& regex_mask, const string& fileName)
{
    for (const string &mask : regex_mask)
    {
        regex reg(mask);
        if (regex_search(fileName.cbegin(), fileName.cend(), reg))
            return true;
    }
    return false;
}

void getFileList(const string& directory, vector<string>& fileList, const vector<string>& regex_mask, bool bSearchSubDir)
{
    DIR *WorkDir = opendir(directory.c_str());
    if (WorkDir == nullptr)
    {
        throw logic_error("Error opening directory");
    }
    struct dirent *file_info;
    while((file_info = readdir(WorkDir)) != nullptr)
    {
        if (file_info->d_type == DT_DIR)
        {
            if (!strcmp(".", file_info->d_name) || !strcmp("..", file_info->d_name))
                continue;
            if (bSearchSubDir)
            {
                getFileList(directory + file_info->d_name + "/", fileList, regex_mask, bSearchSubDir);
            }
        }
        else
        {
            if (checkFileMask(regex_mask, file_info->d_name))
                fileList.push_back(directory + file_info->d_name);
        }
    }
    closedir(WorkDir);
}