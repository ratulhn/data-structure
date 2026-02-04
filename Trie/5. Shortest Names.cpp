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




 // usage: Trie tr;

struct Trie {
    struct Node {
        Node* nxt[26];
        int pref_cnt, depth_cnt;

        Node(int n) {
            for (int i = 0; i < 26; i++) nxt[i] = nullptr;
            pref_cnt =0, depth_cnt = n;
        }
    };

    Node* root;

    Trie() {
        root = new Node(0);
    }

    // Insert a word
    void insert(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch])
                cur->nxt[ch] = new Node(cur->depth_cnt+1);
            cur = cur->nxt[ch];
            cur->pref_cnt++;
        }
    }

 // Count words starting with prefix
    int starts_with(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            cur = cur->nxt[ch];
            if (cur->pref_cnt<=1) return cur->depth_cnt;
        }
     return cur->depth_cnt;
    }


    // Free memory
    void del(Node* cur) {
        for (int i = 0; i < 26; i++)
            if (cur->nxt[i])
                del(cur->nxt[i]);
        delete cur;
    }

    ~Trie() {
        del(root);
    }
};





void solve() {

    int n; cin>>n;
    vector<string>v(n);
    Trie tr;
    for(int i=0; i<n; i++) {
        cin>>v[i];
        tr.insert(v[i]);
    }

    ll res=0;

    for(int i=0; i<n; i++) {
        res+=tr.starts_with(v[i]);
    }
    cout << res << "\n";
}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
