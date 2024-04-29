// 设坐标为 (i,j)(i,j)(i,j)，设 k=i−jk=i-jk=i−j。

// 第一条对角线上只有一个点，坐标为 (0,n−1)(0,n-1)(0,n−1)，其 k=1−nk=1-nk=1−n。
// 最后一条对角线上也只有一个点，坐标为 (m−1,0)(m-1,0)(m−1,0)，其 k=m−1k=m-1k=m−1。
// 所以枚举对角线，就是枚举 kkk 从 1−n1-n1−n 到 m−1m-1m−1。
// 对于同一条对角线，知道行下标 iii 就知道列下标 j=i−kj=i-kj=i−k。

// iii 的最小值：令等式 k=i−jk=i-jk=i−j 中的 j=0j=0j=0，可得 i=ki=ki=k，但 iii 必须是非负数，所以 iii 最小为 max⁡(k,0)\max(k, 0)max(k,0)。
// iii 的最大值：令等式 k=i−jk=i-jk=i−j 中的 j=n−1j=n-1j=n−1，可得 i=k+n−1i=k+n-1i=k+n−1，但 iii 至多为 m−1m-1m−1，所以 iii 最大为 min⁡(k+n−1,m−1)\min(k+n-1, m-1)min(k+n−1,m−1)。
// 枚举 iii，范围为左闭右开区间 [max⁡(k,0),min⁡(k+n,m))[\max(k, 0),\min(k+n, m))[max(k,0),min(k+n,m))。
// 把 mat[i][i−k]\textit{mat}[i][i-k]mat[i][i−k] 加入一个数组，把数组从小到大排序后，再依次填入 mat[i][i−k]\textit{mat}[i][i-k]mat[i][i−k]，即完成了这条对角线的排序。

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<int> a(min(m, n));
        for (int k = 1 - n; k < m; k++) { // k = i - j
            int left_i = max(k, 0), right_i = min(k + n, m);
            for (int i = left_i; i < right_i; i++) {
                a[i - left_i] = mat[i][i - k];
            }
            sort(a.begin(), a.begin() + (right_i - left_i));
            for (int i = left_i; i < right_i; i++) {
                mat[i][i - k] = a[i - left_i];
            }
        }
        return mat;
    }
};
