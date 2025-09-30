#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int r=*max_element(v.begin(),v.end());
    int l=*min_element(v.begin(),v.end());
    int k=r-l+1;
    vector<int>f(k);
    for(auto &x:v) ++f[x-l];
    for(int i=1; i<k; i++) f[i]+=f[i-1];

    vector<int>ans(n);

    for(int i=n-1; i>=0; i--) {
        int idx = f[v[i]-l]-1;
        ans[idx]=v[i];
        --f[v[i]-l];
    }

    for(int i=0; i<n; i++) cout << ans[i] << " ";
    cout << "\n";
   
    cout << "\n";

    return 0;
}
