#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;
const int maxn = 100010;

struct SegmentTree{
    ll sum;
    ll add;
    ll mul;
}st[maxn*4];

ll n, m, mod, arr[maxn];
ll key, l, r, k;

void input(){
    cin >> n >> m >> mod;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &arr[i]);
    }
}

void push_up(ll p){
    st[p].sum = (st[p*2].sum + st[p*2 + 1].sum) % mod;
}

void build(ll p, ll l, ll r){
    st[p].add = 0;
    st[p].mul = 1;
    if(l == r){
        st[p].sum = arr[l] % mod;
        return;
    }
    ll mid = (l + r) >> 1;
    build(p*2, l, mid);
    build(p*2 + 1, mid + 1, r);
    push_up(p);
}

void pd(ll p, ll l, ll r){
    st[p].sum = (st[p].sum * st[p/2].mul + st[p/2].add * (r - l + 1)) % mod;
    st[p].mul = (st[p].mul * st[p/2].mul) % mod;
    st[p].add = (st[p].add * st[p/2].mul + st[p/2].add) % mod;
}

void push_down(ll p, ll l, ll r){
    ll mid = (l + r) >> 1;
    pd(p*2, l, mid);
    pd(p*2 + 1, mid + 1, r);
    st[p].add = 0;
    st[p].mul = 1;
}

void update1(ll nl, ll nr, ll l, ll r, ll p, ll k){
    if(nl <= l && r <= nr){
        st[p].sum = (st[p].sum * k) % mod;
        st[p].mul = (st[p].mul * k) % mod;
        st[p].add = (st[p].add * k) % mod;
        return;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1;
    if(nl <= mid) update1(nl, nr, l, mid, p*2, k);
    if(nr > mid) update1(nl, nr, mid + 1, r, p*2 + 1, k);
    push_up(p);
}

void update2(ll nl, ll nr, ll l, ll r, ll p, ll k){
    if(nl <= l && r <= nr){
        st[p].sum = (st[p].sum + k * (r - l + 1)) % mod;
        st[p].add = (st[p].add + k) % mod;
        return;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1;
    if(nl <= mid) update2(nl, nr, l, mid, p*2, k);
    if(nr > mid) update2(nl, nr, mid + 1, r, p*2 + 1, k);
    push_up(p);
}

ll query(ll nl, ll nr, ll l, ll r, ll p){
    ll res = 0;
    if(nl <= l && r <= nr){
        return st[p].sum;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1;
    if(nl <= mid) res = (res + query(nl, nr, l, mid, p*2)) % mod;
    if(nr > mid) res = (res + query(nl, nr, mid + 1, r, p*2 + 1)) % mod;
    return res;
}

int main(){
    input();
    build(1, 1, n);
    while(m--){
        scanf("%lld", &key);
        if(key == 1){
            scanf("%lld%lld%lld", &l, &r, &k);
            update1(l, r, 1, n, 1, k);
        }else if(key == 2){
            scanf("%lld%lld%lld", &l, &r, &k);
            update2(l, r, 1, n, 1, k);
        }else if(key == 3){
            scanf("%lld%lld", &l, &r);
            printf("%lld\n", query(l, r, 1, n, 1));
        }
    }
    system("pause");
    return 0;
}