#include "general.cpp"
#include "myfile.cpp"
#include "statements.cpp"
#include <iostream>
#define DIR "mydir"
#define CD "mycd"
#define COPY "mycopy"
#define DEL "mydel"
#define PWD "mypwd"
#define HELP "myhelp"
#define EXIT "myexit"
#define mfPointer MyFile *

using namespace std;

void myHelp() {
    clearScreen();
    cout << DIR << "列出目录及文件" << endl;
    cout << CD << "改变当前文件夹" << endl;
    cout << COPY << "复制文件" << endl;
    cout << DEL << "删除目录" << endl;
    cout << PWD << "显示当前目录名" << endl;
    cout << EXIT << "退出系统" << endl;
}

void myDir() { cout << "mydir" << endl; }

void myCD(stPointer statements, mfPointer *currentPath) {
    if ((statements->getCommand() != CD ||
         !statements->getTargetPath().empty()) &&
        (statements->getOriginalPath().empty())) {
        cout << "该命令格式有误,非" << CD << "命令" << endl;
        return;
    }
    *currentPath = new MyFile(statements->getOriginalPath());
}

void myCopy() { cout << "mycopy" << endl; }
// void myDel() {
//     mfPointer mf = new MyFile("test/123");
//     cout << mf->getLocation() << endl;
//     cout << mf->getFileName() << endl;
//     cout << "mydel" << endl;
// }

// void myPwd() {
//     char current_absolute_path[PATH_MAX];
//     if (realpath("./", current_absolute_path) == NULL) {
//         cout << "当前系统环境不支持stdlib的realpath函数" << endl;
//     } else {
//         cout << "当前路径为" << current_absolute_path << endl;
//     }
// }