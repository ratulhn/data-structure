class Solution {
public:

    void segUpdate(int i,int l,int r,int pos,vector<int>&seg) {
        if(l==r) {
            seg[i]=1;
            return;
        }
        int mid=l+(r-l)/2;
        if(pos<=mid) {
            segUpdate(2*i+1,l,mid,pos,seg);
        } else {
            segUpdate(2*i+2,mid+1,r,pos,seg);
        }
        seg[i]=seg[2*i+1]+seg[2*i+2];
    }
    int query(int start, int end, int i, int l, int r, vector<int>&seg) {
        if(l>end||r<start) return 0;
        if(l>=start&&r<=end) return seg[i];
        int mid=l+(r-l)/2;
        return query(start,end,2*i+1,l,mid,seg)+query(start,end,2*i+2,mid+1,r,seg);
    }
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        vector<int>mp(n);
        for(int i=0; i<n; i++) {
            mp[nums2[i]]=i;
        }  
        vector<int>seg(4*n);
        segUpdate(0,0,n-1,mp[nums1[0]],seg); 
        long long res=0;
        for(int i=1; i<n-1; i++) {
            int idx=mp[nums1[i]];
            int common=query(0,idx,0,0,n-1,seg);
            int uncommon=i-common;
            int p = n-1-idx-uncommon;
            res+=p*1ll*common;
            segUpdate(0,0,n-1,idx,seg);
        }
        return res;
    }
};
