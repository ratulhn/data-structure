class Solution {
public:
    vector<int>seg;
    void build(int i, int l, int r, vector<int>&v) {
        if(l==r) {
            seg[i]=v[l]; return;
        }
        int mid=l+(r-l)/2;
        build(2*i+1,l,mid,v);
        build(2*i+2,mid+1,r,v);
        seg[i]=max(seg[2*i+1],seg[2*i+2]);
    }
    bool query(int i, int l, int r, int val) {
        if(seg[i]<val) return false;
        if(l==r) {
            seg[i]=-1;
            return true;
        }
        int mid=l+(r-l)/2;
        bool ok=false;
        if(seg[2*i+1]>=val) {
            ok=query(2*i+1,l,mid,val);
        } else {
            ok=query(2*i+2,mid+1,r,val);
        }
        seg[i]=max(seg[2*i+1],seg[2*i+2]);
        return ok;
    }
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n=fruits.size();
        seg.resize(4*n);
        build(0,0,n-1,baskets);
        int cnt=0;
        for(int i=0; i<n; i++) {
            if(!query(0,0,n-1,fruits[i])) cnt++;
        }
        return cnt;
    }
};
