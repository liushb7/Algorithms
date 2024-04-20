class BIT{
private:
    int n;
    vector<int> t;
public:
    BIT(int _n):n(_n), t(_n + 1){}

    int lowbit(int x){
        return x & (-x);
    }    

    void update(int x, int k){
        for(int i = x; i <= n; i += lowbit(i)){
            t[i]+=k;
        }
    }

    int query(int x){
        int ans = 0;
        for(int i = x; i; i -= lowbit(i)){
            ans += t[i];
        }
        return ans;
    }
};

class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        int n = *max_element(instructions.begin(), instructions.end());
        BIT bit(n);
        long long ans = 0;
        int mod = 1e9 + 7;
        for(int i = 0; i < instructions.size(); i++){
            int x = instructions[i];
            int lower = bit.query(x - 1);
            int upper = i - bit.query(x);
            ans = (ans + min(lower, upper)) % mod;
            bit.update(x, 1);
        }
        return ans;
    }
};
