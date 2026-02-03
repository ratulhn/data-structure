#include <bits/stdc++.h>
using namespace std;

#define FastIO ios::sync_with_stdio(false); cin.tie(nullptr);

struct Trie {
    struct Node {
        Node* nxt[26];
        int best_cnt, end_cnt;
        string best_word;

        Node() {
            for (int i = 0; i < 26; i++) nxt[i] = nullptr;
            best_cnt = end_cnt = 0;
            best_word = "";
        }
    };

    Node* root;

    Trie() {
        root = new Node();
    }

    // Insert word
    void insert(const string &s) {
        Node* cur = root;
        vector<Node*> path;

        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch])
                cur->nxt[ch] = new Node();
            cur = cur->nxt[ch];
            path.push_back(cur);
        }

        cur->end_cnt++;
        int freq = cur->end_cnt;

        // Update best word for all prefixes
        for (auto &node : path) {
            if (node->best_cnt < freq ||
               (node->best_cnt == freq && node->best_word > s)) {
                node->best_cnt = freq;
                node->best_word = s;
            }
        }
    }

    // Query best autocomplete for prefix
    void starts_with(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch]) {
                cout << "-1\n";
                return;
            }
            cur = cur->nxt[ch];
        }
        cout << cur->best_word << " " << cur->best_cnt << "\n";
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

int main() {
    FastIO

    int n;
    cin >> n;

    Trie tr;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        tr.insert(s);
    }

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        tr.starts_with(s);
    }

    return 0;
}
