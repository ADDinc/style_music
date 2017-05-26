#include "common.hpp"
#include "filesystem.hpp"

using namespace std;

void getFileListFromFile(const string &filename, vector <string> &fileList)
{
    ifstream file(filename, ios_base::in);
    string audio;
    if (file.is_open()) {
        while (getline(file, audio)) {
            if (fileExist(audio)) {
                fileList.push_back(audio);
            }
            else {
                if (fileExist(getDirectoryFromFilePath(filename) + audio))
                    fileList.push_back(getDirectoryFromFilePath(filename) + audio);
                else
                    cerr << "File \"" << audio << "\" is missing!" << endl;
            }
            audio.clear();
        }
        file.close();
    }
}

int input(int argc, char *argv[], vector <string> &files)
{
    if (argc == 1) {
        cout << "Use: " << argv[0] << " <filename|-d (directory)|-f (file)> <необязательные параметры>" << endl;
        return -1;
    }

    int rez = 0;
    while (rez != -1) {
        if ((rez = getopt(argc, argv, "d::if::l:")) == -1) {
            if (optind < argc) {
                if (argv[optind] != nullptr && fileExist(argv[optind])) {
                    files.push_back(argv[optind]);
                }
                argv += optind;
                argc -= optind;
                optind = 0;
                rez = 0;
            }
            else {
                break;
            }
        }
        else {
            switch (rez) {
            case 'd':
                if (optarg != nullptr) {
                    getFileList(string(optarg) + "/", files, getRegexMask("*.flac|*.mp3|*.m4a"));
                }
                else {
                    if (argv[optind] != nullptr) {
                        if (argv[optind][0] != '-')
                            getFileList(string(argv[optind++]) + "/", files, getRegexMask("*.flac|*.mp3|*.m4a"));
                        break;
                    }
                    cerr << "Use: -d <directory>" << endl;
                }
                break;
            case 'l':
                style = stringToLower(optarg);
                learn = true;
                break;
            case 'f':
                if (optarg != nullptr) {
                    getFileListFromFile(optarg, files);
                }
                else {
                    if (argv[optind] != nullptr) {
                        if (argv[optind][0] != '-')
                            getFileListFromFile(argv[optind++], files);
                        break;
                    }
                    cerr << "Use: -f <filename>" << endl;
                }
                break;
            case 'i':
                info = true;
                break;
            case '?':
                cout << "Not found!" << endl;
                break;
            }
        }
    };
    return 0;
}

string getDirectoryFromFilePath(const string &filePath)
{
    return filePath.substr(0, filePath.find_last_of('/') + 1);
}

string getFilenameFromFilePath(const string &filePath)
{
    return filePath.substr(filePath.find_last_of('/') + 1);
}