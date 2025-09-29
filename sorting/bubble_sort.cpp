#include <bits/stdc++.h>
using namespace std;

void bubble_sort(vector<int>&v,int n) {
    for(int i=0; i<n-1; i++) {
        bool flag=false;
        for(int j=0; j<n-i-1; j++) {
            if(v[j]>v[j+1]) {
                swap(v[j],v[j+1]);
                flag=true;
            }
        }
        if(!flag) break;
    }
}


int main() {


    int n; cin>>n;
    vector<int>v(n);
    for(int i=0; i<n; i++) cin>>v[i];
    bubble_sort(v,n);
    for(int i=0; i<n; i++) cout << v[i] << " ";
    cout << "\n";
    

    return 0;
}
