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

int c=1;
void solve() {
    cout << "Case " << c << ":\n";
    c++;
    string s; cin>>s;
    int n=s.size();
    bool active[n];
    DSU d(n);
    memset(active,1,sizeof(active));

    int q; cin>>q;
    vector<array<int,2>>qr(q);

    for(int i=0; i<q; i++) {
        cin>>qr[i][0]>>qr[i][1];
        if(qr[i][0]==2) active[qr[i][1]]=0;
    }

    for(int i=1; i<n-1; i++) {
        if(active[i] && active[i-1] &&(s[i]==s[i-1]))  d.merge(i,i-1);
        if(active[i] && active[i+1 ]&&(s[i]==s[i+1]))  d.merge(i,i+1);
    }
    vector<int>ans;
    for(int i=q-1; i>=0; i--) {
        if(qr[i][0]==1) {
            ans.push_back( d.get_size(qr[i][1]));
        } else {
            active[qr[i][1]]=1;
            int p=qr[i][1];
            if(p-1>=0 && active[p] && active[p-1] &&(s[p]==s[p-1]))  d.merge(p,p-1);
            if(p+1<n && active[p] && active[p+1 ]&&(s[p]==s[p+1]))  d.merge(p,p+1);
        }
    }

    reverse(ans.begin(),ans.end());

    for(auto &x:ans) cout << x << "\n";

}

int32_t main() {

    int t; cin>>t;
    while(t--) solve();

  return 0;
}
