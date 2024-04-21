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
    int reversePairs(vector<int>& nums) {
       int n = nums.size();
       vector<long long> d;
       for(auto& x : nums){
            d.push_back((long long)x);
            d.push_back((long long)x * 2);
       }
       // 使用离散化后的数组大小来初始化 BIT
       BIT bit(d.size()); 
       int ans = 0;
       bit.discrete(d);
       for(int i = 0; i < n; i ++){
            int id = bit.getId((long long)nums[i] * 2);
            int id2 = bit.getId((long long)nums[i]);
            ans += i - bit.query(id);
            bit.update(id2, 1);
       }
       return ans;
    }
};
