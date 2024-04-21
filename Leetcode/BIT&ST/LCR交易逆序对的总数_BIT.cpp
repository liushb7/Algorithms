class BIT{
private:
    int n;
    vector<int> t;
    vector<int> d;
public:
    BIT(int _n):n(_n), t(_n + 1){}
 
    int lowbit(int x){
        return x & (-x);
    }

    void update(int x, int k){
        for(int i = x; i <= n; i += lowbit(i)){
            t[i] += k;
        }
    }

    int query(int x){
        int res = 0;
        for(int i = x; i; i -= lowbit(i)){
            res += t[i];
        }
        return res;
    }

    void discrete(vector<int>& nums){
        d.assign(nums.begin(), nums.end());
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
    }

    int getId(int x){
        return lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
};


class Solution {
public:
    
    int reversePairs(vector<int>& record) {
        int n = record.size();
        BIT bit(n);
        bit.discrete(record);
        vector<int> res;
        int ans = 0;
        for(int i = 0; i < n; i ++){
            int id = bit.getId(record[i]);
            // 注意是寻找前面严格大于当前数的个数， 因此是id， 而不是id - 1
            ans +=  i - bit.query(id);
            bit.update(id, 1);
        }
        return ans;
    }
};
