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

    int n,m; cin>>n>>m;
    DSU d(n);

    vector<pair<int,int>>pr(m);

    for(int i=0; i<m; i++) {
        cin>>pr[i].first>>pr[i].second;
        pr[i].first--;pr[i].second--;
    }
    int k; cin>>k;
    vector<int>qr(k);
    vector<bool>active(m,1);

    for(int i=0; i<k; i++) {
        cin>>qr[i];qr[i]--;
        active[qr[i]]=0;
    }

    for(int i=0; i<m; i++) {
        if(!active[i]) continue;
        d.merge(pr[i].first,pr[i].second);
    }
    vector<int>res;
    for(int i=k-1; i>=0; i--) {
        res.push_back(d.count());
        d.merge(pr[qr[i]].first,pr[qr[i]].second);
    }
    reverse(res.begin(),res.end());
    for(auto &x:res) cout << x << " ";
    cout << "\n";



  return 0;
}
