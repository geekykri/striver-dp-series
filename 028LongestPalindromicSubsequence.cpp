// Author: REET
// Problem: Longest Palindromic Subsequence
// Link: https://leetcode.com/problems/longest-palindromic-subsequence/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n*2^n) ~ Exponential
// Reason: Standing at the same index even after picking
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int idx1, int idx2, string &s, string &t) {
    // Using shifting of index
    if(idx1==0 or idx2==0) {
        return 0;
    }
    if(s[idx1-1]==t[idx2-1]) {
        return 1 + solveR(idx1-1, idx2-1, s, t);
    }
    return max(solveR(idx1-1, idx2, s, t), solveR(idx1, idx2-1, s, t));
}

// Approach: Memoization
// Time Complexity: O(n*n)
// Reason: Value being reused after computation
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveM(int idx1, int idx2, string &s, string &t, vector<vector<int>> &dp) {
    if(idx1==0 or idx2==0) {
        return 0;
    }
    if(dp[idx1][idx2]!=-1) {
        return dp[idx1][idx2];
    }
    if(s[idx1-1]==t[idx2-1]) {
        return dp[idx1][idx2] = 1 + solveM(idx1-1, idx2-1, s, t, dp);
    }
    return dp[idx1][idx2] = max(solveM(idx1-1, idx2, s, t, dp), solveM(idx1, idx2-1, s, t, dp));
}

// Approach: Tabulation
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n*n)
// Reason: Dp Array O(n*n)
int solveT(string &s, string &t) {
    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int> (n+1));
    for(int idx1=1; idx1<=n; idx1++) {
        for(int idx2=1; idx2<=n; idx2++) {
            if(s[idx1-1]==t[idx2-1]) {
                dp[idx1][idx2] = 1 + dp[idx1-1][idx2-1];
            }
            else {
                dp[idx1][idx2] = max(dp[idx1-1][idx2], dp[idx1][idx2-1]);
            }
        }
    }
    return dp[n][n];
}

// Approach: Space Optimized
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n)
// Reason: Dp Array O(n+n)
int solveS(string &s, string &t) {
    int n = s.size();
    vector<int> prev(n+1);
    vector<int> curr(n+1);
    for(int idx1=1; idx1<=n; idx1++) {
        for(int idx2=1; idx2<=n; idx2++) {
            if(s[idx1-1]==t[idx2-1]) {
                curr[idx2] = 1 + prev[idx2-1];
            }
            else {
                curr[idx2] = max(prev[idx2], curr[idx2-1]);
            }
        }
        prev = curr;
    }
    return prev[n];
}

int main() {
    string s = "bbbab";
    string t = s;
    reverse(begin(t), end(t));
    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int> (n+1, -1));
    
    cout << solveR(n, n, s, t) << "\n";
    cout << solveM(n, n, s, t, dp) << "\n";
    cout << solveT(s, t) << "\n";
    cout << solveS(s, t);
    
    return 0;
}

/*
Output of the program:
4
4
4
4
*/