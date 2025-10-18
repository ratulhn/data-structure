#include <bits/stdc++.h>
using namespace std;

template<typename T, typename U>
struct SegmentTree {
    int n;
    vector<T> tree;
    vector<U> lazy;
    T identity;               // identity element for the operation (e.g., 0 for sum, INF for min)
    U noop;                   // "no operation" value for lazy (e.g., 0 for add, 1 for multiply)

    // Define your merge (combine) operation
    function<T(T, T)> merge;
    // Define how to apply a lazy update to a node value
    function<T(T, U, int)> applyUpdate;
    // Define how to combine two lazy updates
    function<U(U, U)> combineLazy;

    SegmentTree(int size, T _identity, U _noop,
                function<T(T, T)> _merge,
                function<T(T, U, int)> _applyUpdate,
                function<U(U, U)> _combineLazy)
        : n(size), identity(_identity), noop(_noop),
          merge(_merge), applyUpdate(_applyUpdate), combineLazy(_combineLazy) {
        tree.resize(4 * n, identity);
        lazy.resize(4 * n, noop);
    }

    void build(const vector<T>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node, l, mid);
        build(arr, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void push(int node, int l, int r) {
        if (lazy[node] == noop) return;
        tree[node] = applyUpdate(tree[node], lazy[node], r - l + 1);
        if (l != r) {
            lazy[2 * node] = combineLazy(lazy[2 * node], lazy[node]);
            lazy[2 * node + 1] = combineLazy(lazy[2 * node + 1], lazy[node]);
        }
        lazy[node] = noop;
    }

    void updateRange(int node, int l, int r, int ql, int qr, U val) {
        push(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] = combineLazy(lazy[node], val);
            push(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        updateRange(2 * node, l, mid, ql, qr, val);
        updateRange(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    T queryRange(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (ql > r || qr < l) return identity;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        T leftRes = queryRange(2 * node, l, mid, ql, qr);
        T rightRes = queryRange(2 * node + 1, mid + 1, r, ql, qr);
        return merge(leftRes, rightRes);
    }

    // Public interface
    void build(const vector<T>& arr) {
        build(arr, 1, 0, n - 1);
    }

    void update(int l, int r, U val) {
        updateRange(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        return queryRange(1, 0, n - 1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 5;
    vector<long long> arr = {1, 2, 3, 4, 5};

    // Identity for sum = 0, No-op for add = 0
    auto seg = SegmentTree<long long, long long>(
        n,
        0LL,                          // identity
        0LL,                          // noop
        [](long long a, long long b) { return a + b; },               // merge
        [](long long nodeVal, long long upd, int len) { return nodeVal + upd * len; }, // apply
        [](long long lazy1, long long lazy2) { return lazy1 + lazy2; } // combine lazy
    );

    seg.build(arr);

    cout << seg.query(1, 3) << '\n';   // 2+3+4 = 9
    seg.update(1, 3, 10);              // add 10 to [1,3]
    cout << seg.query(1, 3) << '\n';   // 12+13+14 = 39

    return 0;
}
