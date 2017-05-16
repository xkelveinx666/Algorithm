#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include "person.cpp"
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
bool addPerson(pPointers vectorPointer, pPointer *person);
bool findPerson(pPointers vectorPointer, pPointer *pointer);

void clearScreen() {
    system("CLS");
    system("clear");
}

void pause() {
    cout << "输入任意键继续操作" << endl;
    getchar();
    getchar();
}

pPointers initiatePerson() {
    /*循环将Person读出*/
    ifstream readFile;
    readFile.open(FILE_PERSON_NAME, ios::binary | ios::in);
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
    readFile.open(FILE_OCCUPATION_NAME, ios::binary | ios::in);
    oPointer pointer = new Occupation();
    oPointers vectorPointer = new vector<oPointer>();
    while (readFile.read((char *)(pointer), sizeof(*pointer))) {
        vectorPointer->push_back(pointer);
        pointer = new Occupation();
    }
    readFile.close();
    return vectorPointer;
}

//初始化将链表建立
void initateAll() {}

void savePerson(pPointers vectorPointer) {
    /*循环将Person保存*/
    fstream writeFile;
    writeFile.open(FILE_PERSON_NAME,
                   ios::binary | std::ios::out | std::ios::ate);
    vector<pPointer>::iterator begin = vectorPointer->begin();
    vector<pPointer>::iterator end = vectorPointer->end();
    while (begin != end) {
        pPointer pointer = *begin;
        writeFile.write((char *)(pointer), sizeof(*pointer));
        begin++;
    }
    writeFile.close();
}

void saveOccupation(oPointers vectorPointer) {
    /*循环将Person保存*/
    fstream writeFile;
    writeFile.open(FILE_OCCUPATION_NAME,
                   ios::binary | std::ios::out | std::ios::ate);
    vector<oPointer>::iterator begin = vectorPointer->begin();
    vector<oPointer>::iterator end = vectorPointer->end();
    while (begin != end) {
        oPointer pointer = *begin;
        writeFile.write((char *)(pointer), sizeof(*pointer));
        begin++;
    }
    writeFile.close();
}

int getUsefulIndexInpPointers(pPointers vectorPointer) {
    int index = 1;
    vector<pPointer>::iterator begin = vectorPointer->begin();
    vector<pPointer>::iterator end = vectorPointer->end();
    while (begin != end) {
        if (index != (*begin)->getID()) {
            break;
        }
        index++;
        begin++;
    }
    return index;
}
int getUsefulIndexInoPointers(oPointers vectorPointer) {
    int index = 1;
    vector<oPointer>::iterator begin = vectorPointer->begin();
    vector<oPointer>::iterator end = vectorPointer->end();
    while (begin != end) {
        if (index != (*begin)->getID()) {
            break;
        }
        index++;
        begin++;
    }
    return index;
}

bool addPerson(pPointers vectorPointer, pPointer *person) {
    pPointer p = new Person();
    oPointer op;
    string name;
    string fatherName;
    string sex;
    int day;
    int month;
    int year;
    p->setID(getUsefulIndexInpPointers(vectorPointer));
    cout << "请输入要添加成员的信息" << endl;
    cout << "姓名" << endl;
    cin >> name;
    p->setName(name);
    cout << "性别(男、女)" << endl;
    cin >> sex;
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
    /*添加职业
    cout << "输入职业名称" << endl;
    cin >> name;
    vector<oPointer>::iterator begin = vectorOPointer->begin();
    vector<oPointer>::iterator end = vectorOPointer->end();
    while (begin != end) {
        if ((*begin)->getOccupationName() == name) {
            op = *begin;
            break;
        }
        begin++;
    }
    if (begin == end) {
        op = new Occupation();
        op->setOccupationName(name);
        cout << op->getOccupationName();
        op->setID(getUsefulIndexInoPointers(vectorOPointer));
        vectorOPointer->push_back(op);
    }
    p->setOccupation(op);
    */
    vectorPointer->push_back(p);
    *person = p;
    return true;
}

void addRelation(pPointers vectorPointer, pPointer *person) {
    int relationIndex;
    cout << "请输入要添加的关系的序号" << endl;
    cout << "1:父亲" << endl;
    cout << "2:母亲" << endl;
    cout << "3:夫妻" << endl;
    cout << "4:兄弟姐妹" << endl;
    cout << "5:孩子" << endl;
    cin >> relationIndex;
    pPointer otherPerson;
    findPerson(vectorPointer, &otherPerson);
    switch (relationIndex) {
        case 1:
            (*person)->addFather(otherPerson);
            break;
        case 2:
            (*person)->addMother(otherPerson);
            break;
        case 3:
            (*person)->addSpouse(otherPerson);
            break;
        case 4:
            (*person)->addSibling(otherPerson);
            break;
        case 5:
            (*person)->addChild(otherPerson);
            break;
    }
    // cout << "依次输入关系输入-1跳过此种关系" << endl;
    // cout << "父亲名称" << endl;
    // pPointer father;
    // do {
    //     if (father != NULL) {
    //         cout << "父亲性别必须为男性" << endl;
    //     }
    //     findPerson(vectorPointer, &father);
    // } while (father->getSex() == MALE);
    // (*person)->setFather(father);
    // if (father->getSpouse() == NULL) {
    //     cout << "母亲名称" << endl;
    //     pPointer mother;
    //     do {
    //         if (mother != NULL) {
    //             cout << "母亲性别必须为女性" << endl;
    //         }
    //         findPerson(vectorPointer, &mother);
    //     } while (mother->getSex() == "女");
    //     (*person)->setMother(mother);
    // } else {
    // }
    // cout << "父亲名称或母亲名称" << endl;
    // pPointer parent;
    // findPerson(vectorPointer, &parent);
}

bool findPerson(pPointers vectorPointer, pPointer *pointer) {
    // 3次机会
    int findIndex = 3;
    cout << "请输入要查找人员姓名" << endl;
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

bool showPersons(pPointers vectorPointer) {
    vector<pPointer>::iterator begin = vectorPointer->begin();
    vector<pPointer>::iterator end = vectorPointer->end();
    if (begin == end) {
        return false;
    }
    cout << "姓名"
         << "     ";
    cout << "性别"
         << "     ";
    cout << "ID"
         << "     ";
    cout << "出生日期"
         << "     ";
    cout << "死亡日期"
         << "     ";
    cout << endl;
    while (begin != end) {
        pPointer person = *begin;
        person->showInfo();
        begin++;
    }
    pause();
    return true;
}

int main(void) {
    pPointers vectorPointer = initiatePerson();
    pPointer person;
    if (vectorPointer->size() == 0) {
        cout << "没有信息记录" << endl;
    } else {
        person = *(vectorPointer->begin());
    }
    int operation;
    do {
        clearScreen();
        switch (operation) {
            case 1:
                showPersons(vectorPointer);
                break;
            case 2:;
                break;
            case 3:
                addPerson(vectorPointer, &person);
                break;
            case 4:
                addRelation(vectorPointer, &person);
                break;
            case 5:;
                break;
            case 6:
                savePerson(vectorPointer);
                break;
            case 7:
                savePerson(vectorPointer);
                return 0;
            case 8:
                return 0;
        }
        clearScreen();
        if (person != NULL) {
            cout << "当前登录人员:" << person->getName() << endl;
            cout << "当前人数:" << vectorPointer->size() << endl;
        }
        cout << "(1)显示所有成员信息" << endl;
        cout << "(2)显示该成员家庭信息" << endl;
        cout << "(3)添加新人员" << endl;
        cout << "(4)添加新关系" << endl;
        cout << "(5)更换登录人员" << endl;
        cout << "(6)保存" << endl;
        cout << "(7)退出" << endl;
        cout << "(8)退出不保存" << endl;
    } while (cin >> operation);
    return 0;
}