#include "command.cpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#define DIR "mydir"
#define CD "mycd"
#define COPY "mycopy"
#define DEL "mydel"
#define PWD "mypwd"
#define HELP "myhelp"
#define EXIT "myexit"
using namespace std;
mfPointer initiate() {
    char currentPathArray[PATH_MAX];
    if (realpath("./", currentPathArray) == NULL) {
        cout << "当前系统环境不支持stdlib的realpath函数,将无法正常运行" << endl;
        return NULL;
    } else {
        string pwd(currentPathArray);
        mfPointer currentPath = new MyFile(pwd);
        return currentPath;
    }
}

int main(void) {
    cout << "输入myhelp显示所有已支持命令" << endl;
    mfPointer currentPath = initiate();
    stPointer currentStatemnt;
    if (currentPath == NULL) {
        return 0;
    }
    while (true) {
        string cmd;
        getline(cin, cmd);
        stPointer currentStatemnt = new Statements(cmd);
        string command = currentStatemnt->getCommand();
        if (command == HELP) {
            myHelp();
        } else if (command == DIR) {
            myDir();
        } else if (command == CD) {
            myCD(currentStatemnt, &currentPath);
        } else if (command == COPY) {
            myCopy(currentStatemnt, &currentPath);
        } else if (command == DEL) {
            // myDel();
        } else if (command == PWD) {
            currentPath->showLocation();
        } else if (command == EXIT) {
            return 0;
        } else {
            cout << "您输入的命令暂不支持" << endl;
            cout << "输入myhelp查看所有已支持的命令" << endl;
        }
    }
    return 0;
}