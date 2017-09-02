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
    void changToAbsolute(mfPointer currentPath) {
        size_t bopPoint = this->backupOriginalPath.find("./");
        size_t btpPoint = this->backupTargetPath.find("./");
        if (((int)(bopPoint) >= 0)) {
            bopPoint = this->backupOriginalPath.find_first_of("./");
            this->originalPath = currentPath->getLocation();
            this->originalPath.append(this->backupOriginalPath.substr(
                bopPoint + 2, this->backupOriginalPath.length() - bopPoint));
        }
        if (((int)(btpPoint) >= 0)) {
            btpPoint = this->backupTargetPath.find_first_of("./");
            this->targetPath = currentPath->getLocation();
            this->targetPath.append(this->backupTargetPath.substr(
                btpPoint + 2, this->backupTargetPath.length() - btpPoint));
        }
        // int cpLength = currentPath->getLocation().length();
        // bopPoint = 0;
        // size_t clPoint = cpLength;
        // while (bopPoint = this->backupOriginalPath.find("../", bopPoint) + 3
        // &&
        //                   bopPoint >= 0) {
        //     string currentLocation = currentPath->getLocation();
        //     clPoint = currentLocation.find_first_not_of("/", clPoint - 1);
        // }
        // if (clPoint != cpLength) {
        //     this->originalPath = currentPath->getLocation().substr(0,
        //     clPoint);
        //     this->originalPath.append(this->backupOriginalPath.substr(
        //         bopPoint, this->backupOriginalPath.length() - bopPoint));
        // }
    }
    void changeToRelative(mfPointer currentPath) {}
    string getCommand() { return this->command; }
    string getTargetPath() { return this->targetPath; }
    string getOriginalPath() { return this->originalPath; }
    void setCommand(string command) { this->command = command; }
    void setTargetPath(string targetPath) { this->targetPath = targetPath; }
    void setOriginalPath(string originalPath) {
        this->originalPath = originalPath;
    }
    void showStatements() {
        cout << "command = " << this->command << endl;
        cout << "backupOriginalPath = " << this->backupOriginalPath << endl;
        cout << "backupTargetPath = " << this->backupTargetPath << endl;
        cout << "originalPath = " << this->originalPath << endl;
        cout << "targetPath = " << this->targetPath << endl;
    }

  private:
    string trim(string stm) {
        size_t start = stm.find_first_not_of(' ');
        size_t end = stm.find_last_not_of(' ');
        return stm.substr(start, end - start + 1);
    }
    vcPointer split(string stm, char pattern) {
        size_t startIndex = 0;
        size_t endIndex = 0;
        vcPointer vec = new vector<string>();
        while ((int)(startIndex) <= stm.length() && (int)(startIndex) != -1) {
            endIndex = stm.find_first_of(pattern, startIndex);
            if ((int)(endIndex) <= 0) {
                endIndex = stm.length();
            }
            vec->push_back(stm.substr(startIndex, endIndex - startIndex));
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