#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include "calendar.cpp"
#define pPointer Person *

using namespace std;
class Person {
   public:
    string getName() { return this->name; }
    int getID() { return this->id; }
    void setID(int id) { this->id = id; }
    void setName(string name) { this->name = name; }

    void setSex(string sex) {
        if (this->getSID() != -1 && this->getSpouse() != NULL) {
            cout << "已有配偶关系，不能修改性别" << endl;
            return;
        }
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

    string getAllBirthDay() {
        tm date = this->birthDay;
        cout << left;
        cout << setw(10);
        string birthDay = " ";
        birthDay.append(to_string(date.tm_year));
        birthDay.append("年");
        birthDay.append(to_string(date.tm_mon));
        birthDay.append("月");
        birthDay.append(to_string(date.tm_mday));
        birthDay.append("日");
        return birthDay;
    }

    string getAllDeathDay() {
        tm date = this->deathDay;
        string deathDay;
        if (date.tm_year == 0) {
            deathDay = " ";
        } else {
            deathDay = " ";
            deathDay.append(to_string(date.tm_year));
            deathDay.append("年");
            deathDay.append(to_string(date.tm_mon));
            deathDay.append("月");
            deathDay.append(to_string(date.tm_mday));
            deathDay.append("日");
        }
        return deathDay;
    }

    pPointer getFather() { return this->father; }
    pPointer getMother() { return this->mother; }
    pPointer getSpouse() { return this->spouse; }
    pPointer getLeftBrother() { return this->leftBrother; }
    pPointer getRightBrother() { return this->rightBrother; }
    pPointer getChild() { return this->child; }
    int getFID() { return this->fID; }
    int getMID() { return this->mID; }
    int getSID() { return this->sID; }
    int getLID() { return this->lID; }
    int getRID() { return this->rID; }
    int getCID() { return this->cID; }
    bool getHasDelete() { return this->hasDelete; }
    void setHasDelete(bool deleteJudge) { this->hasDelete = deleteJudge; }
    void setFID(int newID) { this->fID = newID; }
    void setMID(int newID) { this->mID = newID; }
    void setSID(int newID) { this->sID = newID; }
    void setLID(int newID) { this->lID = newID; }
    void setRID(int newID) { this->rID = newID; }
    void setCID(int newID) { this->cID = newID; }
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

    string getOccupation() { return this->occupation; }
    void setOccupation(string occupation) { this->occupation = occupation; }

    void editOccupation() {
        string occupation;
        cout << "职业名称" << endl;
        cin >> occupation;
        this->setOccupation(occupation);
    }

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
        cPointer birthDayCP = new Calendar();
        tm date = this->birthDay;
        birthDayCP->setCalendar(date.tm_year, date.tm_mon, date.tm_mday);
        cPointer cp = new Calendar();
        cout << "请添加死亡日期,输入-1表示未死亡" << endl;
        while (cp->addCalendar()) {
            if (cp->compareCalendar(birthDayCP) > 0) {
                year = cp->getYear();
                month = cp->getMonth();
                day = cp->getDay();
                this->setDeathDay(year, month, day);
                return;
            } else {
                cout << "死亡日期不能在出生日期前" << endl;
            }
        }
        this->setDeathDay(0, 0, 0);
        cout << "此人健康未死亡" << endl;
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
                pPointer child = father->getChild();
                while (child->getRightBrother() != NULL) {
                    child = child->getRightBrother();
                }
                child->setRightBrother(this);
                this->setLeftBrother(child);
            } else {
                father->setChild(this);
                father->setCID(this->getID());
                this->setFather(father);
                this->setFID(father->getID());
                pPointer mother = father->getSpouse();
                mother->setCID(this->getID());
                mother->setChild(this);
                this->setMother(mother);
                this->setMID(mother->getID());
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
                mother->setCID(this->getID());
                mother->setChild(this);
                this->setMother(mother);
                this->setMID(mother->getID());
                pPointer father = mother->getSpouse();
                father->setChild(this);
                father->setCID(this->getID());
                this->setFather(father);
                this->setFID(father->getID());
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
                this->setSID(spouse->getID());
                spouse->setSpouse(this);
                spouse->setSID(spouse->getID());
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
            this->setCID(newChild->getID());
            this->spouse->setChild(newChild);
            this->spouse->setCID(newChild->getID());
            pPointer father = this->sex ? this : this->getSpouse();
            newChild->setFather(father);
            newChild->setFID(father->getID());
            newChild->setMother(father->getSpouse());
            newChild->setMID(father->getSpouse()->getID());
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
            do {
                child = child->getRightBrother();
                preChild->setRightBrother(NULL);
                preChild->setLeftBrother(NULL);
                preChild->setRID(-1);
                preChild->setLID(-1);
                if (notOnlyRelation) {
                    cout << "由于删除人员，将会递归删除有关此人的所有记录"
                         << endl;
                    preChild->deletePerson();
                }
                preChild = child;
            } while (child != NULL && child->getRightBrother() != NULL);
            if (child != NULL) {
                if (notOnlyRelation) {
                    cout << "由于删除人员，将会递归删除有关此人的所有记录"
                         << endl;
                    child->deletePerson();
                }
            }
            this->setChild(NULL);
            this->setCID(-1);
            this->getSpouse()->setChild(NULL);
            this->getSpouse()->setCID(-1);
        }
    }

    void cleanBrother() {
        cout << "删除兄弟姐妹将会把父母亲也一并删除" << endl;
        pPointer leftBrother = this->getLeftBrother();
        pPointer rightBrother = this->getRightBrother();
        if (leftBrother != NULL || rightBrother != NULL) {
            if (leftBrother == NULL) {
                pPointer father = this->getFather();
                pPointer mother = this->getMother();
                father->setChild(rightBrother);
                father->setCID(rightBrother->getID());
                mother->setChild(rightBrother);
                mother->setCID(rightBrother->getID());
                rightBrother->setFather(father);
                rightBrother->setMother(mother);
                this->setFather(NULL);
                this->setSID(-1);
                this->setMother(NULL);
                this->setMID(-1);
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
            father->setChild(rightBrother);
            father->setCID(rightBrother->getID());
            mother->setChild(rightBrother);
            mother->setCID(rightBrother->getID());
            this->setFather(NULL);
            this->setSID(-1);
            this->setMother(NULL);
            this->setMID(-1);
        }
    }

    void cleanFather() {
        cout << "清除父亲关系同时会清除母亲关系" << endl;
        this->cleanBrother();
    }

    void cleanMother() {
        cout << "清除母亲关系同时会清除父亲关系" << endl;
        this->cleanBrother();
    }

    void cleanSpouse(bool notOnlyRelation) {
        pPointer spouse = this->spouse;
        cout << "清理配偶时也会将孩子清除同时会将孩子间的兄弟姐妹删除" << endl;
        if (spouse != NULL) {
            pPointer child = this->getChild();
            if (child != NULL) {
                this->cleanChild(notOnlyRelation);
            }
            spouse->setSpouse(NULL);
            spouse->setSID(-1);
            this->setSpouse(NULL);
            this->setSID(-1);
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
    }

    void deletePerson() {
        this->cleanSpouse(true);
        this->cleanBrother();
        this->cleanChild(true);
        this->setHasDelete(true);
        delete this;
    }

    void showInfo() {
        cout << left;
        cout << setw(10) << this->getName();
        cout << setw(9) << this->getSex();
        cout << setw(20) << this->getOccupation();
        cout << setw(30) << this->getAllBirthDay();
        cout << left;
        cout << setw(30) << this->getAllDeathDay();
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
            cout << setw(10) << "父亲";
            father->showInfo();
        }
        if (mother != NULL) {
            cout << setw(10) << "母亲";
            mother->showInfo();
        }
        cout << setw(10) << "本人";
        this->showInfo();
        if (spouse != NULL) {
            cout << setw(10) << "配偶";
            spouse->showInfo();
        }
        while (firstBrother != NULL) {
            if (firstBrother == this) {
                firstBrother = firstBrother->getRightBrother();
                continue;
            }
            if (firstBrother->getSex() == this->male) {
                cout << setw(10) << "兄弟";
            } else {
                cout << setw(10) << "姐妹";
            }
            firstBrother->showInfo();
            firstBrother = firstBrother->getRightBrother();
        }
        if (child != NULL) {
            do {
                cout << setw(10) << "孩子";
                child->showInfo();
                child = child->getRightBrother();
            } while (child != NULL);
        }
    }

    double getAge() {
        time_t now_time;
        now_time = time(NULL);
        tm *currentTime = localtime(&now_time);
        getEndTime(currentTime);
        tm birthday = getBirthDay();
        if (currentTime->tm_year < 1900) {
            currentTime->tm_year += 1900;
        }
        double age = 0;
        age = currentTime->tm_year - birthday.tm_year + 1;
        return age;
    }

   private:
    int id;
    int fID;         //父亲编号
    int mID;         //母亲编号
    int sID;         //配偶编号
    int lID;         //前兄弟编号
    int rID;         //后兄弟编号
    int cID;         //孩子编号
    bool hasDelete;  //判断是否已经被删除
    string name;
    string occupation;
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
    void getEndTime(tm *currentTime) {
        tm deathDay = this->getDeathDay();
        if (deathDay.tm_year != 0) {
            *currentTime = deathDay;
        }
    }
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