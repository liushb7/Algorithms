// 尚未搞明白...
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long k = ((long long)n * (n + 1) / 2 + 1) / 2;

        auto check = [&](int upper){
            long long cnt = 0;
            int l = 0;
            unordered_map<int, int> mp;
            for(int r = 0; r < n; r ++){
                mp[nums[r]]++;
                while(mp.size() > upper){
                    int out = nums[l];
                    if(--mp[out] == 0){
                        mp.erase(out);
                    }
                    l += 1;
                }

                cnt += (r - l + 1);
                if(cnt >= k){
                    return true;
                }
            }
            return false;
        };

        int l = 1, r = n;
        while(l <= r){
            int mid = l + (r - l) / 2;
            if(check(mid)){
                r = mid - 1;
            }else{
                l = mid + 1;
            }
        }

        return l;
    }
};
