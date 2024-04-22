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
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        for(int i = 0; i < nums1.size(); i ++){
            nums1[i] -= nums2[i];
        }
        vector<int> d = nums1;
        for(auto& x : nums1){
            d.push_back(x + diff);
        } 
        BIT bit(d.size());
        bit.discrete(d);
        long long ans = 0;
        for(int i = 0; i < nums1.size(); i ++){
            int id = bit.getId(nums1[i] + diff);
            ans += bit.query(id);
            int id2 = bit.getId(nums1[i]);
            bit.update(id2, 1);
        }
        return ans;
    } 
};
