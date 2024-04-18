#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define lowbit(x) (x&(-x))
const int maxn = 5e5 + 10;

typedef struct node{
    ll val;
    ll ind;
}Node;

Node arr[maxn];
ll t[maxn], Rank[maxn];
ll n;

void update(ll x, ll k){
    for(ll i = x; i <= n; i += lowbit(i)){
        t[i] += k;
    }
}

ll query(ll x){
    ll ans = 0;
    for(ll i = x; i; i -= lowbit(i)){
        ans += t[i];
    }
    return ans;
}

ll cmp(Node a, Node b){
    if(a.val != b.val) return a.val < b.val;
    else return a.ind < b.ind;
}

ll cmp2(Node a, Node b){
    if(a.val != b.val) return a.val > b.val;
    else return a.ind > b.ind;
}

int main(){
    ll ans = 0;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        scanf("%lld", &arr[i].val);
        arr[i].ind = i;
    }
    sort(arr + 1, arr + 1 + n, cmp);
    // sort(arr + 1, arr + 1 + n, cmp2);
    for(int i = 1; i <= n; i ++){
        Rank[arr[i].ind] = i;
    }
    for(int i = 1; i <= n; i ++){
        int pos = Rank[i];
        ans += query(n) - query(pos);
        // ans += query(pos - 1);
        update(pos, 1);
    }
    cout << ans;
    system("pause");
    return 0;
}