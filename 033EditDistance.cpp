// Author: REET
// Problem: Edit Distance
// Link: https://leetcode.com/problems/edit-distance

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(3^n*3^m) ~ Exponential
// Reason: Three states call
// Space Complexity: O(n+m)
// Reason: Auxiliary Stack Space O(n+m)
int solveR(int i, int j, string &s, string &t) {
    if(i==0) {
        return j;
    }
    if(j==0) {
        return i;
    }
    if(s[i-1]==t[j-1]) {
        return solveR(i-1, j-1, s, t);
    }
    int ins = 1 + solveR(i, j-1, s, t);
    int del = 1 + solveR(i-1, j, s, t);
    int rep = 1 + solveR(i-1, j-1, s, t);
    return min(ins, min(del, rep));
}

// Approach: Memoization
// Time Complexity: O(n*m)
// Reason: Using previous stored value from dp array
// Space Complexity: O(n*m)
// Reason: Auxiliary Stack Space O(n+m) + Dp array O(n*m)
int solveM(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
    if(i==0) {
        return j;
    }
    if(j==0) {
        return i;
    }
    if(dp[i][j]!=-1) {
        return dp[i][j];
    }
    if(s[i-1]==t[j-1]) {
        return dp[i][j] = solveM(i-1, j-1, s, t, dp);
    }
    int ins = 1 + solveM(i, j-1, s, t, dp);
    int del = 1 + solveM(i-1, j, s, t, dp);
    int rep = 1 + solveM(i-1, j-1, s, t, dp);
    return dp[i][j] = min(ins, min(del, rep));
}

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp array O(n*m)
int solveT(string &s, string &t) {
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1));
    for(int i=0; i<=n; i++) {
        dp[i][0] = i;
    }
    for(int j=0; j<=m; j++) {
        dp[0][j] = j;
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(s[i-1]==t[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
            else {
                int ins = 1 + dp[i][j-1];
                int del = 1 + dp[i-1][j];
                int rep = 1 + dp[i-1][j-1];
                dp[i][j] = min(ins, min(del, rep));
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
    vector<int> prev(m+1);
    vector<int> curr(m+1);
    for(int j=0; j<=m; j++) {
        prev[j] = j;
    }
    for(int i=1; i<=n; i++) {
        curr[0] = i;
        for(int j=1; j<=m; j++) {
            if(s[i-1]==t[j-1]) {
                curr[j] = prev[j-1];
            }
            else {
                int ins = 1 + curr[j-1];
                int del = 1 + prev[j];
                int rep = 1 + prev[j-1];
                curr[j] = min(ins, min(del, rep));
            }
        }
        prev = curr;
    }
    return prev[m];
}

int main() {
    string s = "intention";
    string t = "execution";
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int> (m, -1)); // For Memoization
    
    // Using shifting of index
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