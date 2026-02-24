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

    int n,m,q; cin>>n>>m>>q;

    for(int i=0; i<m; i++) {
        int x,y; cin>>x>>y;
    }

    DSU d(n+1);

    vector<array<int,3>>g(q);

    for(int i=0; i<q; i++) {
        string s; cin>>s;
        int u,v; cin>>u>>v;
    
        if(s=="ask") {
            g[i]={0,u,v};
        } else g[i]={1,u,v};
    }
    vector<string>ans;
    for(int i=q-1; i>=0; i--) {
        if(g[i][0]==0) {
            if(d.same(g[i][1],g[i][2])) ans.push_back("YES");
            else ans.push_back("NO");
        } else d.merge(g[i][1],g[i][2]);
    }

    reverse(ans.begin(),ans.end());
    for(auto &s:ans) cout << s << "\n";

  return 0;
}
