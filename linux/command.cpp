#include "general.cpp"
#include "myfile.cpp"
#include "statements.cpp"
#include <cstdio>
#include <dirent.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>
#define MY_DIR "mydir"
#define MY_CD "mycd"
#define MY_COPY "mycopy"
#define MY_DEL "mydel"
#define MY_PWD "mypwd"
#define MY_HELP "myhelp"
#define MY_EXIT "myexit"
#define mfPointer MyFile *

using namespace std;

vcPointer listFiles(string path);
void showFiles(vcPointer files);
bool isFolder(string path);
void myHelp() {
    clearScreen();
    cout << MY_DIR << "列出目录及文件" << endl;
    cout << MY_CD << "改变当前文件夹" << endl;
    cout << MY_COPY << "复制文件" << endl;
    cout << MY_DEL << "删除目录" << endl;
    cout << MY_PWD << "显示当前目录名" << endl;
    cout << MY_EXIT << "退出系统" << endl;
}

void myDir(stPointer statements) {
    if (statements->getCommand() == MY_DIR &&
        !statements->getOriginalPath().empty() &&
        statements->getTargetPath().empty()) {
        vcPointer files = listFiles(statements->getOriginalPath());
        showFiles(files);
    } else {
        cout << "该命令格式有误,非" << MY_DIR << "命令" << endl;
        return;
    }
}

void myCD(stPointer statements, mfPointer *currentPath) {
    if (statements->getCommand() == MY_CD &&
        !statements->getOriginalPath().empty() &&
        statements->getTargetPath().empty()) {
        string oPath = statements->getOriginalPath();
        if (isFolder(oPath)) {
            if (oPath[oPath.length() - 1] != '/') {
                oPath.append("/");
            }
            *currentPath = new MyFile(oPath);
            (*currentPath)->showLocation();
        } else {
            cout << "该路径不是文件夹，不能切换目录到文件" << endl;
        }
    } else {
        cout << "该命令格式有误,非" << MY_CD << "命令" << endl;
        return;
    }
}

void myCopy(stPointer statements, mfPointer *currentPath) {
    // statements->showStatements();
    if (statements->getCommand() == MY_COPY &&
        !statements->getTargetPath().empty() &&
        !statements->getOriginalPath().empty()) {
        // statements->showStatements();
        cout << "mycopy" << endl;
        // statements->changToAbsolute(*currentPath);
        // statements->showStatements();
    } else {
        cout << "该命令格式有误,非" << MY_COPY << "命令" << endl;
        return;
    }
}

// void myDel() {
//     mfPointer mf = new MyFile("test/123");
//     cout << mf->getLocation() << endl;
//     cout << mf->getFileName() << endl;
//     cout << "mydel" << endl;
// }

// void listFiles(string path) {
//     vector<string> dirname;
//     struct _finddata_t findFile;
//     int end = 0;
//     int start = _findfirst(path.c_str().& findFile);
//     if (start == -1) {
//         return;
//     }
//     while (!(done = _findnext(start, &findFile))) {
//         if ((_A_SUBDIR == findFile.attrib)) {
//             dirname.push_back(findFile.name);
//         }
//     }
//     vector<string>::iterator begin = dirname.begin();
//     vector<string>::iterator end = dirname.end();
//     while (begin != end) {
//         cout << *begin << endl;
//     }
//     _findclose(start);
// }

// void filesearch(string path, int layer) {
//     int num = 0;
//     string dirname[100] = {""};
//     struct _finddata_t filefind;
//     string curr = path + "\\*.*";
//     int done = 0, i = 0, j, handle;
//     if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)
//         return;
//     while (!(done = _findnext(handle, &filefind))) {
//         if ((_A_SUBDIR == filefind.attrib))
//             dirname[num++] = filefind.name;
//     }
//     for (j = 0; j <= num; j++) {
//         cout << dirname[j] << endl;
//     }
//     _findclose(handle);
// }
// int listfile() {
//     string path = "D:\\Test";
//     filesearch(path, 0);
//     return 0;
// }
vcPointer listFiles(string path) {
    vcPointer files = new vector<string>();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                files->push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
    }
    return files;
}

void showFiles(vcPointer files) {
    if (files != NULL) {
        vector<string>::iterator begin = files->begin();
        vector<string>::iterator end = files->end();
        int index = 0;
        cout << left;
        while (begin != end) {
            cout << setw(30) << *begin;
            if (++index % 5 == 0) {
                cout << endl;
                cout << left;
            }
            begin++;
        }
        if (index % 5 != 0) {
            cout << endl;
        }
    }
}

bool isFolder(string path) {
    struct stat st;
    stat(path.c_str(), &st);
    if (S_ISDIR(st.st_mode)) {
        return 1;
    } else {
        return 0;
    }
}