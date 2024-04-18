#include <cstdio>
#include <cstring>
#include <iostream>
// #include <algorithm>

const int maxn = 3 * 1e6 + 10;
int T, n, q, t[maxn][65], cnt[maxn], idx;
char s[maxn];

int getnum(char x){
    if(x >= 'A' && x <= 'Z') return x - 'A';
    else if(x >= 'a' && x <= 'z') return x - 'a' + 26;
    else return x - '0' + 52;
}

void insert(char str[]){
    int p = 0, len = strlen(str);
    for(int i = 0; i < len; i++){
        int c = getnum(str[i]);
        if(t[p][c] == 0){
            t[p][c] = ++idx;
        }
        p = t[p][c];
        cnt[p]++;
    }
}

int find(char str[]){
    int p = 0, len = strlen(str);
    for(int i = 0; i < len; i++){
        int c = getnum(str[i]);
        if(t[p][c] == 0){
            return 0;
        }
        p = t[p][c];
    }
    return cnt[p];
}

int main(){
    scanf("%d", &T);
    while(T--){
        for(int i = 0; i <= idx; i++){
            for(int j = 0; j < 65; j++){
                t[i][j] = 0;
            }
        }

        for(int i = 0; i <= idx; i++){
            cnt[i] = 0;
        }

        idx = 0;
        scanf("%d%d", &n, &q);
        for(int i = 0; i < n; i++){
            scanf("%s", s);
            insert(s);
        }
        for(int i = 0; i < q; i++){
            scanf("%s", s);
            printf("%d\n", find(s));
        }
    }
    system("pause");
    return 0;
}