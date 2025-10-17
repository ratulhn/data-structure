#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Segment Tree with both Range Add and Range Set with Lazy Propagation
struct SegmentTree {
    int n;
    vector<ll> tree;       // Segment tree nodes
    vector<ll> lazyAdd;    // Pending "add" updates
    vector<ll> lazySet;    // Pending "set" updates
    vector<bool> hasLazySet; // Flag: true if "set" is pending

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazyAdd.assign(4 * n, 0);
        lazySet.assign(4 * n, 0);
        hasLazySet.assign(4 * n, false);
    }

    // 🔹 Combine two child nodes (for sum query)
    ll combine(ll a, ll b) {
        return a + b; // For sum; change to min/max/gcd if needed
    }

    // 🔹 Build segment tree from array a[]
    void build(vector<ll> &a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l]; // Leaf node = array value
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * node, l, mid);       // Build left child
        build(a, 2 * node + 1, mid + 1, r); // Build right child
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]); // Merge children
    }
    void build(vector<ll> &a) { build(a, 1, 0, n - 1); }

    // 🔹 Apply "set" to a node
    void applySet(int node, int l, int r, ll val) {
        tree[node] = (r - l + 1) * val; // Total sum = val * number of elements
        lazySet[node] = val;             // Mark pending set
        lazyAdd[node] = 0;               // Remove pending add, because set overrides
        hasLazySet[node] = true;         // Flag indicates "set" is active
    }

    // 🔹 Apply "add" to a node
    void applyAdd(int node, int l, int r, ll val) {
        if (hasLazySet[node]) lazySet[node] += val; // If set pending, add to set value
        else lazyAdd[node] += val;                  // Otherwise, add to lazyAdd
        tree[node] += (r - l + 1) * val;           // Update node sum
    }

    // 🔹 Push pending updates from parent to children
    void push(int node, int l, int r) {
        if (l == r) return; // Leaf node has no children
        int mid = (l + r) / 2;
        int left = node * 2;
        int right = node * 2 + 1;

        if (hasLazySet[node]) {
            // If a set is pending, push it to children
            applySet(left, l, mid, lazySet[node]);
            applySet(right, mid + 1, r, lazySet[node]);
            hasLazySet[node] = false; // Clear current node's set
        }

        if (lazyAdd[node] != 0) {
            // Push pending add to children
            applyAdd(left, l, mid, lazyAdd[node]);
            applyAdd(right, mid + 1, r, lazyAdd[node]);
            lazyAdd[node] = 0; // Clear current node's add
        }
    }

    // 🔹 Range Add Update [ql, qr] += val
    void updateAdd(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || ql > r) return;          // No overlap
        if (ql <= l && r <= qr) {              // Full overlap
            applyAdd(node, l, r, val);         // Apply add directly
            return;
        }
        push(node, l, r);                       // Push pending updates before going down
        int mid = (l + r) / 2;
        updateAdd(2 * node, l, mid, ql, qr, val);       // Update left child
        updateAdd(2 * node + 1, mid + 1, r, ql, qr, val); // Update right child
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]); // Recalculate current node
    }
    void updateAdd(int l, int r, ll val) { updateAdd(1, 0, n - 1, l, r, val); }

    // 🔹 Range Set Update [ql, qr] = val
    void updateSet(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || ql > r) return;           // No overlap
        if (ql <= l && r <= qr) {               // Full overlap
            applySet(node, l, r, val);          // Apply set directly
            return;
        }
        push(node, l, r);                        // Push pending updates before going down
        int mid = (l + r) / 2;
        updateSet(2 * node, l, mid, ql, qr, val);
        updateSet(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]); // Recalculate current node
    }
    void updateSet(int l, int r, ll val) { updateSet(1, 0, n - 1, l, r, val); }

    // 🔹 Range Query [ql, qr]
    ll query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;         // No overlap, return neutral value
        if (ql <= l && r <= qr) return tree[node]; // Full overlap, return node value
        push(node, l, r);                        // Push pending updates to children
        int mid = (l + r) / 2;
        return combine(
            query(2 * node, l, mid, ql, qr),
            query(2 * node + 1, mid + 1, r, ql, qr)
        );
    }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    SegmentTree st(n);
    st.build(a); // Build tree from initial array

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {         // Range Add
            int l, r; ll val;
            cin >> l >> r >> val;
            --l; --r;            // Convert to 0-indexed
            st.updateAdd(l, r, val);
        } else if (type == 2) {  // Range Set
            int l, r; ll val;
            cin >> l >> r >> val;
            --l; --r;
            st.updateSet(l, r, val);
        } else {                  // Range Query
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << st.query(l, r) << "\n";
        }
    }
}
