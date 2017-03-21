#include <iostream>
#include <vector>
using namespace std;
#define datatype int
#define pointer struct node *
#define bitree pointer
#define MAXSIZE 10000
struct node {
  datatype data;
  pointer lchild;
  pointer rchild;
};
typedef struct {
  pointer data[MAXSIZE];
  int front, rear;
} sqqueue;
void initiateQueue(sqqueue *sq) {
  sq->front = 0;
  sq->rear = 0;
}
bool isEmpty(sqqueue *sq) {
  if (sq->rear == sq->front)
    return true;
  else
    return false;
}
bool isFull(sqqueue *sq) {
  if ((sq->rear - sq->front + MAXSIZE + 1) % MAXSIZE == 0) {
    return true;
  } else
    return false;
}
void enSqqueue(sqqueue *sq, pointer t) {
  if (isFull(sq) == 1)
    return;
  sq->rear = (sq->rear + 1) % MAXSIZE;
  sq->data[sq->rear] = t;
  return;
}
void deSqqueue(sqqueue *sq, pointer *t) {
  if (isEmpty(sq) == 1)
    return;
  sq->front = (sq->front + 1) % MAXSIZE;
  *t = sq->data[sq->front];
}
void floororder(bitree t) {
  sqqueue queue;
  sqqueue *sq = &queue;
  initiateQueue(sq);
  enSqqueue(sq, t);
  pointer p;
  vector<datatype> vec;
  while (isEmpty(sq) == 0) {
    deSqqueue(sq, &p);
    vec.push_back(p -> data);
    if (p->lchild != NULL)
      enSqqueue(sq, p->lchild);
    if (p->rchild != NULL)
      enSqqueue(sq, p->rchild);
  }
  vector<datatype>::iterator it = vec.begin();
  cout<<*it;
  it++;
  for(;it != vec.end();it++) {
      cout<<" "<<*it;
  }
}
bitree create(datatype Pre[], int ps, int pe, datatype In[], int is, int ie) {
  if (ps > pe) {
    return NULL;
  }
  bitree t = new node;
  t->data = Pre[ps];
  int i = is;
  while (In[i] != Pre[ps]) {
    i++;
  }
  t->lchild = create(Pre, ps + 1, ps + i - is, In, is, i - 1);
  t->rchild = create(Pre, ps + i - is + 1, pe, In, i + 1, ie);
  return t;
}
bitree preInCreate(int n) {
  datatype Pre[MAXSIZE + 1];
  datatype In[MAXSIZE + 1];
  datatype ch;
  int i = 0;
  for (i = 0; i < n; i++) {
    cin >> ch;
    In[i] = ch;
  }
  Pre[n] = '\0';
  i = 0;
  for (i = 0; i < n; i++) {
    cin >> ch;
    Pre[i] = ch;
  }
  In[n] = '\0';
  bitree t = create(Pre, 0, n - 1, In, 0, n - 1);
  return t;
}
void changeChild(bitree t) {
  if (t == NULL)
    return;
  pointer p = t->lchild;
  t->lchild = t->rchild;
  t->rchild = p;
  changeChild(t->lchild);
  changeChild(t->rchild);
}
int main(void) {
  int n;
  cin >> n;
  bitree t = preInCreate(n);
  changeChild(t);
  floororder(t);
  return 0;
}