#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct DSU {
  vector<long long> par, sz;
  int c;
  DSU(int n) : par(n + 1), sz(n + 1, 0), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) {
    if(par[i] == i) return i;
    int b = par[i];
    par[i] = find(par[i]);
    if(b!=par[i])
    sz[i]+=sz[b];
    return par[i];
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }
  void add(int i, int val) {
    sz[find(i)]+=val;
  }
  long long get_size(int i) {
    find(i);
    return (par[i]==i?sz[i]:sz[find(i)]+sz[i]);
  }
  int count() {
    return c;    //connected components
  }
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    par[i] = j;

    sz[i]-=sz[j];

    return j;
  }
};

int32_t main() {

    int n,m; cin>>n>>m;
    DSU d(n+1);


    for(int i=0; i<m; i++) {
        string t; cin>>t;
        if(t=="join") {
            int u,v; cin>>u>>v;
            d.merge(u,v);
        } else if(t=="add") {
            int x,val; cin>>x>>val;
            d.add(x,val);
        } else {
            int x; cin>>x;
            cout << d.get_size(x) << "\n";
        }
    }





  return 0;
}
