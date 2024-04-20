
class ST{
private:
    typedef struct node{
        int sum;
        int tag;
    }Node;

    int n;
    vector<Node> arr;
public:
    ST(int _n):n(_n + 10), arr(n * 4) {}

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
        int ans = 0;
        if(nl > nr || l > r) return 0;
        if(nl <= l && r <= nr){
            return arr[p].sum;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if(nl <= mid) ans += query(nl, nr, l, mid, p*2);
        if(nr > mid) ans += query(nl, nr, mid + 1, r, p*2 + 1);
        return ans;
    }
};

class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        int n = *max_element(instructions.begin(), instructions.end());
        ST st(n);
        st.build(1, 1, n);
        long long ans = 0;
        int mod = 1e9 + 7;
        for(int i = 0; i < instructions.size(); i++){
            int x = instructions[i];
            int lower = st.query(1, x - 1, 1, n, 1);
            int upper = i - st.query(1, x, 1, n, 1);
            // int upper = st.query(x + 1, n, 1, n, 1);
            ans = (ans + min(lower, upper)) % mod;
            st.update(x, x, 1, n, 1, 1);
        }
        return ans;
    }
};

