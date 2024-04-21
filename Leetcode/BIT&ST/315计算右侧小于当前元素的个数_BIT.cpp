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
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        BIT bit(n);
        bit.discrete(nums);
        for(int i = n - 1; i >= 0; i --){
            int id = bit.getId(nums[i]);
            ans.push_back(bit.query(id - 1));
            bit.update(id, 1);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
