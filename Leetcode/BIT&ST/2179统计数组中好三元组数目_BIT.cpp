class BIT{
private:
    int n;
    vector<int> t;
public:
    BIT(int _n):n(_n), t(_n + 1) {}

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
};


class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        long long ans = 0;
        int n = nums1.size();
        vector<int> p(n);
        for(int i = 0; i < n; i++){
            p[nums1[i]] = i;
        }
        vector<int> temp(n);
        // 处理为1~n方便操作
        for(int i = 0; i < n; i++){
            temp[i] = p[nums2[i]] + 1;
        }
        BIT bit(n);
        for(int i = 0; i < n; i ++){
            int x = temp[i];
            long long lower = bit.query(x - 1);
            long long upper = n - x - (i - lower);
            ans += lower * upper;
            bit.update(x, 1);
        }
        return ans;
    }
};
