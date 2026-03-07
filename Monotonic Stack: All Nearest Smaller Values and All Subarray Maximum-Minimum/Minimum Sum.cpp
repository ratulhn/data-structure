/*=====================================================================

    ██████╗  ██████╗ ██████╗ ███████╗
   ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝
   ██║      ██║   ██║██║  ██║█████╗
   ██║      ██║   ██║██║  ██║██╔══╝
   ╚██████╗ ╚██████╔╝██████╔╝███████╗
    ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝

-----------------------------------------------------------------------

    Problem Name : Minimum Sum
    Problem Link : https://atcoder.jp/contests/agc005/tasks/agc005_b
    Platform     : AtCoder

-----------------------------------------------------------------------

    Author       : Md. Ratul Hossain
    CF Handle    : Phantom_R
    University   : Comilla University (CSE)
    Github       : https://github.com/ratulhn

-----------------------------------------------------------------------

    Technique    : Data Structure
    Idea         :
        - Instead of evaluating every interval, compute the contribution of each a[i].
        - For each element a[i], determine how many subarrays have a[i] as the minimum.
        - Find the nearest smallest element on the left (L) and Right (R).
        - a[i] is the minimum for all subarrays starting from (L+1....i)
          and ending at (i....R-1).
        - Number of such subarrays = (i-L)*(R-i)
        - Contribution of a[i] = a[i]*(i-L)*(R-i).
        - Summing all contribution gives the final answer.

-----------------------------------------------------------------------

    Complexity
        Time  : O(N)
        Space : O(N)

-----------------------------------------------------------------------

    Tags:
        #DSA #Stack 

-----------------------------------------------------------------------

    Notes:
        - Using a monotonic stack to efficiently find the nearest smaller element.

=====================================================================*/


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


    int n; cin>>n;
    vector<int>v(n+1);
    for(int i=1; i<=n; i++) cin>>v[i];
    vector<int>pre(n+1),suf(n+1);

    vector<int>st;

    for(int i=1; i<=n; i++) {
        while(!st.empty()&&v[st.back()]>=v[i]) st.pop_back();
        if(st.empty()) pre[i]=0;
        else pre[i]=st.back();
        st.push_back(i);
    }
    st.clear();
    for(int i=n; i>=1; i--) {
        while(!st.empty()&&v[st.back()]>=v[i]) st.pop_back();
        if(st.empty()) suf[i]=n+1;
        else suf[i]=st.back();
        st.push_back(i);
    }

    ll res=0;

    for(int i=1; i<=n; i++) {
        res+=(i-pre[i])*1ll*(suf[i]-i)*1ll*v[i];
    }

    cout << res << "\n";


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
