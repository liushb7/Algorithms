#include <iostream>
#include <cstdio>
const int maxn = 100010;
#define ll long long
using namespace std;
ll n, m, arr[maxn], sum[maxn*4], tag[maxn*4];

void scan(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &arr[i]);
    }
}

void push_up(ll p){
    sum[p] = sum[p*2] + sum[p*2 + 1];
}

void pd(ll p, ll l, ll r, ll k){
    sum[p] += k * (r - l + 1);
    tag[p] += k;
}

void push_down(ll p, ll l, ll r){
    ll mid = (l + r) >> 1;
    pd(p*2, l, mid, tag[p]);
    pd(p*2 + 1, mid + 1, r, tag[p]);
    tag[p] = 0;
}

void build(ll p, ll l, ll r){
    tag[p] = 0;
    if(l == r){
        sum[p] = arr[l];
        return;
    }
    ll mid = (l + r) >> 1;
    build(p*2, l, mid);
    build(p*2 + 1, mid + 1, r);
    push_up(p); 
}

void update(ll nl, ll nr, ll l, ll r, ll p, ll k){
    if(nl <= l && r <= nr){
        tag[p] += k;
        sum[p] += k * (r - l + 1);
        return;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1;
    if(nl <= mid) update(nl, nr, l, mid, p*2, k);
    if(nr > mid) update(nl, nr, mid + 1, r, p*2 + 1, k);
    push_up(p);
}

ll query(ll nl, ll nr, ll l, ll r, ll p){
    ll res = 0;
    if(nl <= l && r <= nr) return sum[p];
    ll mid = (l + r) >> 1;
    push_down(p, l, r);
    if(nl <= mid) res += query(nl, nr, l, mid, p*2);
    if(nr > mid) res += query(nl, nr, mid + 1, r, p*2 + 1);
    return res;
}

int main(){
    ll left, right, k, key;
    scan();
    build(1, 1, n);
    while(m--){
        cin >> key;
        switch(key)
        {
            case 1:{
                scanf("%lld%lld%lld", &left, &right, &k);
                update(left, right, 1, n, 1, k);
                break;
            }
            case 2:{
                scanf("%lld%lld", &left, &right);
                printf("%lld\n", query(left, right, 1, n, 1));
                break;
            }
        }
    }
    system("pause");
    return 0;
}
