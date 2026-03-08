/*=====================================================================

    ██████╗  ██████╗ ██████╗ ███████╗
   ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝
   ██║      ██║   ██║██║  ██║█████╗
   ██║      ██║   ██║██║  ██║██╔══╝
   ╚██████╗ ╚██████╔╝██████╔╝███████╗
    ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝

-----------------------------------------------------------------------

    Problem Name : [Problem Name]
    Problem Link : [Problem URL]
    Platform     : [CSES / Codeforces / AtCoder / etc]

-----------------------------------------------------------------------

    Author       : Md. Ratul Hossain
    CF Handle    : Phantom_R
    University   : Comilla University (CSE)
    Github       : https://github.com/ratulhn

-----------------------------------------------------------------------

    Technique    : [Algorithm / Data Structure]
    Idea         :
        - [Main observation]
        - [Key trick / property]
        - [How solution works]

-----------------------------------------------------------------------

    Complexity
        Time  : O(?)
        Space : O(?)

-----------------------------------------------------------------------

    Tags:
        #DSA #Stack #Graph #DP #Greedy #BinarySearch #Math

-----------------------------------------------------------------------

    Notes:
        - [Important observation]
        - [Edge cases]
        - [Anything to remember later]

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

    int n,k,x,a,b,c; cin>>n>>k>>x>>a>>b>>c;

    vector<int>v(n+1);

    for(int i=1; i<=n; i++) {
        if(i==1) v[i]=x;
        else v[i] = (a*1ll*v[i-1]+b)%c;
    }

    deque<int>dq;
    int res=0;
    for(int i=1; i<=n; i++) {
        while(!dq.empty() && v[dq.back()]>v[i]) dq.pop_back();
        while(!dq.empty()&&(i-dq.front()+1>k)) dq.pop_front();
        dq.push_back(i);
        if(i>=k) res^=v[dq.front()];
    }

    cout << res << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
