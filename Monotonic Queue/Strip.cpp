/*=====================================================================

    ██████╗  ██████╗ ██████╗ ███████╗
   ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝
   ██║      ██║   ██║██║  ██║█████╗
   ██║      ██║   ██║██║  ██║██╔══╝
   ╚██████╗ ╚██████╔╝██████╔╝███████╗
    ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝

-----------------------------------------------------------------------

    Problem Name : Strip
    Problem Link : https://codeforces.com/contest/488/problem/D
    Platform     : Codeforces

-----------------------------------------------------------------------

    Author       : Md. Ratul Hossain
    CF Handle    : Phantom_R
    University   : Comilla University (CSE)
    Github       : https://github.com/ratulhn

-----------------------------------------------------------------------

    Technique    : Algorithm / Data Structure / dp
    Idea         :
        Idea :

            1. Let f[i] = minimum number of pieces to cover the prefix [1..i].

            2. Let g[i] = maximum length of a valid segment ending at i
            such that (max - min ≤ s).

            3. The last piece ending at i must satisfy:
                    l ≤ length ≤ g[i]

                    If the previous cut is at k:
                            piece = [k+1 ... i]
                            length = i - k

                    So:
                            i - g[i] ≤ k ≤ i - l

            4. Therefore:
                    f[i] = min(f[k]) + 1
                    where i-g[i] ≤ k ≤ i-l

            5. g[i] is computed using a sliding window with two deques
            maintaining minimum and maximum.

            6. Another monotonic queue is used to maintain
                    min(f[k]) over the sliding range.

-----------------------------------------------------------------------

    Complexity
        Time  : O(?)
        Space : O(?)

-----------------------------------------------------------------------

    Tags:
        #DSA #Stack #Graph #DP #Greedy #BinarySearch #Math

-----------------------------------------------------------------------

    Notes:
        Notes:

        - Key observation: the valid split point k forms a sliding range
            [i-g[i], i-l].

        - Maintain minimum f[k] in this range using a monotonic deque.

        - Two classic techniques combined:
            1) Sliding window for max/min
            2) DP with monotonic queue optimization.

        - If l > g[i], then f[i] cannot be updated.
        
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

    int n,s,l; cin>>n>>s>>l;
    vector<int>v(n+1);
    for(int i=1; i<=n; i++) cin>>v[i];
    vector<int>g(n+1);
    deque<int>dm,dx;
    int k=1;
    for(int i=1; i<=n; i++) {
        while(!dm.empty()&&v[dm.back()]>=v[i]) dm.pop_back();
        while(!dx.empty()&&v[dx.back()]<=v[i]) dx.pop_back();

        dm.push_back(i);
        dx.push_back(i);

        while(v[dx.front()]-v[dm.front()]>s) {
            if(dm.front()==k) dm.pop_front();
            if(dx.front()==k) dx.pop_front();
            k++;
        }
        g[i]=i-k+1;
    }
    
    vector<int>f(n+1,M);

    f[0]=0;
    deque<int>dq;
    for(int i=1; i<=n; i++) {
        if(i-l>=0) {
            k = i-l;
            if(f[k]!=M) {
                while(!dq.empty()&&f[dq.back()]>=f[k]) dq.pop_back();
                dq.push_back(k);
            }
        }
        while(!dq.empty()&&dq.front()<i-g[i]) dq.pop_front();
        if(!dq.empty()) f[i] = f[dq.front()]+1;
    }
    if(f[n]==M) cout << "-1\n";
    else cout << f[n] << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
