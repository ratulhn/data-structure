#include <bits/stdc++.h>
using namespace std;

void selection_sort(vector<int>&v,int n) {
    for(int i=0; i<n-1; i++) {
        int idx=i;
        for(int j=i+1; j<n; j++) {
            if(v[j]<v[idx]) idx=j;
        }
        swap(v[i],v[idx]);
    }
}


int main() {


    int n; cin>>n;
    vector<int>v(n);
    for(int i=0; i<n; i++) cin>>v[i];
    selection_sort(v,n);
    for(int i=0; i<n; i++) cout << v[i] << " ";
    cout << "\n";
    

    return 0;
}
