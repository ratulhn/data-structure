#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct DSU {
  vector<int> par;
  vector<pair<int,int>>com;
  set<int>p;
  int c;
  DSU(int n) : par(n + 1), c(n) {
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
        p.insert(i);
    }
  }
  int find(int i) {
    return (par[i] == i ? i : (par[i] = find(par[i])));
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }

  void close() {
    cout << com.back().first << " " << com.back().second << " ";
    com.pop_back();
    int u=*p.begin();p.erase(p.begin());
    int v=*p.begin();
    cout << u << " " << v << "\n";
  }
  
  int count() {
    return c;    //connected components
  }
  void loop(int i, int j) {
    com.push_back({i,j});
  }
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) {
        return -1;
    }
    else --c;
    
    par[i] = j;
    p.erase(i);
    p.insert(j);
    
    return j;
  }
};

int32_t main() {

    int n; cin>>n;
    DSU d(n);
    
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        int x = d.merge(u,v);
        if(x==-1) {
            d.loop(u,v);
        }
    }

    cout <<d.count()-1 << "\n";

    for(int i=0; i<d.count()-1; i++) {
        d.close();
    }



  return 0;
}
