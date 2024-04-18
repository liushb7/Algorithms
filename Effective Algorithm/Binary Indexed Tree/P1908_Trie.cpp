#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e5 + 10;
typedef long long ll;
// 不能开得太小了
int t[maxn * 32][2];
int sum[maxn * 32];
int idx = 0, n, x;
ll ans = 0;

void insert(ll v){
    int p = 0;
    for(int i = 31; i >= 0; i--){
        int u = (v >> i) & 1;
        if(t[p][u] == 0){
            t[p][u] = ++idx;
        }
        if(u == 0){
            ans += sum[p];
        }else{
            sum[p]++;
        }
        p = t[p][u];
    }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        insert(x);
    }
    cout << ans;
    system("pause");
}
