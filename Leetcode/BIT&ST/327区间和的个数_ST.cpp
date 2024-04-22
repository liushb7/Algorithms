class ST{
private:
    typedef struct node{
        long long sum;
        long long tag;
    }Node;

    long long n;
    vector<Node> arr;
    vector<long long> d;
public:
    ST(long long _n):n(_n), arr(n * 4) {}

    void push_up(long long p){
        arr[p].sum = arr[p*2].sum + arr[p*2 + 1].sum;
    }

    void build(long long p, long long l, long long r){
        arr[p].tag = 0;
        if(l == r){
            arr[p].sum = 0;
            return;
        }
        long long mid = (l + r) >> 1;
        build(p*2, l, mid);
        build(p*2 + 1, mid + 1, r);
        push_up(p);
    }

    void pd(long long p, long long l, long long r){
        arr[p].sum += arr[p/2].tag * (r - l + 1);
        arr[p].tag += arr[p/2].tag;
    }

    void push_down(long long p, long long l, long long r){
        long long mid = (l + r) >> 1;
        pd(p*2, l, mid);
        pd(p*2 + 1, mid + 1, r);
        arr[p].tag = 0;
    }

    void update(long long nl, long long nr, long long l, long long r, long long p, long long k){
        if(nl > nr || l > r) return;
        if(nl <= l && r <= nr){
            arr[p].sum += k * (r - l + 1);
            arr[p].tag += k;
            return;
        }
        push_down(p, l, r);
        long long mid = (l + r) >> 1;
        if(nl <= mid) update(nl, nr, l, mid, p*2, k);
        if(nr > mid) update(nl, nr, mid + 1, r, p*2 + 1, k);
        push_up(p);
    }

    long long query(long long nl, long long nr, long long l, long long r, long long p){
        if(nl > nr || l > r) return 0;
        if(nl <= l && r <= nr) return arr[p].sum;
        long long res = 0;
        push_down(p, l, r);
        long long mid = (l + r) >> 1;
        if(nl <= mid) res += query(nl, nr, l, mid, p*2);
        if(nr > mid) res += query(nl, nr, mid + 1, r, p*2 + 1);
        return res; 
    }

    void discrete(vector<long long>& nums){
        d.assign(nums.begin(), nums.end());
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
    }

    long long getId(long long x){
        return lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
};


class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long> d;
        vector<long long> pre;
        pre.push_back(0);
        long long s = 0;
        for(auto& x : nums){
            s += x;
            pre.push_back(s);
        }
        for(auto& x : pre){
            d.push_back((long long)x);
            d.push_back((long long)x - lower);
            d.push_back((long long)x - upper);
        }
        int N = d.size();
        ST st(N);
        st.build(1, 1, N);
        st.discrete(d);
        int ans = 0;
        for(int i = 0; i < pre.size(); i ++){
            int id_left = st.getId(pre[i] - upper);
            int id_right = st.getId(pre[i] - lower);
            ans += st.query(id_left, id_right, 1, N, 1);
            int id = st.getId(pre[i]);
            st.update(id, id, 1, N, 1, 1);
        }
        return ans;
    }
};
