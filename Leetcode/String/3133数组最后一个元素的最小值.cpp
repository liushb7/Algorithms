class Solution {
public:
    long long minEnd(int n, int x) {
        n -= 1;
        long long ans = x;
        int i = 0, j = 0;
        // n >> j不为零表示还未遍历完n的所有比特位
        while(n >> j){
            // 当ans的第i位为0（其实就是x的第i位为0）
            if((ans >> i & 1) == 0){
                // 将ans的第i位设置为n的第j个比特位
                ans |= (long long)(n >> j & 1) << i;
                j++;
            } 
            i++;
        }
        return ans;
    }
};

// 可以将复杂度从O(log n) + O(log x)优化到O(log n)
class Solution {
public:
    long long minEnd(int n, int x) {
        n--;
        long long ans = x, lowbit, t = ~x, bit;
        int j = 0;
        while(n >> j){
            lowbit = t & -t;
            bit = n >> j & 1;
            ans |= bit * lowbit;
            t -= lowbit;
            j++;
        }
        return ans;
    }
};

