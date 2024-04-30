class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
      // 闭区间写法
      // 根据红蓝染色法，假设红色是峰值左侧的， 蓝色是峰值以及峰值右侧的， 这里的峰值并不确定到底是哪一个峰值， 但是一定存在
      // nums[n -1]必定是蓝色的， 因为不管峰值是nums[0],还是nums[n - 1]， 还是中间的一个数， nums[n - 1]都满足蓝色染色的条件， 因此二分查找区间为[0, n - 2]
        int l = 0, r = n - 2;//在[0, n - 2]二分查找， 同时还保证了下面nums[mid] < nums[mid + 1]不会发生下标越界， 因为有mid + 1
        while(l <= r){
            int mid = l + (r - l) / 2;
            if(nums[mid] < nums[mid + 1]){//nums[mid] < nums[mid + 1]时， 右边（mid + 1及右侧）一定存在峰值， 可以用反证法进行证明：
              // 假如mid+1及右侧没有峰值， 根据题意有nums[n] == -inf， 那么将会有nums[n] < nums[n - 1], nums[n - 1] < nums[n - 2]... 那么将会有nums[mid + 1] < nums[mid]， 矛盾！
                l = mid + 1;//l左侧为红色， 
            }else{
                r = mid - 1;//r右侧为蓝色
            }
        }

        return l;
    }
};
