class ST{
private:
    typedef struct node{
        int sum;
        int tag;
    }Node;

    int n;
    vector<Node> arr;
    vector<int> d;
public:
    ST(int _n):n(_n), arr(n * 4) {}

    void push_up(int p){
        arr[p].sum = arr[p*2].sum + arr[p*2 + 1].sum;
    }

    void build(int p, int l, int r){
        arr[p].tag = 0;
        if(l == r){
            arr[p].sum = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(p*2, l, mid);
        build(p*2 + 1, mid + 1, r);
        push_up(p);
    }

    void pd(int p, int l, int r){
        arr[p].sum += arr[p/2].tag * (r - l + 1);
        arr[p].tag += arr[p/2].tag;
    }

    void push_down(int p, int l, int r){
        int mid = (l + r) >> 1;
        pd(p*2, l, mid);
        pd(p*2 + 1, mid + 1, r);
        arr[p].tag = 0;
    }

    void update(int nl, int nr, int l, int r, int p, int k){
        if(nl > nr || l > r) return;
        if(nl <= l && r <= nr){
            arr[p].sum += k * (r - l + 1);
            arr[p].tag += k;
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if(nl <= mid) update(nl, nr, l, mid, p*2, k);
        if(nr > mid) update(nl, nr, mid + 1, r, p*2 + 1, k);
        push_up(p);
    }

    int query(int nl, int nr, int l, int r, int p){
        if(nl > nr || l > r) return 0;
        if(nl <= l && r <= nr) return arr[p].sum;
        int res = 0;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if(nl <= mid) res += query(nl, nr, l, mid, p*2);
        if(nr > mid) res += query(nl, nr, mid + 1, r, p*2 + 1);
        return res; 
    }

    void discrete(vector<int>& nums){
        d.assign(nums.begin(), nums.end());
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
    }

    int getId(int x){
        return lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
};

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        for(int i = 0; i < nums1.size(); i ++){
            nums1[i] -= nums2[i];
        }
        vector<int> d = nums1;
        for(auto& x : nums1){
            d.push_back(x + diff);
        } 
        int n = d.size();
        ST st(n);
        st.build(1, 1, n);
        st.discrete(d);
        long long ans = 0;
        for(int i = 0; i < nums1.size(); i ++){
            int id = st.getId(nums1[i] + diff);
            ans += st.query(1, id, 1, n, 1);
            int id2 = st.getId(nums1[i]);
            st.update(id2, id2, 1, n, 1, 1);
        }
        return ans;
    } 
};
