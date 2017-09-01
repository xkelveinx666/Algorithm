#include <iostream>
#include "general.cpp"

using namespace std;

void myHelp()
{
    clearScreen();
    cout << "mydir 列出目录及文件" << endl;
    cout << "mycd 改变当前文件夹" << endl;
    cout << "mycopy 复制文件" << endl;
    cout << "mydel 删除目录" << endl;
    cout << "mypwd 显示当前目录名" << endl;
}

void myDir() {
    cout<<"mydir"<<endl;
}

void myCD() {
    cout<<"mycd"<<endl;
}

void myCopy() {
    cout<<"mycopy"<<endl;
}

void myDel() {
    cout<<"mydel"<<endl;
}

void myPwd() {
    cout<<"mypwd"<<endl;
}