#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;



// 定义图的边结构体
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// 定义图的顶点和边的列表
vector<vector<Edge>> graph;

// Dijkstra 算法函数
vector<int> dijkstra(int start, int n) {
    vector<int> dist(n, numeric_limits<int>::max());
    dist[start] = 0;

    // 优先队列，用于按照最小距离优先处理节点
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}



int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    graph.resize(n);

    cout << "Enter edges (from to weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].emplace_back(to, weight);
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    vector<int> shortest_distances = dijkstra(start, n);

    cout << "Shortest distances from node " << start << ":" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << shortest_distances[i] << endl;
    }

    return 0;
}



#include<bits/stdc++.h>
using namespace std;
//Legacy
#define int long long
const int maxn = (int)2e5 + 10;
struct node {
    int l, r;
    int ls, rs;
} tr[maxn << 2];
struct edge {
    int to = 0;
    int vl = 0;
};
vector<edge> ed[maxn << 2];
queue<int> qwq;
struct staCk {
    int kkksc03[maxn];
    int tOp;
    void push(int x) {
        kkksc03[++tOp] = x;
        return;
    }
    void clear() {
        tOp = 0;
        return;
    }
    void makeEdge(int id, int w) {
        edge dxy;   dxy.vl = w;
        for (int i = 1; i <= tOp; i++) {
            dxy.to = kkksc03[i];
            ed[id].push_back(dxy);
        }
        return;
    }
} stk;
struct pqnode {
    int node;
    int ds;
    bool operator< (const pqnode& yxc) const {
        return ds > yxc.ds;
    }
};
priority_queue<pqnode> pq;
bool cnnct[maxn << 2];
int dis[maxn << 2];
int pointStart;
int nmaxin1;
int n, q, s;
 
void build(int id, int l, int r, bool in, int u) {
    if (!in) nmaxin1 = max(id, nmaxin1);
    tr[id].l = l;
    tr[id].r = r;
    if (l == r) {
        if (in) {
            edge zhx;   zhx.to = id;
            ed[id - nmaxin1].push_back(zhx);
        } else if (l == u) pointStart = id;
        return;
    }
    int mid = l + r >> 1;
    tr[id].ls = in ? (id - nmaxin1 << 1) + nmaxin1 : id << 1;
    tr[id].rs = in ? (id - nmaxin1 << 1 | 1) + nmaxin1 : id << 1 | 1;
    build(tr[id].ls, l, mid, in, u);
    build(tr[id].rs, mid + 1, r, in, u);
    if (in) {
        edge zhx;   zhx.vl = 0; zhx.to = id;
        ed[tr[id].ls].push_back(zhx);
        ed[tr[id].rs].push_back(zhx);
    }
    else {
        edge zhx;   zhx.vl = 0;
        zhx.to = tr[id].ls; ed[id].push_back(zhx);
        zhx.to = tr[id].rs; ed[id].push_back(zhx);
    }
    return;
}
 
void getPointV(int id, int tgtl, int tgtr) {
    int l = tr[id].l;
    int r = tr[id].r;
    if (l >= tgtl && r <= tgtr) {
        stk.push(id);
        return;
    }
    int mid = l + r >> 1;
    if (mid < tgtl) getPointV(tr[id].rs, tgtl, tgtr);
    else if (mid >= tgtr) getPointV(tr[id].ls, tgtl, tgtr);
    else {
        getPointV(tr[id].ls, tgtl, tgtr);
        getPointV(tr[id].rs, tgtl, tgtr);
    }
    return;
}
 
void getPointU(int id, int tgtl, int tgtr, int EV) {
    int l = tr[id].l;
    int r = tr[id].r;
    if (l >= tgtl && r <= tgtr) {
        stk.makeEdge(id, EV);
        return;
    }
    int mid = l + r >> 1;
    if (mid < tgtl) getPointU(tr[id].rs, tgtl, tgtr, EV);
    else if (mid >= tgtr) getPointU(tr[id].ls, tgtl, tgtr, EV);
    else {
        getPointU(tr[id].ls, tgtl, tgtr, EV);
        getPointU(tr[id].rs, tgtl, tgtr, EV);
    }
    return;
}
 
void getAnswer(int id) {
    int l = tr[id].l;
    int r = tr[id].r;
    if (l == r) {
        printf("%lld ", cnnct[id] ? dis[id] : -1);
        return;
    }
    getAnswer(tr[id].ls);
    getAnswer(tr[id].rs);
    return;
}
 
//不要用SPFA！！会TLE！！#9直接挂了（不知道为什么会TLE，理论上这道题应该是稀疏图才对）
/*
void spfa(int ps) {
    memset(dis, 0x7f, sizeof(dis));
    dis[ps] = 0;
    qwq.push(ps);
    while (!qwq.empty()) {
        int x = qwq.front();
        cnnct[x] = true;
        for (int i = 0; i < ed[x].size(); i++) {
            int y = ed[x][i].to;
            int v = ed[x][i].vl;
            if (dis[y] < dis[x] + v) continue;
            dis[y] = dis[x] + v;
            qwq.push(y);
        }
        qwq.pop();
    }
    return;
}
*/
 
void dijkstra(int ps) {
    memset(dis, 0x7f, sizeof(dis));
    dis[ps] = 0;
    pqnode zhx;
    zhx.node = ps;
    zhx.ds = 0;
    pq.push(zhx);
    while (!pq.empty()) {
        int x = pq.top().node;
        int d = pq.top().ds;
        pq.pop();
        if (cnnct[x]) continue;
        cnnct[x] = true;
        for (int i = 0; i < ed[x].size(); i++) {
            int y = ed[x][i].to;
            int v = ed[x][i].vl;
            if (cnnct[y]) continue;
            dis[y] = min(dis[y], d + v);
            pqnode lxl;
            lxl.node = y;
            lxl.ds = dis[y];
            pq.push(lxl);
        }
    }
}
 
signed main() {
    scanf("%lld %lld %lld", &n, &q, &s);
    build(1, 1, n, 0, s);
    build(1 + nmaxin1, 1, n, 1, 0);
    for (int i = 1; i <= q; i++) {
        int opt, u, l, r, w;
        scanf("%lld", &opt);
        if (opt == 1) {
            scanf("%lld %lld %lld", &u, &r, &w);
            getPointV(1, r, r);
            getPointU(1 + nmaxin1, u, u, w);
            stk.clear();
        }
        else if (opt == 2) {
            scanf("%lld %lld %lld %lld", &u, &l, &r, &w);
            getPointV(1, l, r);
            getPointU(1 + nmaxin1, u, u, w);
            stk.clear();
        }
        else if (opt == 3) {
            scanf("%lld %lld %lld %lld", &u, &l, &r, &w);
            getPointV(1, u, u);
            getPointU(1 + nmaxin1, l, r, w);
            stk.clear();
        }
    }
    //不要用SPFA！！会TLE！！#9直接挂了（不知道为什么会TLE，理论上这道题应该是稀疏图才对）  × 2
    // spfa(pointStart);
    dijkstra(pointStart);
    getAnswer(1);
    return 0;
}