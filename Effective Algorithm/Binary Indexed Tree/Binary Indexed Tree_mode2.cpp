#include <iostream>

using namespace std;
#define lowbit(x) (x&(-x))
typedef long long ll;
const int maxn = 5 * 1e5 + 10;
ll arr[maxn], d[maxn], t[maxn];
ll n, m, choice, x, y, k;

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
        cin >> arr[i];
        d[i] = arr[i] - arr[i - 1];
        update(i, d[i]);
    }
    for(int i = 0; i < m; i ++){
        cin >> choice;
        if(choice == 1){
            cin >> x >> y >> k;
            update(x, k);
            update(y + 1, -k);
        }else{
            cin >> x;
            printf("%lld\n", query(x));
        }
    }
    system("pause");
    return 0;
}