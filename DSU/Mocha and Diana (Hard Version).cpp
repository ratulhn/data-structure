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
    vector<int>s1,s2;
    for(int i=2; i<=n; i++) {
        if(!d1.same(i,1)&&!d2.same(i,1)) {
            pr.push_back({i,1});
            d1.merge(i,1);
            d2.merge(i,1);
        }
        if(!d1.same(i,1)) s1.push_back(i);
        if(!d2.same(i,1)) s2.push_back(i);
    }

    while(!s1.empty()&& !s2.empty()) {
        if(d1.same(s1.back(),1)&&d2.same(s1.back(),1)) {
            s1.pop_back();continue;
        }
        if(d1.same(s2.back(),1)&&d2.same(s2.back(),1)) {
            s2.pop_back();continue;
        }
        pr.push_back({s1.back(),s2.back()});
        d1.merge(s1.back(),s2.back());
        d2.merge(s1.back(),s2.back());
    }

    cout << pr.size() << "\n";
    for(auto &[x,y]:pr) cout << x << " " << y << "\n";


  return 0;
}
