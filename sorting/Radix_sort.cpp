#include <bits/stdc++.h>
using namespace std;

void counting_sort(vector<int>&v,int exp) {
    vector<int>f(10,0);
    int n=v.size();
    for(int i=0; i<n; i++) {
        ++f[(v[i]/exp)%10];
    }
    for(int i=1; i<10; i++) f[i]+=f[i-1];
    vector<int>res(n);
    for(int i=n-1; i>=0; i--) {
        int id=(v[i]/exp)%10;
        res[f[id]-1]=v[i];
        f[id]--;
    }
    for(int i=0; i<n; i++) {
        v[i]=res[i];
    }
}

void radix_sort(vector<int>&v) {
    int max_val = *max_element(v.begin(),v.end());

    for(int i=1; max_val/i>0; i*=10) {
        counting_sort(v,i);
    }
}


int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    radix_sort(v);
    
    for(int i=0; i<n; i++) cout << v[i] << " ";
    cout << "\n";

    return 0;
}
