#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> 
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // find_by_order, order_of_key

#define FastIO ios::sync_with_stdio(false);cin.tie(nullptr);
#define dbg(v) cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << "\n";
//#include "dbgtest.h"
#define ll long long
#define all(v) v.begin(),v.end()
#define nl cout<<'\n'
#define lp(i,a,n) for(int i=a; i<n; i++)

const int M = 1e9+7;

void solve() {

    int n,q; cin>>n>>q;
    vector<ll>v(n); lp(i,0,n) cin>>v[i];

    int blocksize = sqrt(n)+1;
    vector<ll>blockAdd(blocksize+1,0);

    while(q--) {
        int t; cin>>t;
        if(t==1) {
            int l,r,u; cin>>l>>r>>u;
            --l;r--;
            int start = l/blocksize;
            int end = r/blocksize;
            if(start==end) {
                for (int i = l; i <= r; i++) v[i] += u;
            } else {
                int endofStart = (start+1)*blocksize-1;
                for(int i=l; i<=min(r,endofStart); i++) v[i]+=u;
                for(int i=start+1; i<end; i++) blockAdd[i]+=u;
                for(int i=end*blocksize; i<=r; i++) v[i]+=u;
            }
        } else {
            int k; cin>>k;
            k--;
            cout << v[k]+blockAdd[k/blocksize] << "\n";
        }
    }


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
