class Solution {
public:
    long long ans = 0;

    void mergeSort(vector<int>& record, int l, int r){
        if(l >= r) return;
        int mid = (l + r) >> 1;
        mergeSort(record, l, mid);
        mergeSort(record, mid + 1, r);
        int i = l, j = mid + 1;
        vector<int> temp;
        while(i <= mid && j <= r){
            if(record[i] <= record[j]){
                temp.push_back(record[i++]);
            }else{
                ans += (mid - i + 1);
                temp.push_back(record[j++]);
            }
        }
        while(i <= mid){
            temp.push_back(record[i++]);
        }
        while(j <= r){
            temp.push_back(record[j++]);
        }
        for(int i = l; i <= r; i++){
            record[i] = temp[i - l];
        }
    }

    int reversePairs(vector<int>& record) {
        mergeSort(record, 0, record.size() - 1);
        return ans;
    }
};
