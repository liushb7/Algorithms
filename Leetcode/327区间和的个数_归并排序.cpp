class Solution {
public:
    int low, up, ans = 0;
    
    void mergeSort(vector<long long>& nums, int l, int r){
        if(l >= r) return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1, k = mid + 1;
        while(i <= mid){
            while(j <= r && nums[j] - nums[i] < low) j++;
            while(k <= r && nums[k] - nums[i] <= up) k++;
            ans += (k - j);
            i++;
        }
        // 这里不要忘记开long long!
        vector<long long> temp;
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
        for(int i = l; i <= r; i++){
            nums[i] = temp[i - l];
        }
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        low = lower;
        up = upper;
        vector<long long> pre;
        pre.push_back(0);
        for(int i = 1; i <= nums.size(); i++){
            pre.push_back(pre[i - 1] + nums[i - 1]);
        }
        mergeSort(pre, 0, pre.size() - 1);
        return ans;
    }
};
