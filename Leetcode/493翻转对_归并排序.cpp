class Solution {
public:
    long long ans = 0;

    void mergeSort(vector<int>& nums, int l, int r){
        if(l == r) return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        vector<int> temp;
        int i = l, j = mid + 1;
        while(i <= mid){
            while(j <= r && nums[i] > 2 * (long long)nums[j]) j++;
            ans += j - (mid + 1);
            i++;
        }
        i = l, j = mid + 1;
        while(i <= mid && j <= r){
            if(nums[i] <= nums[j]){
                temp.push_back(nums[i++]);
            }else{
                temp.push_back(nums[j++]);
            }
        }
        while(i <= mid){
            temp.push_back(nums[i++]);
        }
        while(j <= r){
            temp.push_back(nums[j++]);
        }
        for(int k = l; k <= r; k++){
            nums[k] = temp[k - l];
        }
    }

    int reversePairs(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return ans;
    }
};
