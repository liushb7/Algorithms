class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 2;
        while(l <= r){
            int mid = l + (r - l) / 2;
            if(nums[mid] < nums[n - 1]){
                r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        
        return nums[l];
    }
};
