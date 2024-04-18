#include <iostream>
#include <cstdio>
using namespace std;

const int maxn = 100010;
typedef long long ll;
ll n, m, mod, arr[maxn], sum[maxn*4], add[maxn*4], mul[maxn*4];
ll key, l, r, k;

void input(){
    cin >> n >> m >> mod;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &arr[i]);
    }
}

void push_up(ll p){
    sum[p] = (sum[p*2] + sum[p*2 + 1]) % mod;
}

void build(ll p, ll l, ll r){
    add[p] = 0;
    mul[p] = 1;
    if(l == r){
        sum[p] = arr[l] % mod;
        return;
    }
    ll mid = (l + r) >> 1;
    build(p*2, l, mid);
    build(p*2 + 1, mid + 1, r);
    push_up(p);
}

void pd(ll p, ll l, ll r, ll addk, ll mulk){
    sum[p] = (sum[p] * mulk + addk * (r - l + 1)) % mod;
    mul[p] = (mul[p] * mulk) % mod;
    add[p] = (add[p] * mulk + addk) % mod;
}

void push_down(ll p, ll l, ll r){
    ll mid = (l + r) >> 1;
    pd(p*2, l, mid, add[p], mul[p]);
    pd(p*2 + 1, mid + 1, r, add[p], mul[p]);
    add[p] = 0;
    mul[p] = 1;
}

void update1(ll nl, ll nr, ll l, ll r, ll p, ll k){
    if(nl <= l && r <= nr){
        sum[p] = (sum[p] * k) % mod;
        mul[p] = (mul[p] * k) % mod;
        add[p] = (add[p] * k) % mod;
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
        sum[p] = (sum[p] + k * (r - l + 1)) % mod;
        add[p] = (add[p] + k) % mod;
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
        return sum[p];
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