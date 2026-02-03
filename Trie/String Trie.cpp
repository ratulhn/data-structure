
 // usage: Trie tr;

struct Trie {
    struct Node {
        Node* nxt[26];
        int pref_cnt, end_cnt;

        Node() {
            for (int i = 0; i < 26; i++) nxt[i] = nullptr;
            pref_cnt = end_cnt = 0;
        }
    };

    Node* root;

    Trie() {
        root = new Node();
    }

    // Insert a word
    void insert(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch])
                cur->nxt[ch] = new Node();
            cur = cur->nxt[ch];
            cur->pref_cnt++;
        }
        cur->end_cnt++;
    }

    // Count exact matches of a word
    int equal_to(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch]) return 0;
            cur = cur->nxt[ch];
        }
        return cur->end_cnt;
    }

    // Count words starting with prefix
    int starts_with(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch]) return 0;
            cur = cur->nxt[ch];
        }
        return cur->pref_cnt;
    }

    // Erase one occurrence of a word (safe if guaranteed to exist)
    void erase(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int ch = c - 'a';
            if (!cur->nxt[ch]) return;
            cur = cur->nxt[ch];
            cur->pref_cnt--;
        }
        cur->end_cnt--;
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




