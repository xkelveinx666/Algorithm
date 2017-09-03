#include <iostream>
#include <string>
#include <sys/stat.h>
using namespace std;

#define pPointer Path *
#define sPointer string *

class Path {
  public:
    Path(string pwd) {
        this->fullPath = pwd;
        if (isFolder()) {
            if (fullPath[fullPath.length() - 1] != '/') {
                fullPath.append("/");
            }
        }
        transferLocatoin();
    }
    void nextFolder(string folder) {
        this->fullPath.append("/");
        this->fullPath.append(folder);
        this->fullPath.append("/");
        transferLocatoin();
    }
    void preFolder() {
        this->fullPath = this->location;
        transferLocatoin();
    }
    string getLocation() { return this->location; }
    string getLastName() { return this->lastName; }
    string getFullPath() { return this->fullPath; }
    void setLocation(string location) { this->location = location; }
    void setLastName(string lastName) { this->lastName = lastName; }
    void showLocation() {
        cout << "当前路径为" << location << lastName << endl;
    }
    void showLastName() { cout << "~" << this->lastName << ":"; }
    bool isFolder() {
        struct stat st;
        stat(fullPath.c_str(), &st);
        if (S_ISDIR(st.st_mode)) {
            return 1;
        } else {
            return 0;
        }
    }

  private:
    void transferLocatoin() {
        size_t slash = fullPath.find_last_of('/');
        slash = fullPath.find_last_of('/', slash - 1);
        this->location = fullPath.substr(0, slash);
        this->lastName = fullPath.substr(slash, fullPath.length() - slash);
    }
    string location;
    string lastName;
    string fullPath;
};