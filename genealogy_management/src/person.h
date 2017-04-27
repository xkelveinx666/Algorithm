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

    pPointer getFather() { return this->father; }
    pPointer getMother() { return this->mother; }
    pPointer getSpouse() { return this->spouse; }
    pPointer getLeftChild() { return this->leftChild; }
    pPointer getRightChild() { return this->rightChild; }
    void setFather(pPointer father) { this->father = father; }
    void setMother(pPointer mother) { this->mother = mother; }
    void setSpouse(pPointer spouse) { this->spouse = spouse; }
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
    pPointer mother;
    pPointer spouse;
    pPointer leftChild;
    pPointer rightChild;
    tm birthDay;
    tm deathDay;
    const string male = "男";
};