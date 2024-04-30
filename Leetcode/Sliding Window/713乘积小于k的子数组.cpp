class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k <= 1) return 0;
        int n = nums.size(), l = 0, prod = 1, ans = 0;
        for(int r = 0; r < n; r ++){
            prod *= nums[r];
          // 经过while循环， 条件从不满足变为条件满足
            while(prod >= k){
                prod /= nums[l];
                l += 1;
            }
          // 统计子数组个数的思路是：通过遍历r， 累加以r结尾的满足条件的子数组个数
            ans += (r - l + 1);
        }
        
        return ans;
    }
};
