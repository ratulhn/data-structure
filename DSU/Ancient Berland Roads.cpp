#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct DSU {
  vector<long long> par, rnk, sz;
  int c;
  multiset<long long>mx;
  DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 0), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  void set(int i, int val) {
    sz[i]=val;
    mx.insert(val);
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
  void opt_red(int i, int val) {
    mx.erase(mx.find(sz[find(i)]));
    sz[find(i)]-=val;
  }
  void opt_add(int i, int val) {
    sz[find(i)]+=val;
    mx.insert(sz[find(i)]);
  }
  
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j;
    mx.erase(mx.find(sz[i]));
    mx.erase(mx.find(sz[j]));
    sz[j]+=sz[i];
    mx.insert(sz[j]);
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};

int32_t main() {


  int n,m,q; cin>>n>>m>>q;
  DSU d(n+1);
  vector<int>pre[n+1];
  for(int i=1; i<=n; i++) {
    int x; cin>>x;
    pre[i].push_back(x);
  }

  vector<pair<int,int>>adj(m+1);

  for(int i=1; i<=m; i++) cin>>adj[i].first>>adj[i].second;

  vector<array<int,3>>qr(q);
  vector<bool>active(m+1,true);
  for(int i=0; i<q; i++) {
    char ch; cin>>ch;
    if(ch=='P') {
      int x,y; cin>>x>>y;
      pre[x].push_back(y);
      qr[i]={1,x,y};
    } else {
      int x; cin>>x;
      qr[i]={2,x,-1};
      active[x]=false;
    }
  }

  for(int i=1; i<=n; i++) {
    d.set(i,pre[i].back());
  }

  for(int i=1; i<=m; i++) {
    if(!active[i]) continue;
    
    d.merge(adj[i].first,adj[i].second);
  }
  vector<long long>ans;
  for(int i=q-1; i>=0; i--) {
    ans.push_back(*d.mx.rbegin());

    if(qr[i][0]==1) {
      int pos=qr[i][1];
      int val=qr[i][2];
      d.opt_red(pos,val);
      pre[pos].pop_back();
      d.opt_add(pos,pre[pos].back());
    } else {
      int pos=qr[i][1];
      d.merge(adj[pos].first,adj[pos].second);
    }
    
  }

  reverse(ans.begin(),ans.end());

  for(auto &x:ans) cout << x << "\n";


  return 0;
}
