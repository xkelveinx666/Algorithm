#include "command.cpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#define MY_DIR "mydir"
#define MY_CD "mycd"
#define MY_COPY "mycopy"
#define MY_DEL "mydel"
#define MY_PWD "mypwd"
#define MY_HELP "myhelp"
#define MY_EXIT "myexit"
using namespace std;
pPointer initiate() {
    char currentPathArray[PATH_MAX];
    if (realpath("./", currentPathArray) == NULL) {
        cout << "当前系统环境不支持stdlib的realpath函数,将无法正常运行" << endl;
        return NULL;
    } else {
        string pwd(currentPathArray);
        pwd.append("/");
        pPointer currentPath = new Path(pwd);
        return currentPath;
    }
}

int main(void) {
    cout << "输入myhelp显示所有已支持命令" << endl;
    pPointer currentPath = initiate();
    stPointer currentStatemnt;
    if (currentPath == NULL) {
        return 0;
    }
    while (true) {
        string cmd;
        currentPath->showLastName();
        getline(cin, cmd);
        stPointer currentStatemnt = new Statements(cmd);
        currentStatemnt->changToAbsolute(currentPath);
        string command = currentStatemnt->getCommand();
        if (command == MY_HELP) {
            myHelp();
        } else if (command == MY_DIR) {
            myDir(currentStatemnt);
        } else if (command == MY_CD) {
            myCD(currentStatemnt, &currentPath);
        } else if (command == MY_COPY) {
            myCopy(currentStatemnt);
        } else if (command == MY_DEL) {
            myDel(currentStatemnt);
        } else if (command == MY_PWD) {
            currentPath->showLocation();
        } else if (command == MY_EXIT) {
            return 0;
        } else {
            cout << "您输入的命令暂不支持" << endl;
            cout << "输入myhelp查看所有已支持的命令" << endl;
        }
    }
    return 0;
}