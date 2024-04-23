class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int total = 0, n = customers.size();
        for(int i = 0; i < n; i ++){
            if(grumpy[i] == 0){
                total += customers[i];
            }
        }

        int extra = 0;
        for(int i = 0; i < minutes; i ++){
            extra += (grumpy[i] * customers[i]);
        }
        int maxExtra = extra;
        for(int i = minutes; i < n; i ++){
            extra = extra - grumpy[i - minutes] * customers[i - minutes] + grumpy[i] * customers[i];
            maxExtra = max(maxExtra, extra);
        }
        return total + maxExtra;
    }
};
