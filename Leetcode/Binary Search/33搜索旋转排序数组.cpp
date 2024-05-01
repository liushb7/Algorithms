// 在本题中， 蓝色的含义表示需要将查询范围缩小到蓝色之前， 也即r = mid - 1， 因为每次总是判断mid是否需要被涂成蓝色
class Solution {
public:
// 要清晰的明确目标是为了寻找target
// 数组经过旋转之后变成了两端有序数组， 其中每个数和数组最后一个数字end比较就能知道属于哪一段有序数组中：前半段都比end大， 后半段（除了end本身）都比end小
    int search(vector<int>& nums, int target) {
        // 单纯在其中一段有序数组中时， 假设小于target为红色， 大于等于target为蓝色
        // 如果target和nums[mid] 分别在两端有序数组， 那么只有当需要缩小右边界的时候才染成蓝色
        
        // 总之， 要缩小右边界才会染成蓝色！
        auto is_blue = [&](int i) {//blue函数的目的时为了判断是否缩小右边界， 即是否要将r 设置为mid - 1
            // 什么时候要缩小右边界呢？三种情况：
            // 1.  nums[mid] 和 target都在左边并且nums[mid] >= target的时候
            // 2.  nums[mid] 和 target都在右边并且nums[mid] >= target的时候
            // 3.  nums[mid] 在右边， 并且target 在左边， 那么就要缩小右边界， 往左半段[l, mid - 1]继续查找
            int end = nums[nums.size() - 1];
            if (nums[i] > end) {//此时nums[i]在左半段
                return target > end && nums[i] >= target;//如果target也在左半段，此时退化到在左边这个有序数组中寻找target， 此时nums[i]（即nums[mid]) >= target自然要将r 设置为 mid - 1;
            } else {//此时nums[i]在右半段
                return target > end || nums[i] >= target;
                // 此时
            }
        };//注意lambda函数末尾要加分号 ;

        int n = nums.size();
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (is_blue(mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        if (l == n || nums[l] != target) return -1;
        return l;
    }
};
