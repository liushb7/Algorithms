// 对于某个x:有四种情况：

//寻找第一个 >= x的位置：直接用low_bound

//寻找第一个 > x的位置：等价于第一个 >= x+1 的位置

//寻找最后一个 < x的位置：等价于第一个 >= x 的位置 -1 （即前一个位置）

//寻找最后一个 <= x的位置：等价于第一个 > x 的位置 -1 （即前一个位置）


// 三种不同的二分查找写法
class Solution {
public:
    // 循环不变量(对于闭区间写法)， l左边都是小于target的， r右边都是大于等于target的
    // l - 1一定小于target， r + 1一定大于等于target
    // 闭区间写法， while结束后[r, l]， 此时r + 1 == l， 故r + 1（也即l)为第一个大于等于x的位置
    // 当然有可能所有元素都比x小， 故l最终也可能是n

    // 如果要查找的是刚好等于target的元素， 还要判断一下第一个大于等于target的数字（如果有的话， 也即l != n)，
    // nums[l]是不是刚好等于target， 如果不是的话， 查找失败
    int lower_bound(vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;//区间[l, r]
        while(l <= r){//区间不为空
            int mid = l + (r - l) / 2;
            if(nums[mid] < target){
                l = mid + 1;//[mid + 1, r]
            }else{
                r = mid - 1;//[l, mid - 1]
            }
        }

        return l;
    }

    int lower_bound2(vector<int>& nums, int target){
        int l = 0, r = nums.size();//区间[l, r)
        while(l < r){//区间不为空
            int mid = l + (r - l) / 2;
            if(nums[mid] < target){
                l = mid + 1;//[mid + 1, r)
            }else{
                r = mid;//[l, mid)
            }
        }

        return l;//循环结束后l == r， 返回l 或 r 都一样
    }

    int lower_bound3(vector<int>& nums, int target){
        int l = -1, r = nums.size();//区间(l, r)
        while(l + 1 < r){//区间不为空
            int mid = l + (r - l) / 2;
            if(nums[mid] < target){
                l = mid;//(mid, r)
            }else{
                r = mid;//(l, mid)
            }
        }

        return r;//注意返回的是r
    }


    vector<int> searchRange(vector<int>& nums, int target) {
        int start = lower_bound(nums, target), n = nums.size();
        if(start == n ||  nums[start] != target){
            return {-1, -1};
        }
      // 最后一个小于等于target的位置等价于第一个大于target(大于等于target + 1)的位置的前一个位置
        int end = lower_bound(nums, target + 1) - 1;
        return {start, end};
    }
};
