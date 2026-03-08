class Solution {
public:


    int largestRectangleArea(vector<int>& v) {


        int n=v.size();
        vector<int>pre(n+1),suf(n+1);
        vector<int>st;

        for(int i=1; i<=n; i++) {
            while(!st.empty()&&v[st.back()-1]>=v[i-1]) st.pop_back();
            if(st.empty()) pre[i]=0;
            else pre[i]=st.back();
            st.push_back(i);
        }
        st.clear();
        for(int i=n; i>=1; i--) {
            while(!st.empty()&&v[st.back()-1]>=v[i-1]) st.pop_back();
            if(st.empty()) suf[i]=n+1;
            else suf[i]=st.back();
            st.push_back(i);
        }

        long long res=0;

        for(int i=1; i<=n; i++) {
            long long ln = suf[i]-pre[i]-1;
            res=max(res,ln*v[i-1]);
        }

        return res;
    }
};
