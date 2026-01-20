#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define ll long long
#define nl '\n'


int w;

template<typename T>
class Segment {

public:
    int n;
    vector<T> tree;

    T merge_val(T a, T b) {
        if (a == w) return a;
        else if (b == w) return b;
        else return min(a, b);
    }

    void maintain(int node) {
        tree[node] = merge_val(tree[node*2], tree[node*2+1]);
    }

    void update(int node, int l, int r, int i, T val) {
        if (l == r) {
            tree[node] += val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(node*2, l, m, i, val);
        else update(node*2+1, m+1, r, i, val);
        maintain(node);
    }

    T query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int m = (l + r) / 2;
        if (qr <= m) return query(node*2, l, m, ql, qr);
        if (ql > m) return query(node*2+1, m+1, r, ql, qr);
        T l_res = query(node*2, l, m, ql, qr);
        T r_res = query(node*2+1, m+1, r, ql, qr);
        return merge_val(l_res, r_res);
    }

public:

    Segment(int n) : n(n), tree(4 * n) {}

    void update(int i, T val) {
        update(1, 1, n, i, val);
    }

    T query(int ql, int qr) {
        return query(1, 1, n, ql, qr);
    }

    T get(int i) {
        return query(1, 1, n, i, i);
    }
};

void solve() {
    int n; cin >> n >> w;
    int m = 1 << n;
    Segment<int> seg(m);
    int cur = w;
    for (int i = 1; i <= m; i++) {
        seg.update(i, cur);
        cur = (cur+1 - 1) % m + 1;
    } 
    
    auto& arr = seg.tree;
    for (int i = 1; i < (1 << n+1); i++)
    {
        cout << arr[i] << " ";
    }
    cout << nl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t; cin >> t;
    while (t--) solve();
}
