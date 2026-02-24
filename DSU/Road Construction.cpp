#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct DSU {
  vector<int> par, rnk, sz;
  int c,mx=0;
  DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) {
    return (par[i] == i ? i : (par[i] = find(par[i])));
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }
  int get_size(int i) {
    return sz[find(i)];
  }
  int count() {
    return c;    //connected components
  }
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j;
    sz[j] += sz[i];
    mx=max(mx,sz[j]);
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};

int32_t main() {

    int n,m; cin>>n>>m;
    DSU d(n+1);
    while(m--) {
        int u,v; cin>>u>>v;
        d.merge(u,v);
        cout << d.count()-1 << " " << d.mx << "\n";
    }


  return 0;
}
