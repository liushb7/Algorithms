class Solution {
public:
    vector<int> counts;
    vector<int> index;;

    void mergeSort(vector<int>& nums, int l, int r){
        if(l >= r) return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1;
        vector<int> temp, tempIndex;
        // 注意这里的条件不是i <= mid && j <= r啊！
        while(i <= mid){
            while(j <= r && nums[i] > nums[j]) j++;
            counts[index[i]] += j - (mid + 1);
            i++;
        }
        i = l, j = mid + 1;
        while(i <= mid && j <= r){
            if(nums[i] <= nums[j]){
                temp.push_back(nums[i]);
                tempIndex.push_back(index[i++]);
            }else{
                temp.push_back(nums[j]);
                tempIndex.push_back(index[j++]);
            }
        }
        while(i <= mid){
            temp.push_back(nums[i]);
            tempIndex.push_back(index[i++]);
        }
        while(j <= r){
            temp.push_back(nums[j]);
            tempIndex.push_back(index[j++]);
        }
        for(int i = l; i <= r; i++){
            nums[i] = temp[i - l];
            index[i] = tempIndex[i - l];
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        counts.resize(n);
        index.resize(n);
        for(int i = 0; i < n; i++){
            index[i] = i;
        }
        mergeSort(nums, 0, n - 1);
        return counts;
    }
};
