#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e5 + 10;
typedef long long ll;
int n, m, Rank[maxn];
ll ans = 0;

struct SegmentTree{
    int sum;
    int tag;
}st[maxn*4];

typedef struct node{
    int val;
    int idx;
}Node;

Node arr[maxn];

bool cmp(Node a, Node b){
    if(a.val != b.val) return a.val < b.val;
    else return a.idx < b.idx;
}

void push_up(int p){
    st[p].sum = st[p*2].sum + st[p*2 + 1].sum;
}

void build(int p, int l, int r){
    st[p].tag = 0;
    if(l == r){
        st[p].sum = Rank[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p*2, l, mid);
    build(p*2 + 1, mid + 1, r);
    push_up(p);
}

void pd(int p, int l, int r, int k){
    st[p].sum += k * (r - l + 1);
    st[p].tag += k;
}

void push_down(int p, int l, int r){
    int mid = (l + r) >> 1;
    pd(p*2, l, mid, st[p].tag);
    pd(p*2 + 1, mid + 1, r, st[p].tag);
    st[p].tag = 0;
}

void update(int nl, int nr, int l, int r, int p, int k){
    // 加了可以保险一点
    if(nl > nr) return;
    if(nl <= l && r <= nr){
        st[p].sum += k * (r - l + 1);
        st[p].tag += k;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if(nl <= mid) update(nl, nr, l, mid, p*2, k);
    if(nr > mid) update(nl, nr, mid + 1, r, p*2 + 1, k);
    push_up(p);
}

ll query(int nl, int nr, int l, int r, int p){
    ll res = 0;
    // 加了可以保险一点
    if(nl > nr) return 0;
    if(nl <= l && r <= nr) return st[p].sum;
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if(nl <= mid) res += query(nl, nr, l, mid, p*2);
    if(nr > mid) res += query(nl, nr, mid + 1, r, p*2 + 1);
    return res;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &arr[i].val);
        arr[i].idx = i;
    }
    sort(arr + 1, arr + 1 + n, cmp);
    // for(int i = 1; i <= 10; i ++){
    //     cout << st[i].sum << " " << st[i].tag << endl;
    // }

    build(1, 1, n);
    for(int i = 1; i <= n; i++){
        Rank[arr[i].idx] = i;
    }

    for(int i = 1; i <= n; i++){
        ans += query(1, n, 1, n, 1) - query(1, Rank[i] - 1, 1, n, 1);
        update(Rank[i], Rank[i], 1, n, 1, 1);        
    }
    cout << ans;
    system("pause");
    return 0;
}


// 6
// 5 4 2 6 3 1

