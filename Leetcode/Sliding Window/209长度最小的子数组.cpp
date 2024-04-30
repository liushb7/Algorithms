class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
      // 滑动窗口模板
        int l = 0, ans = INT_MAX, s = 0, n = nums.size();
        for(int r = 0; r < n; r ++){
            s += nums[r];
          // 满足条件时一直循环， 并更新ans的最小值
            while(s >= target){
                ans = min(ans, r - l + 1);
                s -= nums[l];
                l += 1;
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
