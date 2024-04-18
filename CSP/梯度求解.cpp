#include <bits/stdc++.h>
using namespace std;
 
const int mo = 1e9+7;
#define CONST -1
#define VAR -2
#define OP -3
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    int n, m;
    cin >> n >> m;
    getline(cin, s); // '\n'
    getline(cin, s);
    istringstream qwq(s);
    vector<int> l;
    vector<int> r;
    vector<int> info;
    vector<int> kind;
    stack<int> id;
    int node_id = 0;
    while(getline(qwq, s, ' ')){
        if (s.size() == 1 && (s[0] == '+' || s[0] == '*' || s[0] == '-')){
            int rson = id.top();
            id.pop();
            int lson = id.top();
            id.pop();
            l.push_back(lson);
            r.push_back(rson);
            info.push_back(s[0]);
            kind.push_back(OP);
 
            id.push(node_id);
            ++ node_id;
        }else if (s[0] == 'x'){
            int x = stoi(s.substr(1));
            -- x;
            l.push_back(-1);
            r.push_back(-1);
            info.push_back(x);
            kind.push_back(VAR);
 
            id.push(node_id);
            ++ node_id;
        }else{
            int x = stoi(s);
            l.push_back(-1);
            r.push_back(-1);
            info.push_back(x);
            kind.push_back(CONST);
 
            id.push(node_id);
            ++ node_id;
        }
    }
    int root = id.top();
    vector<int> a(n);
 
    function<array<int, 2>(int, int)> solve = [&](int u, int x){
        if (kind[u] == VAR){
            return array<int, 2>{a[info[u]], (info[u] == x)};
        }else if (kind[u] == CONST){
            return array<int, 2>{info[u], 0};
        }else{
            auto lans = solve(l[u], x), rans = solve(r[u], x);
            int sum = 0, dsum = 0;
            if (info[u] == '+'){
                sum = lans[0] + rans[0];
                dsum = lans[1] + rans[1];
                if (sum >= mo)  sum -= mo;
                if (dsum >= mo) dsum -= mo;
            }else if (info[u] == '-'){
                sum = lans[0] - rans[0];
                dsum = lans[1] - rans[1];
                if (sum >= mo)  sum -= mo;
                if (dsum >= mo) dsum -= mo;
            }else{
                sum = 1ll * lans[0] * rans[0] % mo;
                dsum = (1ll * lans[0] * rans[1] % mo + 1ll * lans[1] * rans[0] % mo);
                if (dsum >= mo) dsum -= mo;
            }
            if (sum < 0)
                sum += mo;
            if (dsum < 0)
                dsum += mo;
            return array<int, 2>{sum, dsum};
        }
    };
    for(int i = 0; i < m; ++ i){
        int x;
        cin >> x;
        -- x;
        for(auto &i : a)
            cin >> i;
        cout << solve(root, x)[1] << '\n';
    }
    return 0;
}