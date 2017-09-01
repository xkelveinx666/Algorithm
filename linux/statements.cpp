#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define stPointer Statements *
#define vcPointer vector<string> *

class Statements {
  public:
    Statements(string stm) {
        vcPointer vec = split(trim(stm), ' ');
        vector<string>::iterator begin = vec->begin();
        vector<string>::iterator end = vec->end();
        if (vec->size() == 0) {
            return;
        }
        for (int index = 0; begin != end; begin++, index++) {
            switch (index) {
            case 0:
                this->command = *begin;
                break;
            case 1:
                if (!judgePath(*begin)) {
                    return;
                }
                this->backupOriginalPath = *begin;
                this->originalPath = *begin;
                break;
            case 2:
                if (!judgePath(*begin)) {
                    this->backupOriginalPath = "";
                    this->originalPath = "";
                    return;
                }
                this->backupTargetPath = *begin;
                this->targetPath = *begin;
                break;
            }
        }
    }
    string changToAbsolute(mfPointer currentPath) {
        size_t bopPoint = this->backupOriginalPath.find_first_of("./");
        size_t btpPoint = this->backupTargetPath.find_first_of("./");
    }
    string changeToRelative(mfPointer currentPath) {}
    string getCommand() { return this->command; }
    string getTargetPath() { return this->targetPath; }
    string getOriginalPath() { return this->originalPath; }
    void setCommand(string command) { this->command = command; }
    void setTargetPath(string targetPath) { this->targetPath = targetPath; }
    void setOriginalPath(string originalPath) {
        this->originalPath = originalPath;
    }

  private:
    string trim(string stm) {
        size_t start = stm.find_first_not_of(" ");
        size_t end = stm.find_last_not_of(" ");
        return stm.substr(start, end + 1);
    }
    vcPointer split(string stm, char pattern) {
        size_t startIndex = 0;
        size_t endIndex = 0;
        vcPointer vec = new vector<string>();
        while ((int)(startIndex) <= stm.length() && (int)(startIndex) != -1) {
            endIndex = stm.find_first_of(pattern, startIndex);
            if ((int)(endIndex) == -1) {
                endIndex = stm.length();
            }
            vec->push_back(stm.substr(startIndex, endIndex));
            startIndex = stm.find_first_not_of(pattern, endIndex);
        }
        return vec;
    }
    bool judgePath(string path) {
        if (ifstream(path)) {
            return true;
        } else {
            cout << path << "路径不存在" << endl;
            return false;
        }
    }
    string backupTargetPath;
    string backupOriginalPath;
    string command;
    string targetPath;
    string originalPath;
};