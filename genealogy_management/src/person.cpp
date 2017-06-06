#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include "calendar.cpp"
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
        if (date.tm_year == 0) {
            cout << "      " << endl;
        } else {
            cout << date.tm_year << "年";
            cout << date.tm_mon << "月";
            cout << date.tm_mday << "日";
        }
    }

    pPointer getFather() { return this->father; }
    pPointer getMother() { return this->mother; }
    pPointer getSpouse() { return this->spouse; }
    pPointer getLeftBrother() { return this->leftBrother; }
    pPointer getRightBrother() { return this->rightBrother; }
    pPointer getChild() { return this->child; }
    int getOID() { return this->oID; }
    int getFID() { return this->fID; }
    int getMID() { return this->mID; }
    int getSID() { return this->sID; }
    int getLID() { return this->lID; }
    int getRID() { return this->rID; }
    int getCID() { return this->cID; }
    void setOID(int newID) { this->oID = newID; }
    void setFID(int newID) { this->fID = newID; }
    void setMID(int newID) { this->mID = newID; }
    void setSID(int newID) { this->sID = newID; }
    void setLID(int newID) { this->lID = newID; }
    void setRID(int newID) { this->rID = newID; }
    void setCID(int newID) { this->cID = newID; }
    void setFather(pPointer father) {
        this->father = father;
        this->setFID(father->getID());
    }
    void setMother(pPointer mother) {
        this->mother = mother;
        this->setMID(mother->getID());
    }
    void setSpouse(pPointer spouse) {
        this->spouse = spouse;
        this->setSID(spouse->getID());
    }
    void setLeftBrother(pPointer leftBrother) {
        this->leftBrother = leftBrother;
        this->setLID(leftBrother->getID());
    }
    void setRightBrother(pPointer rightBrother) {
        this->rightBrother = rightBrother;
        this->setRID(rightBrother->getID());
    }
    void setChild(pPointer child) {
        this->child = child;
        this->setCID(child->getID());
    }

    oPointer getOccupation() { return this->occupation; }
    void setOccupation(oPointer occupation) { this->occupation = occupation; }

    void editSex() {
        string sex;
        cout << "性别(男、女)" << endl;
        cin >> sex;
        if (sex != "男" && sex != "女") {
            cout << "性别未按格式要求输入" << endl;
        } else if (this->getSpouse() != NULL) {
            cout << "已有配偶不能修改性别" << endl;
        } else {
            this->setSex(sex);
        }
    }

    void editBirthDay() {
        int year;
        int month;
        int day;
        cPointer cp = new Calendar();
        cout << "请添加出生日期" << endl;
        while (!(cp->addCalendar())) {
            cout << "必须添加出生日期" << endl;
        }
        year = cp->getYear();
        month = cp->getMonth();
        day = cp->getDay();
        this->setBirthDay(year, month, day);
    }

    void editDeathDay() {
        int year;
        int month;
        int day;
        cPointer cp = new Calendar();
        cout << "请添加死亡日期" << endl;
        if ((cp->addCalendar())) {
            year = cp->getYear();
            month = cp->getMonth();
            day = cp->getDay();
            this->setDeathDay(year, month, day);
        } else {
            cout << "此人健康未死亡" << endl;
        }
    }

    void showPersonInformation() {
        cout << "ID = " << this->getID() << endl;
        cout << "姓名 = " << this->name << endl;
        cout << "性别 = " << this->getSex() << endl;
    }

    void addFather(pPointer father) {
        pPointer firstChild = this->getLeftBrother();
        if (firstChild != NULL) {
            cout << "已有父亲" << endl;
        } else {
            if (father->getSpouse() == NULL) {
                cout << "父亲必须有配偶" << endl;
            }
            if (father->getChild() != NULL && father->getChild() != this) {
                cout << "test" << endl;
                pPointer child = father->getChild();
                while (child->getRightBrother() != NULL) {
                    child = child->getRightBrother();
                }
                child->setRightBrother(this);
                this->setLeftBrother(child);
            } else {
                father->setChild(this);
                this->setFather(father);
            }
        }
    }

    void addMother(pPointer mother) {
        pPointer firstChild = this->getLeftBrother();
        if (firstChild != NULL) {
            cout << "已有母亲" << endl;
        } else {
            if (mother->getSpouse() == NULL) {
                cout << "母亲必须有配偶" << endl;
                return;
            }
            if (mother->getChild() != NULL && mother->getChild() != this) {
                pPointer child = mother->getChild();
                while (child->getRightBrother() != NULL) {
                    child = child->getRightBrother();
                }
                child->setRightBrother(this);
                this->setLeftBrother(child);
            } else {
                mother->setChild(this);
                this->setMother(mother);
            }
        }
    }

    void addSpouse(pPointer spouse) {
        if (this->getSpouse() != NULL) {
            if (this->getSpouse()->getSpouse() != this) {
                cout << "已有配偶" << endl;
            }
        } else {
            if (spouse->getSex() == this->getSex()) {
                cout << "夫妻性别不能相同" << endl;
            } else {
                this->setSpouse(spouse);
                spouse->setSpouse(this);
                cout << "添加配偶关系成功" << endl;
            }
        }
    }

    void addSibling(pPointer newBrother) {
        //不能将已有父母兄弟姐妹关系节点添加防止多个父母亲或重复节点
        if (!parentBrotherIndepent(newBrother)) {
            return;
        }
        pPointer brother = this->getRightBrother();
        while (brother->getRightBrother() != NULL) {
            brother = brother->getRightBrother();
        }
        cout << "添加兄弟或姐妹成功" << endl;
        brother->setRightBrother(newBrother);
        newBrother->setLeftBrother(brother);
    }

    void addChild(pPointer newChild) {
        pPointer child = this->getChild();
        if (this->getSpouse() == NULL) {
            cout << "无配偶不能添加孩子" << endl;
            return;
        }
        if (child == NULL || child == newChild) {
            this->setChild(newChild);
            this->spouse->setChild(newChild);
            pPointer father = this->sex ? this : this->getSpouse();
            newChild->setFather(father);
            newChild->setMother(father->getSpouse());
        } else {
            if (!spouseChildIndepent(newChild)) {
                return;
            }
            while (child->getRightBrother() != NULL) {
                child = child->getRightBrother();
                if (child == newChild) {
                    cout << "不能重复添加" << endl;
                    return;
                }
            }
            child->setRightBrother(newChild);
            newChild->setLeftBrother(child);
        }
        cout << "添加孩子成功" << endl;
    }

    void cleanChild(bool notOnlyRelation) {
        pPointer child = this->getChild();
        if (child != NULL) {
            pPointer preChild = child;
            child->setFather(NULL);
            child->setMother(NULL);
            child->setFID(-1);
            child->setMID(-1);
            while (child->getRightBrother()) {
                child = child->getRightBrother();
                preChild->setRightBrother(NULL);
                preChild->setLeftBrother(NULL);
                preChild->setRID(-1);
                preChild->setLID(-1);
                if (notOnlyRelation) {
                    preChild->cleanChild(notOnlyRelation);
                    preChild->cleanRelation();
                    delete preChild;
                }
                preChild = child;
            }
            this->setChild(NULL);
            this->setCID(-1);
        }
    }

    void cleanBrother(bool notOnlyRelation) {
        cout << "删除兄弟姐妹将会把父母亲也一并删除" << endl;
        pPointer leftBrother = this->getLeftBrother();
        pPointer rightBrother = this->getRightBrother();
        if (leftBrother != NULL || rightBrother != NULL) {
            if (leftBrother == NULL) {
                pPointer father = this->getFather();
                pPointer mother = this->getMother();
                father->setChild(NULL);
                father->setCID(-1);
                father->addChild(rightBrother);
                mother->setChild(NULL);
                mother->setCID(-1);
                mother->addChild(rightBrother);
            } else if (rightBrother == NULL) {
                leftBrother->setRightBrother(NULL);
                leftBrother->setRID(-1);
            } else {
                leftBrother->setRID(rightBrother->getID());
                leftBrother->setRightBrother(rightBrother);
                rightBrother->setLID(leftBrother->getID());
                rightBrother->setLeftBrother(leftBrother);
            }
            this->setLeftBrother(NULL);
            this->setRightBrother(NULL);
            this->setLID(-1);
            this->setRID(-1);
        } else if (this->getFather() != NULL) {
            pPointer father = this->getFather();
            pPointer mother = this->getMother();
            father->cleanChild(notOnlyRelation);
            mother->cleanChild(notOnlyRelation);
        }
        if (notOnlyRelation) {
            this->cleanChild(notOnlyRelation);
            delete this;
        }
    }

    void cleanFather(bool notOnlyRelation) {
        cout << "清除父亲关系同时会清除母亲关系" << endl;
        this->cleanBrother(notOnlyRelation);
    }

    void cleanMother(bool notOnlyRelation) {
        cout << "清除母亲关系同时会清除父亲关系" << endl;
        this->cleanBrother(notOnlyRelation);
    }

    void cleanSpouse(bool notOnlyRelation) {
        pPointer spouse = this->spouse;
        cout << "清理配偶时也会将孩子清除同时会将孩子间的兄弟姐妹删除" << endl;
        if (spouse != NULL) {
            this->cleanChild(notOnlyRelation);
            spouse->setSpouse(NULL);
            spouse->setSID(-1);
            this->setSpouse(NULL);
            this->setSID(-1);
            this->cleanChild(notOnlyRelation);
            spouse->cleanChild(notOnlyRelation);
        }
        return;
    }

    void cleanRelation() {
        cleanRelationForSave();
        this->setCID(-1);
        this->setFID(-1);
        this->setMID(-1);
        this->setSID(-1);
        this->setLID(-1);
        this->setRID(-1);
    }

    void cleanRelationForSave() {
        this->child = NULL;
        this->father = NULL;
        this->mother = NULL;
        this->spouse = NULL;
        this->leftBrother = NULL;
        this->rightBrother = NULL;
        this->occupation = NULL;
    }

    void deletePerson() { this->cleanSpouse(true); }

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
        // cout << this->getFID() << "    ";
        // cout << this->getMID() << "    ";
        // cout << this->getSID() << "    ";
        // cout << this->getCID() << "    ";
        // cout << this->getLID() << "    ";
        // cout << this->getRID() << "    ";
        cout << endl;
    }

    void showFamily() {
        pPointer firstBrother = this;
        while (firstBrother->getLeftBrother() != NULL) {
            firstBrother = firstBrother->getLeftBrother();
        }
        pPointer father = firstBrother->getFather();
        pPointer mother = firstBrother->getMother();
        pPointer spouse = this->getSpouse();
        pPointer child = this->getChild();
        if (father != NULL) {
            cout << "父亲"
                 << "     ";
            father->showInfo();
        }
        if (mother != NULL) {
            cout << "母亲"
                 << "     ";
            mother->showInfo();
        }
        cout << "本人"
             << "     ";
        this->showInfo();
        if (spouse != NULL) {
            cout << "配偶"
                 << "     ";
            spouse->showInfo();
        }
        while (firstBrother->getRightBrother() != NULL) {
            if (firstBrother->getSex() == this->male) {
                cout << "兄弟";
            } else {
                cout << "姐妹";
            }
            cout << "     ";
            firstBrother->showInfo();
            firstBrother = firstBrother->getRightBrother();
        }
        if (child != NULL) {
            do {
                cout << "孩子"
                     << "     ";
                child->showInfo();
                child = child->getRightBrother();
            } while (child != NULL);
        }
    }

   private:
    int id;
    int oID;  //职业编号
    int fID;  //父亲编号
    int mID;  //母亲编号
    int sID;  //配偶编号
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
    bool spouseChildIndepent(pPointer newChild) {
        if ((this->getSpouse() || this->getChild()) &&
            (newChild->getSpouse() || newChild->getChild())) {
            cout << "添加孩子关系双方必须不能都已有孩子关系" << endl;
            return false;
        } else {
            return true;
        }
    }
    bool parentBrotherIndepent(pPointer newBrother) {
        if ((this->getLeftBrother() || this->getRightBrother() ||
             this->getFather() || this->getMother()) &&
            (newBrother->getLeftBrother() || newBrother->getRightBrother() ||
             newBrother->getFather() || newBrother->getMother())) {
            cout << "添加兄弟姐妹关系双方必须不能都已有兄弟姐妹关系" << endl;
            return false;
        } else if (this->getLeftBrother() || this->getRightBrother() ||
                   this->getFather() || this->getMother() ||
                   newBrother->getLeftBrother() ||
                   newBrother->getRightBrother() || newBrother->getFather() ||
                   newBrother->getMother()) {
            return true;
        } else {
            cout << "添加兄弟姐妹关系双方必须有一方有父母" << endl;
            return false;
        }
    }
};