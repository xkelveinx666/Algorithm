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
                this->backupOriginalPath = *begin;
                this->originalPath = *begin;
                break;
            case 2:
                this->backupTargetPath = *begin;
                this->targetPath = *begin;
                break;
            }
        }
    }
    void changToAbsolute(mfPointer currentPath) {
        size_t bopPoint = 0;
        size_t btpPoint = 0;
        int cpLength = currentPath->getLocation().length();
        //先判断是否有放回上一级的字符
        size_t clPoint = cpLength;
        bopPoint = this->backupOriginalPath.find("../", bopPoint);
        if ((int)bopPoint >= 0) {
            int backBopPoint = 0;
            while ((int)bopPoint >= 0) {
                backBopPoint = bopPoint;
                bopPoint += 3;
                clPoint =
                    currentPath->getLocation().find_last_of("/", clPoint - 1);
                bopPoint = this->backupOriginalPath.find("../", bopPoint);
            }
            if (clPoint != cpLength) {
                clPoint =
                    currentPath->getLocation().find_last_of("/", clPoint - 1);
                this->originalPath =
                    currentPath->getLocation().substr(0, clPoint + 1);
                bopPoint = backBopPoint + 3;
                this->originalPath.append(this->backupOriginalPath.substr(
                    bopPoint, this->backupOriginalPath.length() - bopPoint));
            }
        } else {
            //判断是否含有当前文件夹的字符
            bopPoint = this->backupOriginalPath.find("./");
            if (((int)(bopPoint) >= 0)) {
                bopPoint = this->backupOriginalPath.find_first_of("./");
                this->originalPath = currentPath->getLocation();
                this->originalPath.append(currentPath->getFileName());
                this->originalPath.append(this->backupOriginalPath.substr(
                    bopPoint + 2,
                    this->backupOriginalPath.length() - bopPoint));
            }
        }
        btpPoint = this->backupTargetPath.find("../", btpPoint);
        clPoint = cpLength;
        if ((int)btpPoint >= 0) {
            int backBtpPoint = 0;
            while ((int)btpPoint >= 0) {
                backBtpPoint = btpPoint;
                btpPoint += 3;
                clPoint =
                    currentPath->getLocation().find_last_of("/", clPoint - 1);
                btpPoint = this->backupTargetPath.find("../", btpPoint);
            }
            if (clPoint != cpLength) {
                clPoint =
                    currentPath->getLocation().find_last_of("/", clPoint - 1);
                this->targetPath =
                    currentPath->getLocation().substr(0, clPoint + 1);
                btpPoint = backBtpPoint + 3;
                this->targetPath.append(this->backupTargetPath.substr(
                    btpPoint, this->backupTargetPath.length() - btpPoint));
            }
        } else {
            btpPoint = this->backupTargetPath.find("./");
            if (((int)(btpPoint) >= 0)) {
                btpPoint = this->backupTargetPath.find_first_of("./");
                this->targetPath = currentPath->getLocation();
                this->targetPath.append(currentPath->getFileName());
                this->targetPath.append(this->backupTargetPath.substr(
                    btpPoint + 2, this->backupTargetPath.length() - btpPoint));
            }
        }
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
    bool exists() {
        if (!(this->originalPath.empty()) && !isPath(this->originalPath)) {
            cout << this->originalPath << "该路径不合法或不存在" << endl;
            return false;
        } else if (!(this->targetPath.empty()) && !isPath(this->targetPath)) {
            cout << this->targetPath << "该路径不合法或不存在" << endl;
            return false;
        } else {
            return true;
        }
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
    bool isPath(string path) {
        if (ifstream(path)) {
            return true;
        } else {
            return false;
        }
    }
    string backupTargetPath;
    string backupOriginalPath;
    string command;
    string targetPath;
    string originalPath;
};