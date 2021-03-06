#include "general.cpp"
#include "path.cpp"
#include "statements.cpp"
#include <cstdio>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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
void copyFolder(pPointer oPath, pPointer tPath, int *count);
void deleteFolder(pPointer oPath, int *count);
bool copyFile(pPointer oPath, pPointer tPath);
bool removeFile(pPointer file);
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
        statements->getTargetPath().empty() && statements->exists()) {
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
        statements->getTargetPath().empty() && statements->exists()) {
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

void myCopy(stPointer statements) {
    if (statements->getCommand() == MY_COPY &&
        !statements->getTargetPath().empty() &&
        !statements->getOriginalPath().empty() &&
        statements->existsOriginalPath()) {
        pPointer tPath = new Path(statements->getTargetPath());
        pPointer oPath = new Path(statements->getOriginalPath());
        if (!statements->existsTargetPath()) {
            cout << "即将新建文件夹" << endl;
#ifdef WIN32
            mkdir(tPath->getFullPath().c_str());
#else
            mkdir(tPath->getFullPath().c_str(), 0777);
#endif
        }
        if (statements->existsTargetPath() && tPath->isFolder()) {
            int failCount = 0;
            copyFolder(oPath, tPath, &failCount);
            cout << failCount << "个文件复制失败" << endl;
        } else {
            cout << "目的地路径必须为文件夹" << endl;
        }
    } else {
        cout << "该命令格式有误,非" << MY_COPY << "命令" << endl;
        return;
    }
}

void myDel(stPointer statements) {
    if (statements->getCommand() == MY_DEL &&
        !statements->getOriginalPath().empty() &&
        statements->getTargetPath().empty() && statements->exists()) {
        pPointer oPath = new Path(statements->getOriginalPath());
        int failCount = 0;
        if (oPath->isFolder()) {
            deleteFolder(oPath, &failCount);
            rmdir(oPath->getFilePath().c_str());
        } else {
            cout << oPath->getFilePath() << endl;
            removeFile(oPath);
        }
        cout << failCount << "个文件删除失败" << endl;
    } else {
        cout << "该命令格式有误,非" << MY_DEL << "命令" << endl;
        return;
    }
}

vcPointer listFiles(string path) {
    vcPointer files = new vector<string>();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                files->push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
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

void copyFolder(pPointer oPath, pPointer tPath, int *count) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(oPath->getFullPath().c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                pPointer newOPath = new Path(oPath->getFullPath());
                newOPath->nextFolder(string(ent->d_name));
                pPointer newTPath = new Path(tPath->getFullPath());
                newTPath->nextFolder(string(ent->d_name));
                if (newOPath->isFolder()) {
#ifdef WIN32
                    mkdir(newTPath->getFullPath().c_str());
#else
                    mkdir(newTPath->getFullPath().c_str(), 0777);
#endif
                    copyFolder(newOPath, newTPath, count);

                } else {
                    if (!copyFile(newOPath, newTPath)) {
                        (*count)++;
                    }
                }
            }
        }
        closedir(dir);
    } else {
        perror("");
    }
}

void deleteFolder(pPointer oPath, int *count) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(oPath->getFullPath().c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                pPointer newOPath = new Path(oPath->getFullPath());
                newOPath->nextFolder(string(ent->d_name));
                if (newOPath->isFolder()) {
                    deleteFolder(newOPath, count);
                    rmdir(newOPath->getFilePath().c_str());
                } else {
                    if (!removeFile(newOPath)) {
                        (*count)++;
                    }
                }
            }
        }
        closedir(dir);
    } else {
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

bool removeFile(pPointer file) {
    if (remove(file->getFilePath().c_str()) != EOF) {
        return true;
    } else {
        return false;
    }
}