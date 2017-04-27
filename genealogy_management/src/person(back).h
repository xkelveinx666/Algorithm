#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include "occupation.h"
#define pPointer Person*

using namespace std;
class Person {
   public:
    string getName() { return this->name; }
    set<pPointer> getParents() { return this->parents; }
    set<pPointer> getChildren() { return this->children; }
    int getID() { return this->id; }
    void setID(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setParents(set<pPointer> parents) { this->parents = parents; }
    void addParents(pPointer parent) {
        if (this->parents.size() > 2) {
            cout << "父母数量不能超过两个!" << endl;
            return;
        } else if (this->parents.size() == 1) {
            pPointer oldParent = *(this->parents.begin());
            if (oldParent->getSex() == parent->getSex()) {
                cout << "父母性别不能相同!" << endl;
                return;
            }
        }
        (this->children).insert(parent);
    }
    void setChildren(set<pPointer> children) { this->children = children; }
    void addChildren(pPointer child) { (this->children).insert(child); }
    void deleteChildren(pPointer child) { (this->children).erase(child); }
    void showParents() {
        set<pPointer>::iterator begin = this->parents.begin();
        set<pPointer>::iterator end = this->parents.end();
        while (begin != end) {
            cout << *begin << endl;
        }
    }
    void showChildren() {
        set<pPointer>::iterator begin = this->children.begin();
        set<pPointer>::iterator end = this->children.end();
        while (begin != end) {
            cout << *begin << endl;
        }
    }
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

    pPointer getFather() { return this->father; }
    pPointer getLeftChild() { return this->leftChild; }
    pPointer getRightChild() { return this->rightChild; }
    void setFather(pPointer father) { this->father = father; }
    void setLeftChild(pPointer leftChild) { this->leftChild = leftChild; }
    void setRightChild(pPointer rightChild) { this->rightChild = rightChild; }

    oPointer getOccupation() { return this->occupation; }
    void setOccupation(oPointer occupation) { this->occupation = occupation; }

    void showPersonInformation() {
        cout << "ID = " << this->getID() << endl;
        cout << "姓名 = " << this->name << endl;
        cout << "性别 = " << this->getSex() << endl;
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
    string name;
    oPointer occupation;
    bool sex;
    pPointer father;
    pPointer leftChild;
    pPointer rightChild;
    set<pPointer> parents;
    set<pPointer> children;
    tm birthDay;
    tm deathDay;
    const string male = "男";
};