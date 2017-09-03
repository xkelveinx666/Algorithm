#include "general.cpp"
#include "path.cpp"
#include "statements.cpp"
#include <cstdio>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#define MY_DIR "mydir"
#define MY_CD "mycd"
#define MY_COPY "mycopy"
#define MY_DEL "mydel"
#define MY_PWD "mypwd"
#define MY_HELP "myhelp"
#define MY_EXIT "myexit"

using namespace std;

vcPointer listFiles(string path);
void showFiles(vcPointer files);
void dfsFolder(pPointer oPath, pPointer tPath, int *count);
bool copyFile(pPointer oPath, pPointer tPath);
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

void myCD(stPointer statements, pPointer *currentPath) {
    if (statements->getCommand() == MY_CD &&
        !statements->getOriginalPath().empty() &&
        statements->getTargetPath().empty()) {
        pPointer oPath = new Path(statements->getOriginalPath());
        if (oPath->isFolder()) {
            *currentPath = oPath;
            (*currentPath)->showLocation();
        } else {
            cout << "该路径不是文件夹，不能切换目录到文件" << endl;
        }
    } else {
        cout << "该命令格式有误,非" << MY_CD << "命令" << endl;
        return;
    }
}

void myCopy(stPointer statements, pPointer *currentPath) {
    // statements->showStatements();
    if (statements->getCommand() == MY_COPY &&
        !statements->getTargetPath().empty() &&
        !statements->getOriginalPath().empty()) {
        pPointer tPath = new Path(statements->getTargetPath());
        pPointer oPath = new Path(statements->getOriginalPath());
        if (tPath->isFolder()) {
            int failCount = 0;
            dfsFolder(tPath, oPath, &failCount);
            cout << failCount << "个文件复制失败" << endl;
        } else {
            cout << "目的地路径必须为文件夹" << endl;
        }
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

void dfsFolder(pPointer oPath, pPointer tPath, int *count) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(oPath->getFullPath().c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                pPointer newOPath = new Path(oPath->getFullPath());
                newOPath->nextFolder(string(ent->d_name));
                pPointer newTPath = new Path(tPath->getFullPath());
                newTPath->nextFolder(string(ent->d_name));
                if (newOPath->isFolder()) {
                    dfsFolder(newOPath, newTPath, count);
                } else {
                    if (!copyFile(newOPath, newTPath)) {
                        (*count)++;
                    }
                }
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
    }
}
bool copyFile(pPointer originalFile, pPointer targetFile) {
    ifstream in;
    ofstream out;
    in.open(originalFile->getFilePath().c_str(), ios::binary);
    if (in.fail()) {
        in.close();
        out.close();
        cout << "打开文件失败" << originalFile->getFileName() << endl;
        return false;
    }
    out.open(targetFile->getFilePath().c_str(), ios::binary);
    if (out.fail()) //创建文件失败
    {
        cout << "创建文件失败" << targetFile->getFileName() << endl;
        out.close();
        in.close();
        return false;
    }
    out << in.rdbuf();
    out.close();
    in.close();
    return true;
}