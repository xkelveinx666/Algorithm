#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#define DIR "mydir"
#define CD "mycd"
#define COPY "mycopy"
#define DEL "mydel"
#define PWD "mypwd"
#define HELP "myhelp"
#include "command.cpp"
using namespace std;

int main(void)
{
    cout << "输入myhelp显示所有已支持命令" << endl;
    while (true)
    {
        string command;
        cin>>command;
        getchar(); //处理回车
        if(command == HELP){
           myHelp(); 
        } else if(command == DIR) {
            myDir();
        } else if(command == CD) {
            myCD();
        } else if(command == COPY) {
            myCopy();
        } else if(command == DEL) {
            myDel();
        } else if(command == PWD) {
            myPwd();
        } else {
            cout<<"您输入的命令暂不支持"<<endl;
            cout<<"输入myhelp查看所有已支持的命令"<<endl;
        }
    }
    return 0;
}