#include "filesystem.hpp"

void find_and_replace(string& source, string const& find, string const& replace)
{
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

string getRegexMask(const string& strMask)
{
    if (!strMask.empty())
    {
        string outMask = strMask;
        find_and_replace(outMask, ".", "\\.");
        find_and_replace(outMask, "?", ".?");
        find_and_replace(outMask, "*", ".*");
        return outMask;
    }
    return ".*";
}

inline bool checkFileMask(const string& regex_mask, const string& fileName)
{
    regex reg(regex_mask);
    return regex_search(fileName.cbegin(), fileName.cend(), reg);
}

void getFileList(const string& directory, vector<string>& fileList, const string& regex_mask, bool bSearchSubDir)
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
                fileList.push_back(string(file_info->d_name));
        }
    }
    closedir(WorkDir);
}