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


struct Node {
    Node *links[26];
    int prefix;

    Node() {
        for(int i=0; i<26; i++) links[i]=NULL;
        prefix=0;
    }

    Node* get(char ch) {
        return links[ch-'a'];
    }

    bool contains(char ch) {
        return links[ch-'a']!=NULL;
    }


    void set(char ch, Node *node) {
        links[ch-'a']=node;
    }

    int getPrefix() {
        return prefix;
    }

    void increasePrefix() {
        prefix++;
    }
};

class Trie {
private: Node *root;
public:

    Trie() {
        root = new Node();
    }

    void build(string &word) {
        Node *node=root;
        for(auto ch:word) {
            if(!node->contains(ch)) {
                node->set(ch,new Node());
            }
            node = node->get(ch);
            node->increasePrefix();
        }
    }

    int query(string &word) {
        Node *node = root;
        for(auto ch:word) {
            if(!node->contains(ch)) return 0;
            node = node->get(ch);
        }
        return node->getPrefix();
    }
};





void solve() {

    int n,q; cin>>n>>q;
    Trie t;
    for(int i=0; i<n; i++) {
        string s; cin>>s;
        t.build(s);
    }

    while(q--) {
        string s; cin>>s;
        cout << t.query(s) << "\n";
    }


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
