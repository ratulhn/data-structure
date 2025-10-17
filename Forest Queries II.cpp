#include <bits/stdc++.h>
using namespace std;

class SegmentTree2D {
private:
    int n, m;
    vector<vector<int>> tree;

public:
    SegmentTree2D(int n, int m) : n(n), m(m) {
        tree.assign(4*n, vector<int>(4*m, 0));
    }

    // Build the tree
    void build(vector<vector<int>> &grid, int vx, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build(grid, vx*2, lx, mx);
            build(grid, vx*2+1, mx+1, rx);
        }
        buildY(grid, vx, lx, rx, 1, 0, m-1);
    }

    void buildY(vector<vector<int>> &grid, int vx, int lx, int rx, int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = grid[lx][ly]; // leaf
            else
                tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy]; // combine X children
        } else {
            int my = (ly + ry)/2;
            buildY(grid, vx, lx, rx, vy*2, ly, my);
            buildY(grid, vx, lx, rx, vy*2+1, my+1, ry);
            tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1]; // combine Y children
        }
    }

    // Update a single cell (x=row, y=col) to new_val
    void update(int vx, int lx, int rx, int x, int y, int new_val) {
        if (lx != rx) {
            int mx = (lx + rx)/2;
            if (x <= mx) update(vx*2, lx, mx, x, y, new_val);
            else update(vx*2+1, mx+1, rx, x, y, new_val);
        }
        updateY(vx, lx, rx, 1, 0, m-1, x, y, new_val);
    }

    void updateY(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = new_val;
            else
                tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
        } else {
            int my = (ly + ry)/2;
            if (y <= my) updateY(vx, lx, rx, vy*2, ly, my, x, y, new_val);
            else updateY(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
            tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
        }
    }

    // Query rectangle sum from (x1,y1) to (x2,y2)
    int query(int vx, int lx, int rx, int x1, int x2, int y1, int y2) {
        if (x1 > rx || x2 < lx) return 0;
        if (x1 <= lx && rx <= x2) return queryY(vx, 1, 0, m-1, y1, y2);
        int mx = (lx+rx)/2;
        return query(vx*2, lx, mx, x1, x2, y1, y2) + query(vx*2+1, mx+1, rx, x1, x2, y1, y2);
    }

    int queryY(int vx, int vy, int ly, int ry, int y1, int y2) {
        if (y1 > ry || y2 < ly) return 0;
        if (y1 <= ly && ry <= y2) return tree[vx][vy];
        int my = (ly+ry)/2;
        return queryY(vx, vy*2, ly, my, y1, y2) + queryY(vx, vy*2+1, my+1, ry, y1, y2);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> grid(n, vector<int>(n,0));

    // read grid and mark 1 if '*'
    for (int i=0;i<n;i++) {
        string s; cin >> s;
        for (int j=0;j<n;j++)
            grid[i][j] = (s[j] == '*') ? 1 : 0;
    }

    SegmentTree2D seg(n, n);
    seg.build(grid, 1, 0, n-1);

    while(q--) {
        int type; cin >> type;
        if(type==1) {
            int x,y; cin >> x >> y; x--; y--;
            grid[x][y] ^= 1; // toggle
            seg.update(1,0,n-1,x,y,grid[x][y]);
        } else {
            int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;
            cout << seg.query(1,0,n-1,x1,x2,y1,y2) << "\n";
        }
    }
}
