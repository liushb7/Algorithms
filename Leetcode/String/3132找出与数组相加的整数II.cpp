// 本质就是判断子序列问题, 见392

class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        for(int i = 2; i >= 0; i --){
            int d = nums2[0] - nums1[i];
            
            int k = 0;
            for(int j = i; j < nums1.size(); j ++){
                if(nums2[k] == nums1[j] + d){
                    k++;
                    if(k == nums2.size()){
                        return d;
                    }
                }
            }
        }
        
        return 0;
    }
};
