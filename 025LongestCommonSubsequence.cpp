// Author: REET
// Problem: Longest Common Subsequence
// Link: https://leetcode.com/problems/longest-common-subsequence/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursion
// Time Complexity: O(2^n * 2^m)
// Reason: Standing at the same index even after picking
// Space Complexity: O(m)
// Reason: Auxiliary stack space O(m)
int solveR(int idx1, int idx2, string &text1, string &text2) {
    if(idx1<0 or idx2<0) {
        return 0;
    }
    if(text1[idx1]==text2[idx2]) {
        return 1 + solveR(idx1-1, idx2-1, text1, text2);
    }
    return max(solveR(idx1-1, idx2, text1, text2), solveR(idx1, idx2-1, text1, text2));
}

// Approach: Memoization
// Time Complexity: O(n*m)
// Reason: n*len operations are getting performed
// Space Complexity: O(n*m)
// Reason: Auxiliary Stack Space O(m) + Dp Array O(n*m)
int solveM(int idx1, int idx2, string &text1, string &text2, vector<vector<int>> &dp) {
    if(idx1<0 or idx2<0) {
        return 0;
    }
    if(dp[idx1][idx2]!=-1) {
        return dp[idx1][idx2];
    }
    if(text1[idx1]==text2[idx2]) {
        return dp[idx1][idx2] = 1 + solveM(idx1-1, idx2-1, text1, text2, dp);
    }
    return dp[idx1][idx2] = max(solveM(idx1-1, idx2, text1, text2, dp), solveM(idx1, idx2-1, text1, text2, dp));
}

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp Array O(n*m)
int solveT(string &text1, string &text2) {
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n, vector<int> (m));
    for(int idx1=0; idx1<n; idx1++) {
        for(int idx2=0; idx2<m; idx2++) {
            if(text1[idx1]==text2[idx2]) {
                dp[idx1][idx2] = 1;
                if(idx1>0 and idx2>0) {
                    dp[idx1][idx2] += dp[idx1-1][idx2-1];
                }
            }
            else {
                int l = INT_MIN;
                int r = INT_MIN;
                if(idx1>0) {
                    l = dp[idx1-1][idx2];
                }
                if(idx2>0) {
                    r = dp[idx1][idx2-1];
                }
                if(l==INT_MIN and r==INT_MIN) {
                    dp[idx1][idx2] = 0;
                }
                else {
                    dp[idx1][idx2] = max(l, r);
                }
            }
        }
    }
    return dp[n-1][m-1];
}

// Approach: Space Optimized
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(m)
// Reason: 2 Dp Array O(m+m)
int solveS(string &text1, string &text2) {
    int n = text1.size();
    int m = text2.size();
    vector<int> prev(m);
    vector<int> curr(m);
    for(int idx1=0; idx1<n; idx1++) {
        for(int idx2=0; idx2<m; idx2++) {
            if(text1[idx1]==text2[idx2]) {
                curr[idx2] = 1;
                if(idx1>0 and idx2>0) {
                    curr[idx2] += prev[idx2-1];
                }
            }
            else {
                int l = INT_MIN;
                int r = INT_MIN;
                if(idx1>0) {
                    l = prev[idx2];
                }
                if(idx2>0) {
                    r = curr[idx2-1];
                }
                if(l==INT_MIN and r==INT_MIN) {
                    curr[idx2] = 0;
                }
                else {
                    curr[idx2] = max(l, r);
                }
            }
        }
        prev = curr;
    }
    return prev[m-1];
}

int main() {
    string text1 = "abcde";
    string text2 = "ace"; 
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n, vector<int> (m, -1)); // For Memoization
    
    cout << solveR(n-1, m-1, text1, text2) << "\n";
    cout << solveM(n-1, m-1, text1, text2, dp) << "\n";
    cout << solveT(text1, text2) << "\n";
    cout << solveS(text1, text2);
    
    return 0;
}

/*
Output of the program:
3
3
3
3
*/