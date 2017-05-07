35. 单词计数， DFA自动机， Trie图 ACM算法模板集 WisKey - 169 -
    // linle专场考研路茫茫——单词情结
    // 由正则表达式构造NFA， NFA转DFA，最小化DFA
    // 构造状态转移矩阵，矩阵乘法
    typedef unsigned long long ULL;
#define foreach(it, c) for (it = (c).begin(); it != (c).end(); it++)
#define forsize(it, c) for (it = 0; it < (c).size(); it++)
const int NMAX = 6;
int n, l;
char rt[NMAX][6];
const int SMAX = 80;
#define ADD(a, x) ((a) = ((a) + (x)))
struct MATRIX {
    ULL mat[SMAX][SMAX];
    int n;
    MATRIX(int _n = SMAX) {
        n = _n;
        memset(mat, 0, sizeof(mat));
    }
    void to_E(int nn) {
        int i;
        n = nn;
        memset(mat, 0, sizeof(mat));
        for (i = 0; i < n; i++) mat[i][i] = 1;
    }
    void fill(const MATRIX &mt, int x, int y) {
        int i, j;
        for (i = 0; i < mt.n; i++)
            for (j = 0; j < mt.n; j++) mat[i + x][j + y] = mt.mat[i][j];
    }
    MATRIX operator*(const MATRIX &mt) {
        MATRIX ret;
        int i, j, k;
        ACM算法模板集 WisKey - 170 -
            for (i = 0; i < n; i++) for (j = 0; j < n; j++) {
            ret.mat[i][j] = 0;
            for (k = 0; k < n; k++)
                ADD(ret.mat[i][j], mat[i][k] * mt.mat[k][j]);
        }
        ret.n = n;
        return ret;
    }
    MATRIX operator^(int ex) {
        int i;
        MATRIX ret, tmp;
        ret = *this;
        tmp.to_E(this->n);
        while (ex > 1) {
            if (ex & 1) tmp = tmp * ret;
            ret = ret * ret;
            ex >>= 1;
        }
        ret = ret * tmp;
        return ret;
    }
};
const int NFAMAX = 60;
struct EDGE {
    char ch;
    int next;
    EDGE(char _c = 0, int _n = 0) : ch(_c), next(_n) {}
};
vector<EDGE> nfa[NFAMAX];
vector<EDGE> dfa[NFAMAX];
vector<EDGE> mindfa[NFAMAX];
intnfact;
intdfasn;
intmindfasn;
vector<int> dfact;
vector<int> mindfact;
ACM算法模板集 WisKey - 171 -
#define BADD(x, p) ((x) |= ((ULL)1 << (p)))
#define BSUB(x, p) ((x) &= ~((ULL)1 << (p)))
#define BGET(x, p) ((x) & ((ULL)1 << (p)))
    void make_nfa() {
    int i, j, k;
    for (i = 0; i < NFAMAX; i++) nfa[i].clear();
    for (i = 'a'; i <= 'z'; i++) nfa[0].push_back(EDGE(i, 0));
    nfact = 1;
    int lend[NMAX];
    for (i = 0; i < n; i++) {
        nfa[0].push_back(EDGE('$', nfact++));
        for (j = 0; rt[i][j]; j++) {
            nfa[nfact - 1].push_back(EDGE(rt[i][j], nfact));
            nfact++;
        }
        lend[i] = nfact - 1;
    }
    for (i = 0; i < n; i++) nfa[lend[i]].push_back(EDGE('$', nfact));
    for (i = 'a'; i <= 'z'; i++) nfa[nfact].push_back(EDGE(i, nfact));
    nfact++;
}
bitset<NFAMAX> vis;
ULL e_closure(int now) {
    int i, j;
    ULL ret = 0;
    vector<EDGE>::iterator iter;
    BADD(ret, now);
    if (vis[now]) return ret;
    ACM算法模板集 WisKey - 172 - vis[now] = true;
    foreach (iter, nfa[now])
        if (iter->ch == '$') ret |= e_closure(iter->next);
    return ret;
}
ULL e_closure2(ULL now) {
    int i, j;
    ULL ret = now;
    vis.reset();
    for (i = 0; i < nfact; i++)
        if (BGET(now, i)) ret |= e_closure(i);
    return ret;
}
map<ULL, int> hash;
void dfs(ULL now) {
    int i, j;
    vector<EDGE>::iterator iter;
    vector<int>::iterator iter2;
    vector<int> nxt[30];
    for (i = 0; i < nfact; i++) {
        if (BGET(now, i)) {
            foreach (iter, nfa[i]) {
                if (iter->ch == '$') continue;
                nxt[iter->ch - 'a'].push_back(iter->next);
            }
        }
    }
    int stag = hash[now];
    for (i = 'a'; i <= 'z'; i++) ACM算法模板集 WisKey - 173 - {
            if (nxt[i - 'a'].empty()) continue;
            ULL next = 0;
            foreach (iter2, nxt[i - 'a'])
                BADD(next, *iter2);
            next = e_closure2(next);
            bool flag = false;
            int ntag = hash[next];
            if (ntag == 0) ntag = hash[next] = dfasn++, flag = true;
            dfa[stag - 1].push_back(EDGE(i, ntag - 1));
            if (flag) {
                if (BGET(next, nfact - 1)) dfact.push_back(ntag - 1);
                dfs(next);
            }
        }
}
void nfa_dfa() {
    int i, j, k;
    dfasn = 1;
    vis.reset();
    hash.clear();
    dfact.clear();
    for (i = 0; i < NFAMAX; i++) dfa[i].clear();
    ULL bs = e_closure(0);
    hash[bs] = dfasn++;
    dfs(bs);
}
void min_dfa() {
    int i, j, k;
    vector<vector<int>> split;
    vector<EDGE>::iterator iter;
    int belg[NFAMAX];
    ACM算法模板集 WisKey - 174 - for (i = 0; i < dfasn; i++) {
        vector<int> newi;
        newi.push_back(i);
        split.push_back(newi);
        belg[i] = i;
    }
    bool flag = true;
    while (flag) {
        flag = false;
        for (i = 0; i < split.size(); i++) {
            for (j = i + 1; j < split.size(); j++) {
                vector<pair<char, int>> ibel, jbel;
                for (k = 0; k < split[i].size(); k++)
                    foreach (iter, dfa[split[i][k]])
                        ibel.push_back(make_pair(iter->ch, belg[iter->next]));
                for (k = 0; k < split[j].size(); k++)
                    foreach (iter, dfa[split[j][k]])
                        jbel.push_back(make_pair(iter->ch, belg[iter->next]));
                sort(ibel.begin(), ibel.end());
                sort(jbel.begin(), jbel.end());
                if (ibel == jbel) {
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
        if (flag) {
            int s1 = belg[split[i][0]], s2 = belg[split[j][0]];
            for (k = 0; k < dfasn; k++)
                if (belg[k] == s2) belg[k] = s1;
            split[i].insert(split[i].end(), split[j].begin(), split[j].end());
            split.erase(split.begin() + j);
        }
    }
    ACM算法模板集 WisKey - 175 -
        for (i = 0; i < split.size(); i++) for (j = 0; j < split[i].size(); j++)
            belg[split[i][j]] = i;
    bitset<NFAMAX> acts;
    for (i = 0; i < dfact.size(); i++) acts[dfact[i]] = true;
    mindfact.clear();
    mindfasn = split.size();
    for (i = 0; i < mindfasn; i++) {
        int go[30];
        memset(go, -1, sizeof(go));
        mindfa[i].clear();
        flag = false;
        for (j = 0; j < split[i].size(); j++) {
            if (acts[split[i][j]]) flag = true;
            foreach (iter, dfa[split[i][j]])
                go[iter->ch - 'a'] = belg[iter->next];
        }
        for (j = 'a'; j <= 'z'; j++)
            if (go[j - 'a'] != -1) mindfa[i].push_back(EDGE(j, go[j - 'a']));
        if (flag) mindfact.push_back(i);
    }
}
MATRIX T;
MATRIX TT;
MATRIX BT;
MATRIX E;
void make_matrix() {
    int i, j;
    vector<EDGE>::iterator iter;
    E.to_E(mindfasn);
    ACM算法模板集 WisKey - 176 - T.n = mindfasn;
    memset(T.mat, 0, sizeof(T.mat));
    for (i = 0; i < mindfasn; i++) {
        foreach (iter, mindfa[i])
            T.mat[i][iter->next]++;
    }
    // 构造等比矩阵
    BT.n = mindfasn << 1;
    memset(BT.mat, 0, sizeof(BT.mat));
    BT.fill(T, 0, 0);
    BT.fill(E, 0, mindfasn);
    BT.fill(E, mindfasn, mindfasn);
}
ULL solve() {
    int i, j;
    ULL ret = 0;
    vector<EDGE>::iterator iter;
    make_nfa();
    nfa_dfa();
    dfasn = hash.size();
    min_dfa();
    make_matrix();
    BT = BT ^ l;
    TT.n = mindfasn;
    for (i = 0; i < mindfasn; i++)
        for (j = 0; j < mindfasn; j++) TT.mat[i][j] = BT.mat[i][j + mindfasn];
    T = T * TT;
    for (i = 0; i < mindfact.size(); i++) ret += T.mat[0][mindfact[i]];
    return ret;
}
int main() {
    int i, j;
    while (scanf("%d %d", &n, &l) == 2) {
        for (i = 0; i < n; i++) ACM算法模板集 WisKey - 177 - scanf("%s", rt[i]);
        printf("%I64u\n", solve());
    }
}
// HDU 2471 History of Languages
// DFA同构判断
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
const int NMAX = 2010;
const int TMAX = 26;
const int FAIL = -1;
int sigma;  // 字符集大小
bool dis[NMAX][NMAX];
int lx[NMAX * NMAX], ly[NMAX * NMAX];
struct DFA {
    int X[NMAX][TMAX];
    bool F[NMAX];
    int n;
    void read() {
        int i, j, k;
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%d", &k);
            F[i] = (k == 1);
            for (j = 0; j < sigma; j++) {
                scanf("%d", &X[i][j]);
                if (X[i][j] == -1) X[i][j] = n;
            }
        }
        // 虚拟一个非接受态节点，再补边
        F[n] = false;
        for (i = 0; i < sigma; i++) X[n][i] = n;
        // n++;
    }
    void Minization(DFA &dst) {
        memset(dst.X, -1, sizeof(dst.X));
        ACM算法模板集 WisKey - 178 - int i, j, ch;
        int p, q;
        bool vis[NMAX] = {false};
        vis[0] = true;
        fill(vis, vis + n, true);
        fill(dis[0], dis[n], false);
        int Q[NMAX], Qf, Qr;
        Qf = Qr = 0;
        Q[Qr++] = 0;
        while (Qf < Qr) {
            p = Q[Qf++];
for
    < / (ch = 0; ch < sigma; ch++) {
        q = X[p][ch];
        if (q != -1 && !vis[q]) {
            vis[q] = true;
            Q[Qr++] = q;
        }
    }
        }
        for (i = 0; i < n; i++) {
            if (!vis[i]) continue;
            for (j = i + 1; j < n; j++) {
                if (!vis[j]) continue;
                if (F[i] != F[j]) dis[i][j] = dis[j][i] = true;
            }
        }
        while (1) {
            bool update = false;
            for (i = 0; i < n; i++) {
                if (!vis[i]) continue;
                for (j = i + 1; j < n; j++) {
                    if (!vis[j]) continue;
                    if (dis[i][j] == true) continue;
                    for (ch = 0; ch < sigma; ch++) {
                        p = X[i][ch];
                        q = X[j][ch];
                        if (p == -1 && q == -1) continue;
                        if (p == -1 || q == -1 || dis[p][q]) {
                            ACM算法模板集 WisKey - 179 - dis[i][j] = dis[j][i] =
                                true;
                            update = true;
                            break;
                        }
                    }  // update
                }      // for j
            }          // for i
            if (!update) break;
        }  // while
        int id[NMAX], cnt = 0;
        fill(id, id + n, -1);
        for (i = 0; i < n; i++) {
            if (!vis[i]) continue;
            if (id[i] != -1) continue;
            for (j = 0; j < n; j++) {
                if (!vis[j]) continue;
                if (dis[i][j] == false) id[j] = cnt;
            }
            cnt++;
        }
        dst.n = cnt;
        for (i = 0; i < n; i++) {
            if (!vis[i]) continue;
            if (id[i] != -1) continue;
            p = id[i];
            dst.F[p] = F[i];
            for (ch = 0; ch < sigma; ch++) {
                q = X[i][ch];
                if (q != FAIL) q = id[q];
                dst.X[p][ch] = q;
            }
        }
    }
    void show() {
        int i, j;
        for (i = 0; i < n; i++) {
            cout << F[i] << " ";
            for (j = 0; j < sigma; j++) cout << X[i][j] << " ";
            ACM算法模板集 WisKey - 180 - cout << endl;
        }
        cout << endl;
    }
    bool equals(DFA &dfa2) {
        memset(dis, 0, sizeof(dis));
        int p, q;
        p = q = 0;
        lx[q] = 0;
        ly[q] = 0;
        dis[0][0] = true;
        q++;
        while (p < q) {
            if (F[lx[p]] != dfa2.F[ly[p]]) break;
            for (int k = 0; k < sigma; k++)
                if (!dis[X[lx[p]][k]][dfa2.X[ly[p]][k]]) {
                    dis[X[lx[p]][k]][dfa2.X[ly[p]][k]] = true;
                    lx[q] = X[lx[p]][k];
                    ly[q] = dfa2.X[ly[p]][k];
                    q++;
                }
            p++;
        }
        return p == q;
    }
};
DFA a, b;
int main() {
    int cas = 1;
    while (scanf("%d", &sigma), sigma) {
        a.read();
        b.read();
        printf("Case #%d: ", cas++);
        if (a.equals(b))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
/*
ACM算法模板集 WisKey
- 181-
Trie图
在
Tire树的基础上补边（类似AC自动机）
可用于多字符串匹配和自动机的构造
图可转换为矩阵，或拓扑排序，用作统计或动态规划之用
*/
typedef pair<int, int> PII;
typedef vector<PII> TRANS;
const int VMAX = 200;
const int SIGMAX = 50;
char d2c[110] = "ACGT";  // 字符集
struct TrieGraph {
    struct NODE {
        int suffix;        // 后缀节点指针
        int father;        // 父节点指针
        int next[SIGMAX];  // 儿子节点指针
        bool mark;         // 标记是否出现过
        char ch;           // 入边信息
    };
    NODE mem[VMAX];
    int vn, root;
    char c2d[300];  // 字符集hash表
    int siglen;     // 字符集大小
    int new_node(char ch, int fat) {
        memset(mem + vn, 0, sizeof(NODE));
        mem[vn].ch = ch;
        mem[vn].father = fat;
        return vn++;
    }
    // 初始化(字符集)
    void init(char *pstr) {
        vn = 0;
        siglen = strlen(pstr);
        for (int i = 0; pstr[i]; i++) c2d[pstr[i]] = i;
        // 初始化节点，用作安全转移
        root = new_node('$', 0);
        for (int i = 0; i < siglen; i++)
            mem[root].next[i] = new_node(pstr[i], root);
    }
    // 构造Trie
    void insert(char *pstr) {
        ACM算法模板集 WisKey - 182 - int i;
        for (i = root; *pstr; pstr++) {
            int x = c2d[*pstr];
            if (mem[i].next[x] == 0) mem[i].next[x] = new_node(*pstr, i);
            i = mem[i].next[x];
        }
        mem[i].mark = true;
    }
    int get_suffix(int idx) {
        int fat = mem[idx].father;
        if (fat == root) return root;
        int ich = c2d[mem[idx].ch];
        for (fat = mem[fat].suffix; fat != root && mem[fat].next[ich] == 0;
             fat = mem[fat].suffix)
            ;
        if (mem[fat].next[ich] == 0) return root;
        return mem[fat].next[ich];
    }
    // 构造Trie Graph
    void construct() {
        queue<int> sq;
        for (int i = 0; i < siglen; i++) {
            if (mem[root].next[i] == 0) continue;
            NODE &son = mem[mem[root].next[i]];
            son.suffix = get_suffix(mem[root].next[i]);
            sq.push(mem[root].next[i]);
        }
        while (!sq.empty()) {
            int idx = sq.front();
            sq.pop();
            NODE &now = mem[idx];
            for (int i = 0; i < siglen; i++) {
                int sonidx = now.next[i];
                NODE &son = mem[sonidx];
                if (sonidx == 0) continue;
                sq.push(sonidx);
                son.suffix = get_suffix(sonidx);
                son.mark = son.mark || mem[son.suffix].mark;
            }
            for (int i = 0; i < siglen; i++) {
                if (now.next[i] != 0) continue;
                now.next[i] = mem[now.suffix].next[i];
            }
        }
    }
    ACM算法模板集 WisKey - 183 -
        // 构造安全图
        TRANS make_safe_graph() {
        queue<int> sq;
        bitset<VMAX> vis;
        TRANS ret;
        sq.push(root);
        vis[root] = true;
        while (!sq.empty()) {
            int idx = sq.front();
            sq.pop();
            NODE &now = mem[idx];
            for (int i = 0; i < siglen; i++) {
                int sonidx = now.next[i];
                if (sonidx == 0 || mem[sonidx].mark) {
                    now.next[i] = 0;  // 更新Trie Graph
                    continue;
                }
                ret.push_back(PII(idx, sonidx));
                if (vis[sonidx]) continue;
                sq.push(sonidx);
                vis[sonidx] = true;
            }
        }
        return ret;
    }
    void print() {
        printf("%6s%6s%6s%6s...\n", "Node", "Suff", "Mark", "Son");
        for (int i = 0; i < vn; i++) {
            printf("%6d%6d%6d", i, mem[i].suffix, mem[i].mark);
            for (int j = 0; j < siglen; j++) printf("%6d", mem[i].next[j]);
            puts("");
        }
    }
};
/*
PKU 1625 Censored!
求长度为m，字符集为n且不含p个不良单词的字符串的数目，
就是求在安全图中从根结点出发走m步有多少种走法。
用count[step,x]表示从根结点出发走step步到结点x的走法数。
fillchar(count,sizeof(count),0);
count[0,根]:=1;
for step:=1 to m do
for 安全图中每条边(i,j) do
inc(count[step,j],count[step-1,i]);
ACM算法模板集 WisKey
- 184-
ans:=0;
for 安全图中每个结点x do
inc(ans,count[m,x]);
*/
/*
PKU 2778 DNA Sequence
用矩阵做状态转移，矩阵二分求答案
*/
int n, m, p;
xnum dp[2][VMAX];
TrieGraph tg;
void solve() {
    int i, j;
    xnum ret = 0;
    TRANS tr = tg.make_safe_graph();
    for (i = 0; i < tg.vn; i++) dp[0][i] = dp[1][i] = 0;
    dp[0][0] = 1;
    for (i = 1; i <= m; i++) {
        for (j = 0; j < tr.size(); j++)
            dp[i & 1][tr[j].second] =
                dp[i & 1][tr[j].second] + dp[(i & 1) ^ 1][tr[j].first];
        for (j = 0; j < tg.vn; j++) dp[(i & 1) ^ 1][j] = 0;
    }
    for (i = 0; i < tg.vn; i++) ret = ret + dp[m & 1][i];
    ret.print();
    puts("");
}
int main() {
    int i, j;
    char str[110];
    while (scanf("%d %d %d", &n, &m, &p) == 3) {
        scanf("%s", d2c);
        tg.init(d2c);
        for (i = 0; i < p; i++) {
            scanf("%s", str);
            ACM算法模板集 WisKey - 185 - tg.insert(str);
        }
        tg.construct();
        // tg.print();
        solve();
    }
}