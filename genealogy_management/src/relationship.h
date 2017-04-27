#include <iostream>
#include "person.h"
using namespace std;
#define FEMALE "女"
#define MALE "男"

/*查询配偶关系*/
bool judgeSpouse(pPointer father, pPointer mother) {
    if (father->getSpouse() == mother && mother->getSpouse() == father) {
        return 1;
    } else if (father->getSex() == mother->getSex()) {
        return 0;
    } else {
        return -1;
    }
}

/*查询亲子关系*/
bool judgeParentChild(pPointer parent, pPointer child) {
    if (parent->getRightChild() == NULL || child->getFather() == NULL) {
        return 0;
    } else {
        pPointer brother = parent->getRightChild();
        while (brother != NULL && brother != child) {
            brother = brother->getLeftChild();
        }
        if (brother == NULL) {
            return -1;
        } else {
            return 1;
        }
    }
}

/*查询兄弟关系*/

bool judgeBrother(pPointer brother, pPointer person) {
    if (brother->getFather() != person->getFather()) {
        return -1;
    } else {
        pPointer brotherTemp = brother;
        while (brotherTemp != person) {
            brotherTemp = brotherTemp->getLeftChild();
        }
        if (brotherTemp != person) {
            return 0;
        } else {
            return 1;
        }
    }
}

/*添加亲子关系*/
void addParentChild(pPointer parent, pPointer child) {
    if (parent->getSpouse() == NULL) {
        cout << "家长没有相对应的配偶，请先为其添加配偶或重新输入家长姓名"
             << endl;
        return;
    } else if (parent->getLeftChild() == NULL) {
        parent->setLeftChild(child);
        parent->getSpouse()->setLeftChild(child);
    } else {
        pPointer brother = parent->getLeftChild();
        while (brother->getRightChild() != NULL) {
            brother = brother->getRightChild();
        }
        brother->setRightChild(child);
    }
    if (parent->getSex() == MALE) {
        child->setFather(parent);
        child->setMother(parent->getSpouse());
    } else {
        child->setMother(parent);
        child->setFather(parent->getSpouse());
    }
    cout << "添加成功" << endl;
}

/*添加配偶关系*/
void addSpouse(pPointer male, pPointer female) {
    if (male->getSex() == female->getSex()) {
        cout << "配偶关系性别不能相同" << endl;
    } else if (male->getSpouse() != NULL || female->getSpouse() != NULL) {
        cout << "已有配偶关系不能多次添加" << endl;
    } else {
        male->setSpouse(female);
        female->setSpouse(male);
        cout << "添加成功" << endl;
    }
}

/*添加兄弟关系*/
void addBrother(pPointer brother, pPointer person) {
    if (brother->getFather() != NULL && person->getFather() != NULL) {
        cout << "两者具有不同的父子关系，请先修改" << endl;
    } else {
        while (brother->getLeftChild() != NULL) {
            brother = brother->getLeftChild();
        }
        brother->setLeftChild(person);
        cout << "添加成功" << endl;
    }
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