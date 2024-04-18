#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e5 + 10;
typedef long long ll;
ll arr[maxn], temp[maxn];
ll n, ans;

void mergeSort(ll l, ll r){
    if(l == r) return;
    ll mid = (l + r) >> 1, i = l, j = mid + 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    ll k = l;
    while(i <= mid && j <= r){
        if(arr[i] > arr[j]){
            temp[k++] = arr[j++];
            ans += mid - i + 1;
        }else{
            temp[k++] = arr[i++];
        }
    }
    while(i <= mid){
        temp[k++] = arr[i++];
    }
    while(j <= r){
        temp[k++] = arr[j++];
    }
    for(ll i = l; i <= r; i++){
        arr[i] = temp[i];
    }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i ++){
        scanf("%lld", &arr[i]);
    }
    mergeSort(0, n - 1);
    cout << ans;
    system("pause");
    return 0;
}