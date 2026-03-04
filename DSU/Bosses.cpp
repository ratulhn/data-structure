#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct DSU {
  vector<int> par, rnk, sz;
  int c;
  DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 0), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) {
    if(par[i] == i) return i;
    int b = par[i];
    par[i] = find(par[i]);
    sz[i]+=sz[b];
    return par[i];
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }
  int get_size(int i) {
    find(i);
    return sz[i];
  }
  int count() {
    return c;    //connected components
  }
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    
    par[i] = j;
    sz[i] = 1;

    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};

int32_t main() {

    int n,m; cin>>n>>m;
    DSU d(n+1);


    for(int i=0; i<m; i++) {
        int t; cin>>t;
        if(t==1) {
            int u,v; cin>>u>>v;
            d.merge(u,v);
        } else {
            int x; cin>>x;
            cout << d.get_size(x) << "\n";
        }
    }





  return 0;
}
