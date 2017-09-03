#include <iostream>
#include <string>
using namespace std;

#define mfPointer MyFile *
#define sPointer string *

class MyFile {
  public:
    MyFile(string pwd) {
        size_t slash = pwd.find_last_of('/');
        slash = pwd.find_last_of('/', slash - 1);
        this->location = pwd.substr(0, slash);
        this->fileName = pwd.substr(slash, pwd.length() - slash);
        this->fullPath = pwd;
    }
    string getLocation() { return this->location; }
    string getFileName() { return this->fileName; }
    string getFullPath() { return this->fullPath; }
    void setLocation(string loc) { this->location = loc; }
    void setFileName(string fName) { this->fileName = fName; }
    void showLocation() {
        cout << "当前路径为" << location << fileName << endl;
    }
    void showCurrentFileName() { cout << "~" << this->fileName << ":"; }

  private:
    string location;
    string fileName;
    string fullPath;
};