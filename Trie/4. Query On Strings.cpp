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






const int N=1e5+10;

multiset<int>st[N];
string a[N];

 // usage: Trie tr;

struct Trie {
    struct Node {
        Node* nxt[26];
        int pref_cnt, depth;

        Node(int n) {
            for (int i = 0; i < 26; i++) nxt[i] = nullptr;
            pref_cnt =0, depth = n;
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
                cur->nxt[ch] = new Node(cur->depth+1);
            cur = cur->nxt[ch];
            if(cur->pref_cnt) {
                st[cur->depth].erase(st[cur->depth].find(cur->pref_cnt));
            }
            cur->pref_cnt++;
            st[cur->depth].insert(cur->pref_cnt);
        }
    }

    // Erase one occurrence of a word (safe if guaranteed to exist)
    void erase(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            cur = cur->nxt[ch];
            st[cur->depth].erase(st[cur->depth].find(cur->pref_cnt));
            cur->pref_cnt--;
            st[cur->depth].insert(cur->pref_cnt);
        }
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
    Trie tr;
    for(int i=0; i<n; i++) {
        int op; cin>>op;
        if(op==1) {
            cin>>a[i];
            reverse(a[i].begin(),a[i].end());
            tr.insert(a[i]);
        } else if(op==2) {
            int k,l; cin>>k>>l;
            if(!st[l].empty() && *st[l].rbegin()>=k) cout << "YES\n";
            else cout << "NO\n";
        } else {
            int pos; cin>>pos; pos--;
            if(!a[pos].empty()) {
                tr.erase(a[pos]);
                a[pos].clear();
            }
        }
    }


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
