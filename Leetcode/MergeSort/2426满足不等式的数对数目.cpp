class Solution {
public:
    long long ans = 0;
    int d;

    void mergeSort(vector<int>& nums, int l, int r){
        if(l >= r) return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1;
        while(j <= r){
            while(i <= mid && nums[i] <= nums[j] + d) i++;
            ans += (i - l);
            j++;
        }
        i = l, j = mid + 1;
        vector<int> temp;
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

    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        vector<int> arr = nums1;
        d = diff;
        for(int i = 0; i < arr.size(); i++){
            arr[i] -= nums2[i];
        }
        mergeSort(arr, 0, arr.size() - 1);
        return ans;
    }
};
