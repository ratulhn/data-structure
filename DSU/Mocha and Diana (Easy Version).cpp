#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct DSU {
  vector<int> par, rnk, sz;
  int c;
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
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};

int32_t main() {

    int n,m,k; cin>>n>>m>>k;
    DSU d1(n),d2(n);

    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        d1.merge(u,v);
    }
    for(int i=0; i<k; i++) {
        int u,v; cin>>u>>v;
        d2.merge(u,v);
    }
    vector<pair<int,int>>pr;
    for(int i=1; i<n; i++) {
        for(int j=i+1; j<=n; j++) {
            if(!d1.same(i,j)&&!d2.same(i,j)) {
                pr.push_back({i,j});
                d1.merge(i,j);
                d2.merge(i,j);
            }
        }
    }

    cout << pr.size() << "\n";
    for(auto &[x,y]:pr) cout << x << " " << y << "\n";


  return 0;
}
