class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto is_blue = [&](int i) {
            int end = nums[nums.size() - 1];
            if (nums[i] > end) {
                return target > end && nums[i] >= target;
            } else {
                return target > end || nums[i] >= target;
            }
        };

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
