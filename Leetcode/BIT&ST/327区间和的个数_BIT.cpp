class BIT{
private:
    int n;
    vector<int> t;
    vector<long long> d;
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

    void discrete(vector<long long>& nums){
        d.assign(nums.begin(), nums.end());
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
    }
    // 这题比较坑， 卡long long， 建议直接所有地方开long long， 当然除了要实现函数的返回值和参数列表
    int getId(long long x){
        return lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long> d;
        vector<long long> pre;
        pre.push_back(0);
        long long s = 0;
        for(auto& x : nums){
            s += x;
            pre.push_back(s);
        }
        for(auto& x : pre){
            d.push_back((long long)x);
            d.push_back((long long)x - lower);
            d.push_back((long long)x - upper);
        }
        int N = d.size();
        BIT bit(N);
        bit.discrete(d);
        int ans = 0;
        for(int i = 0; i < pre.size(); i ++){
            int id_left = bit.getId(pre[i] - upper);
            int id_right = bit.getId(pre[i] - lower);
            ans += bit.query(id_right) - bit.query(id_left - 1);
            int id = bit.getId(pre[i]);
            bit.update(id, 1);
        }
        return ans;
    }
};
