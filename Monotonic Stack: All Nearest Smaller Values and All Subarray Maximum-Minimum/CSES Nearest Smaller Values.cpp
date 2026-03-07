/*=====================================================================

    ██████╗  ██████╗ ██████╗ ███████╗
   ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝
   ██║      ██║   ██║██║  ██║█████╗
   ██║      ██║   ██║██║  ██║██╔══╝
   ╚██████╗ ╚██████╔╝██████╔╝███████╗
    ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝

-----------------------------------------------------------------------

    Problem Name : Nearest Smaller Values
    Problem Link : https://cses.fi/problemset/task/1645/
    Platform     : CSES Problem Set

-----------------------------------------------------------------------

    Author       : Md. Ratul Hossain
    CF Handle    : Phantom_R
    University   : Comilla University (CSE)
    Github       : https://github.com/ratulhn

-----------------------------------------------------------------------

    Technique    : Monotonic Stack
    Idea         :
        Maintain a stack of indices where values are strictly increasing.
        For each element, pop elements from the stack until a smaller
        element appears. The top of the stack becomes the answer.

-----------------------------------------------------------------------

    Complexity
        Time  : O(N)
        Space : O(N)

-----------------------------------------------------------------------

    Notes:
        Classic "Previous Smaller Element" problem.
        Useful pattern for stack-based array problems.

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
    vector<int>res(n+1);
    vector<int>st;

    for(int i=1; i<=n; i++) {
        while(!st.empty() && v[st.back()]>=v[i]) st.pop_back();
        if(st.empty()) res[i]=0;
        else res[i]=st.back();
        st.push_back(i);
    }

    for(int i=1; i<=n; i++) cout << res[i] << " ";
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
