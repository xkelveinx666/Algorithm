#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include "person.h"
using namespace std;
#define FILE_PERSON_NAME "../test/person.dat"
#define FILE_OCCUPATION_NAME "../test/occupation.dat"
#define pPointers vector<pPointer> *
#define oPointers vector<oPointer> *
#define FEMALE "女"
#define MALE "男"

pPointers initiatePerson();
oPointers initiateOccupation();
void savePerson(pPointers vectorPointer);
void saveOccupation(oPointers vectorPointer);
int getUsefulIndex(pPointers vectorPointer);
bool addPerson(pPointers vectorPointer);
bool findPerson(pPointers vectorPointer, pPointer *pointer);

pPointers initiatePerson() {
    /*循环将Person读出*/
    ifstream readFile;
    readFile.open(FILE_PERSON_NAME, ios::binary);
    pPointer pointer = new Person();
    pPointers vectorPointer = new vector<pPointer>();
    while (readFile.read((char *)(pointer), sizeof(*pointer))) {
        vectorPointer->push_back(pointer);
        pointer->showPersonInformation();
        pointer = new Person();
    }
    readFile.close();
    return vectorPointer;
}

oPointers initiateOccupation() {
    /*循环将Occupation读出*/
    ifstream readFile;
    readFile.open(FILE_PERSON_NAME, ios::binary);
    oPointer pointer = new Occupation();
    oPointers vectorPointer = new vector<oPointer>();
    while (readFile.read((char *)(pointer), sizeof(*pointer))) {
        vectorPointer->push_back(pointer);
        pointer = new Occupation();
    }
    readFile.close();
    return vectorPointer;
}

void savePerson(pPointers vectorPointer) {
    /*循环将Person保存*/
    ofstream writeFile;
    writeFile.open(FILE_PERSON_NAME, ios::binary);
    vector<pPointer> pPointerVector = *vectorPointer;
    vector<pPointer>::iterator begin = pPointerVector.begin();
    vector<pPointer>::iterator end = pPointerVector.end();
    while (begin != end) {
        pPointer pointer = *begin;
        writeFile.write((char *)(pointer), sizeof(*pointer));
        begin++;
    }
    writeFile.close();
}

void saveOccupation(oPointers vectorPointer) {
    /*循环将Person保存*/
    ofstream writeFile;
    writeFile.open(FILE_PERSON_NAME, ios::binary);
    vector<oPointer> pPointerVector = *vectorPointer;
    vector<oPointer>::iterator begin = pPointerVector.begin();
    vector<oPointer>::iterator end = pPointerVector.end();
    while (begin != end) {
        oPointer pointer = *begin;
        writeFile.write((char *)(pointer), sizeof(*pointer));
        begin++;
    }
    writeFile.close();
}

int getUsefulIndex(pPointers vectorPointer) {
    int index = 1;
    vector<pPointer>::iterator begin = vectorPointer->begin();
    vector<pPointer>::iterator end = vectorPointer->end();
    while (begin != end) {
        if (index == (*begin)->getID()) {
            break;
        }
        index++;
        begin++;
    }
    return index;
}

bool addPerson(pPointers vectorPointer, pPointer *person) {
    pPointer p = new Person();
    string name;
    string fatherName;
    string sex;
    int day;
    int month;
    int year;
    p->setID(getUsefulIndex(vectorPointer));
    cout << "请输入要添加成员的信息" << endl;
    cout << "姓名" << endl;
    cin >> name;
    p->setName(name);
    cout << "性别(男、女)" << endl;
    cin >> sex;
    sex = "男";
    if (sex != "男" && sex != "女") {
        cout << "性别未按格式要求输入" << endl;
        return false;
    }
    p->setSex(sex);
    cout << "出生年月日(以空格分隔)" << endl;
    cin >> year >> month >> day;
    p->setBirthDay(year, month, day);
    cout << "死亡年月日(以空格分隔)" << endl;
    cin >> year >> month >> day;
    p->setDeathDay(year, month, day);
    vectorPointer->push_back(p);
    *person = p;
    return true;
}

void addRelation(pPointers vectorPointer, pPointer *person) {
    cout << "依次输入关系输入-1跳过此种关系" << endl;
    cout << "父亲名称" << endl;
    pPointer father;
    do {
        if (father != NULL) {
            cout << "父亲性别必须为男性" << endl;
        }
        findPerson(vectorPointer, &father);
    } while (father->getSex() == MALE);
    (*person)->setFather(father);
    if (father->getLeftChild() == NULL) {
        cout << "母亲名称" << endl;
        pPointer mother;
        do {
            if (mother != NULL) {
                cout << "母亲性别必须为女性" << endl;
            }
            findPerson(vectorPointer, &mother);
        } while (mother->getSex() == "女");
        (*person)->setMother(mother);
    } else {
    }
    cout << "父亲名称或母亲名称" << endl;
    pPointer parent;
    findPerson(vectorPointer, &parent);
}

bool findPerson(pPointers vectorPointer, pPointer *pointer) {
    int findIndex = 3;
    while (findIndex-- > 0) {
        string personName;
        cin >> personName;
        vector<pPointer>::iterator begin = vectorPointer->begin();
        vector<pPointer>::iterator end = vectorPointer->end();
        while (begin != end) {
            if (personName == (*begin)->getName()) {
                break;
            }
            begin++;
        }
        if (begin == end) {
            cout << "未在家谱中找到含有此名字的人" << endl;
        } else {
            *pointer = *begin;
            return true;
        }
        cout << "请重新输入" << endl;
    }
    cout << "错误次数太多，请检查是否未存入此人" << endl;
    return false;
}

int main(void) {
    pPointers vectorPointer = initiatePerson();
    cout << "人数 = " << vectorPointer->size() << endl;
    addPerson(vectorPointer);
    cout << "人数 = " << vectorPointer->size() << endl;
    savePerson(vectorPointer);
    return 0;
}