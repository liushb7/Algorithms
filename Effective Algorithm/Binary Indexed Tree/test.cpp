#include <iostream>

using namespace std;
typedef long long ll;
#define lowbit(x) (x&(-x))
const int maxn = 5 * 1e5 + 10;
ll arr[maxn], d[maxn], t[maxn];
ll n, m, k, x, y, choice;

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

int main(){
    cin >> n >> m;
    arr[0] = 0;
    for(int i = 1; i <= n; i ++){
        scanf("%lld", &arr[i]);
        d[i] = arr[i] - arr[i - 1];
        update(i, d[i]);
    }
    for(int i = 0; i < m; i ++){
        scanf("%lld", &choice);
        if(choice == 1){
            scanf("%lld%lld%lld", &x, &y, &k);
            update(x, k);
            update(y + 1, -k);
        }else{
            scanf("%lld", &x);
            printf("%lld\n", query(x));
        }
    }
    system("pause");
    return 0;
}