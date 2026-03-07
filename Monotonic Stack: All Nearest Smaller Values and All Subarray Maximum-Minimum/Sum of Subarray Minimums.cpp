class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {

        int n=arr.size();

        vector<int>pref(n+1),suf(n+1);

        vector<int>st;

        for(int i=1; i<=n; i++) {
            while(!st.empty()&&arr[st.back()-1]>arr[i-1]) st.pop_back();
            if(st.empty()) pref[i]=0;
            else pref[i]=st.back();
            st.push_back(i);
        }

        st.clear();

        for(int i=n; i>=1; i--) {
            while(!st.empty()&&arr[st.back()-1]>=arr[i-1]) st.pop_back();
            if(st.empty()) suf[i]=n+1;
            else suf[i]=st.back();
            st.push_back(i);
        }

        int res=0;
        int M=1e9+7;
        for(int i=1; i<=n; i++) {
            res+=(((i-pref[i])*1ll*(suf[i]-i))%M*1ll*arr[i-1])%M;
            res%=M;
        }

        return res;
        
    }
};
