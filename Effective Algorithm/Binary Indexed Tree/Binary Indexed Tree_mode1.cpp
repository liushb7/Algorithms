#include <iostream>

using namespace std;

typedef long long ll;
#define lowbit(x) (x&(-x))
const int maxn = 5 * 1e5 + 10;
ll t[maxn];
ll n, m, k, choice, x, y;

void update(ll x, ll k){
    for(ll i = x; i <= n; i+=lowbit(i)){
        t[i] += k;
    }
}

ll query(ll x){
    ll ans = 0;
    for(ll i = x; i; i-=lowbit(i)){
        ans += t[i];
    }
    return ans;
}

int main(){
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &k);
        update(i, k);
    }
    for(int i = 0; i < m; i++){
        scanf("%lld%lld%lld", &choice, &x, &y);
        if(choice == 1){
            update(x, y);
        }else{
            printf("%lld\n", query(y) - query(x - 1));
        }
    }
    system("pause");
    return 0;
}





