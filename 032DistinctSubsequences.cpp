// Author: REET
// Problem: Distinct Subsequences
// Link: https://leetcode.com/problems/distinct-subsequences/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: Exponential
// Reason: Standing at the same index even after picking
// Space Complexity: O(m)
// Reason: That many maximum calls can be made
int solveR(int idx1, int idx2, string &s, string &t) {
    if(idx2<0) {
        return 1;
    }
    if(idx1<0) {
        return 0;
    }
    if(s[idx1]==t[idx2]) {
        int pick = solveR(idx1-1, idx2-1, s, t);
        int notPick = solveR(idx1-1, idx2, s, t);
        return pick + notPick;
    }
    return solveR(idx1-1, idx2, s, t);
}

// Approach: Memoization
// Time Complexity: O(n*m)
// Reason: Using previously stored values from dp array
// Space Complexity: O(m)
// Reason: That many maximum calls can be made
int solveM(int idx1, int idx2, string &s, string &t, vector<vector<int>> &dp) {
    if(idx2<0) {
        return 1;
    }
    if(idx1<0) {
        return 0;
    }
    if(dp[idx1][idx2]!=-1) {
        return dp[idx1][idx2];
    }
    if(s[idx1]==t[idx2]) {
        int pick = solveM(idx1-1, idx2-1, s, t, dp);
        int notPick = solveM(idx1-1, idx2, s, t, dp);
        return dp[idx1][idx2] = pick + notPick;
    }
    return dp[idx1][idx2] = solveM(idx1-1, idx2, s, t, dp);
}

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp array O(n*m)
int solveT(string &s, string &t) {
    int n = s.size();
        int m = t.size();
        vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
        for(int idx1=0; idx1<=n; idx1++) {
            dp[idx1][0] = 1;
        }
        for(int idx1=1; idx1<=n; idx1++) {
            for(int idx2=1; idx2<=m; idx2++) {
                if(s[idx1-1]==t[idx2-1]) {
                    int pick = dp[idx1-1][idx2-1];
                    int notPick = dp[idx1-1][idx2];
                    dp[idx1][idx2] = pick + notPick;
                }
                else {
                    dp[idx1][idx2] = dp[idx1-1][idx2];
                }
            }
        }
        return dp[n][m];
}

// Approach: Space Optimized
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(m)
// Reason: Dp array O(m)
int solveS(string &s, string &t) {
    int n = s.size();
    int m = t.size();
    vector<int> curr(m+1);
    curr[0] = 1;
    for(int idx1=1; idx1<=n; idx1++) {
        for(int idx2=m; idx2>=1; idx2--) {
            if(s[idx1-1]==t[idx2-1]) {
                int pick = curr[idx2-1];
                int notPick = curr[idx2];
                curr[idx2] = static_cast<long long>(pick) + notPick;
            }
        }
    }
    return curr[m];
}

int main() {
    string s = "babgbag";
    string t = "bag";
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int> (m, -1)); // For Memoization
    
    cout << solveR(n-1, m-1, s, t) << "\n";
    cout << solveM(n-1, m-1, s, t, dp) << "\n";
    cout << solveT(s, t) << "\n";
    cout << solveS(s, t);
    
    return 0;
}

/*
Output of the program:
5
5
5
5
*/