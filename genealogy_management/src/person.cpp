#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include "occupation.cpp"
#define pPointer Person*

using namespace std;
class Person {
   public:
    string getName() { return this->name; }
    int getID() { return this->id; }
    void setID(int id) { this->id = id; }
    void setName(string name) { this->name = name; }

    void setSex(string sex) {
        if (sex == male) {
            this->sex = true;
        } else {
            this->sex = false;
        }
    }
    string getSex() {
        if (this->sex) {
            return "男";
        } else {
            return "女";
        }
    }
    void setBirthDay(int year, int mon, int day) {
        tm date;
        date.tm_year = year;
        date.tm_mon = mon;
        date.tm_mday = day;
        this->birthDay = date;
    }
    void setDeathDay(int year, int mon, int day) {
        tm date;
        date.tm_year = year;
        date.tm_mon = mon;
        date.tm_mday = day;
        this->deathDay = date;
    }
    tm getBirthDay() { return this->birthDay; }
    tm getDeathDay() { return this->deathDay; }

    void showBirthDay() {
        tm date = this->birthDay;
        cout << date.tm_year << "年";
        cout << date.tm_mon << "月";
        cout << date.tm_mday << "日";
    }

    void showDeathDay() {
        tm date = this->deathDay;
        cout << date.tm_year << "年";
        cout << date.tm_mon << "月";
        cout << date.tm_mday << "日";
    }

    pPointer getFather() { return this->father; }
    pPointer getMother() { return this->mother; }
    pPointer getSpouse() { return this->spouse; }
    pPointer getLeftBrother() { return this->leftBrother; }
    pPointer getRightBrother() { return this->rightBrother; }
    pPointer getChild() { return this->child; }
    void setFather(pPointer father) { this->father = father; }
    void setMother(pPointer mother) { this->mother = mother; }
    void setSpouse(pPointer spouse) { this->spouse = spouse; }
    void setLeftBrother(pPointer leftBrother) {
        this->leftBrother = leftBrother;
    }
    void setRightBrother(pPointer rightBrother) {
        this->rightBrother = rightBrother;
    }
    void setChild(pPointer child) { this->child = child; }

    oPointer getOccupation() { return this->occupation; }
    void setOccupation(oPointer occupation) { this->occupation = occupation; }

    void showPersonInformation() {
        cout << "ID = " << this->getID() << endl;
        cout << "姓名 = " << this->name << endl;
        cout << "性别 = " << this->getSex() << endl;
    }

    void addFather(pPointer father) {
        pPointer originalFather = this->getFather();
        if (originalFather != NULL) {
            cout << "已有父亲" << endl;
        } else {
            this->setFather(father);
            pPointer child = father->getChild();
            while (child != NULL) {
                child = child->getRightBrother();
            }
            child = this;
        }
    }

    void addMother(pPointer mother) {
        pPointer originalMother = this->getMother();
        if (originalMother != NULL) {
            cout << "已有母亲" << endl;
        } else {
            this->setMother(mother);
            pPointer child = mother->getChild();
            while (child != NULL) {
                child = child->getRightBrother();
            }
            child = this;
        }
    }

    void addSpouse(pPointer spouse) {
        if (this->getSpouse() != NULL) {
            cout << "已有配偶" << endl;
        } else {
            if (spouse->getSex() == this->getSex()) {
                cout << "夫妻性别不能相同" << endl;
            } else {
                this->setSpouse(spouse);
                spouse->setSpouse(this);
            }
        }
    }

    void addSibling(pPointer newBrother) {
        pPointer brother = this->getRightBrother();
        while (brother != NULL) {
            brother = brother->getRightBrother();
        }
        cout << "添加兄弟或姐妹成功" << endl;
        brother->setRightBrother(newBrother);
        newBrother->setLeftBrother(brother);
    }

    void addChild(pPointer newChild) {
        pPointer child = this->getChild();
        while (child != NULL) {
            child = child->getRightBrother();
        }
        cout << "添加孩子成功" << endl;
        child->setRightBrother(newChild);
    }

    void showInfo() {
        cout << this->getName() << "     ";
        cout << this->getSex() << "     ";
        cout << this->getID() << "     ";
        this->showBirthDay();
        cout << "     ";
        this->showDeathDay();
        cout << "     ";
        oPointer op = this->getOccupation();
        if (op != NULL) {
            cout << op->getOccupationName() << "     ";
        }
        cout << endl;
    }

    // void changeBinaryTreeToMap() {
    //     /*从二叉树中找出兄弟链中的第一个兄弟*/
    //     pPointer father = this->father;
    //     pPointer lChild = father->leftChild;
    //     while (father != lChild) {
    //         father = father->father;
    //         lChild = father->leftChild;
    //     }
    //     pPointer mother = father->rightChild;
    //     /*将找出的父母,孩子插入set中*/
    //     this->parents.clear();
    //     addParents(father);
    //     addParents(mother);
    //     pPointer child = father->rightChild->rightChild;
    //     this->children.clear();
    //     while (child != NULL) {
    //         addChildren(child);
    //         child = child->rightChild;
    //     }
    // }

    // void changeMapToBinaryTree() {}

   private:
    int id;
    int oID;  //职业编号
    int fID;  //父亲编号
    int mID;  //母亲编号
    int lID;  //前兄弟编号
    int rID;  //后兄弟编号
    int cID;  //孩子编号
    string name;
    oPointer occupation;
    bool sex;
    pPointer father;
    pPointer mother;
    pPointer spouse;
    pPointer rightBrother;  //后一个兄弟
    pPointer leftBrother;   //前一个兄弟
    pPointer child;         //孩子
    tm birthDay;
    tm deathDay;
    const string male = "男";
};