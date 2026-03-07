/*=====================================================================

    ██████╗  ██████╗ ██████╗ ███████╗
   ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝
   ██║      ██║   ██║██║  ██║█████╗
   ██║      ██║   ██║██║  ██║██╔══╝
   ╚██████╗ ╚██████╔╝██████╔╝███████╗
    ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝

-----------------------------------------------------------------------

    Problem Name : Next Greater Element I
    Problem Link : https://leetcode.com/problems/next-greater-element-i/description/
    Platform     : LeetCode

-----------------------------------------------------------------------

    Author       : Md. Ratul Hossain
    CF Handle    : Phantom_R
    University   : Comilla University (CSE)
    Github       : https://github.com/ratulhn

-----------------------------------------------------------------------

    Technique    : Monotonic Stack
    Idea         :
        Go from right to left in the array (nums2).
        Maintain a stack of values where values are strictly decreasing.
        For each element, pop elements from the stack until a larger
        element appears. The top of the stack becomes the answer.

-----------------------------------------------------------------------

    Notes:
        Classic "Previous Larger Element" problem.
        Useful pattern for stack-based array problems.

=====================================================================*/

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

        int n=nums1.size(), m=nums2.size();
        vector<int>st;
        int v[(int)1e4+10];

        for(int i=m-1; i>=0; i--) {
            while(!st.empty()&&st.back()<=nums2[i]) st.pop_back();
            if(st.empty()) v[nums2[i]]=-1;
            else v[nums2[i]]=st.back();
            st.push_back(nums2[i]);
        }

        vector<int> res(n);

        for(int i=0; i<n; i++) res[i]=v[nums1[i]];

        return res;
        
    }
};
