#include <algorithm>
#include <iostream>
using namespace std;
#define pointer struct item *
#define MAX 50
struct item {
    double weight;
    double price;
};
int input(pointer items[], int *maxWeight) {
    cout << "输入背包的容量" << endl;
    cin >> *maxWeight;
    int weight, price;
    int length = 0;
    cout << "请依次输入物品，先输入重量再输入价格, 重量或价格小于等于0时退出"
         << endl;
    while (cin >> weight && weight > 0) {
        cin >> price;
        if (price <= 0) {
            break;
        }
        pointer it = new item;
        it->weight = weight;
        it->price = price;
        length++;
        items[length] = it;
    }
    return length;
}

void findBest(pointer items[], int current, int length, int currentPrice,
              int currentWeight, int maxWeight, int *maxPrice) {
    if (current > length) {
        if (currentPrice > *maxPrice) {
            *maxPrice = currentPrice;
        }
    } else {
        findBest(items, current + 1, length, currentPrice, currentWeight,
                 maxWeight, maxPrice);
        if (items[current]->weight + currentWeight <= maxWeight) {
            currentWeight += items[current]->weight;
            currentPrice += items[current]->price;
            findBest(items, current + 1, length, currentPrice, currentWeight,
                     maxWeight, maxPrice);
        }
    }
}

int compare(pointer i, pointer j) {
    return i->price / i->weight < j->price / j->weight;
}

void findBestInCycle(pointer items[], int length, int maxWeight,
                     int *maxPrice) {
    int currentWeight = 0;
    int currentPrice = 0;
    int current = 1;
    int place[MAX] = {0};
    while (current <= length) {
        while (current <= length &&
               items[current]->weight + currentWeight <= maxWeight) {
            currentWeight += items[current]->weight;
            currentPrice += items[current]->price;
            place[current] = 1;
            current++;
        }
        if (currentPrice > *maxPrice) {
            *maxPrice = currentPrice;
            while (current-- > 0) {
                if (place[current] == 1) {
                    currentWeight -= items[current]->weight;
                    currentPrice -= items[current]->price;
                    break;
                }
            }
            current++;
        }
    }
}

int main(void) {
    cout << "回溯法解决0/1背包问题" << endl;
    pointer items[MAX];
    int maxWeight;
    int maxPrice;
    int length = input(items, &maxWeight);
    sort(items + 1, items + length, compare);
    cout << "递归查找" << endl;
    findBest(items, 1, length, 0, 0, maxWeight, &maxPrice);
    cout << "maxPrice = " << maxPrice << endl;
    maxPrice = 0;
    cout << "循环查找" << endl;
    findBestInCycle(items, length, maxWeight, &maxPrice);
    cout << "maxPrice = " << maxPrice << endl;
    return 0;
}

/*
25
20 20
15 30
10 25
0
*/