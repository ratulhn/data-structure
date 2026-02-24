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
   
    par[i] = j;

    return j;
  }
};

int32_t main() {

    int n; cin>>n;
    DSU d(n);

    for(int i=0; i<n; i++) {
        int x; cin>>x; x--;
        int p =  d.find(x);
        cout << p+1 << " ";
        d.merge(x,(p+1)%n);
    }
    

  return 0;
}
