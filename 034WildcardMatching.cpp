// Author: REET
// Problem: Edit Distance
// Link: https://leetcode.com/problems/edit-distance

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: Exponential
// Reason: Exponential calls
// Space Complexity: O(n+m)
// Reason: Auxiliary Stack Space O(n+m)
int solveR(int i, int j, string &s, string &p) {
    if(j==0 and i==0) {
        return true;
    }
    if(j==0 and i>=1) {
        return false;   
    }
    if(i==0 and j>=1) {
        for(int jj=j; jj>0; jj--) {
            if(p[jj-1]!='*') {
                return false;
            }
        }
        return true;
    }
    if(s[i-1]==p[j-1] or p[j-1]=='?') {
        return solveR(i-1, j-1, s, p);
    }
    else if(p[j-1]=='*') {
        bool notTake = solveR(i, j-1, s, p);
        bool take = solveR(i-1, j, s, p);
        return take or notTake;
    }
    return false;
}

// Approach: Memoization
// Time Complexity: O(n*m)
// Reason: At max O(n*m) states
// Space Complexity: O(n*m)
// Reason: Dp array O(n*m) + Auxiliary Stack Space O(n+m)
bool solveM(int i, int j, string &s, string &p, vector<vector<int>> &dp) {
    if(j==0 and i==0) {
        return true;
    }
    if(j==0 and i>=1) {
        return false;   
    }
    if(i==0 and j>=1) {
        for(int jj=j; jj>0; jj--) {
            if(p[jj-1]!='*') {
                return false;
            }
        }
        return true;
    }
    if(dp[i][j]!=-1) {
        return dp[i][j];
    }
    if(s[i-1]==p[j-1] or p[j-1]=='?') {
        return dp[i][j] = solveM(i-1, j-1, s, p, dp);
    }
    else if(p[j-1]=='*') {
        bool notTake = solveM(i, j-1, s, p, dp);
        bool take = solveM(i-1, j, s, p, dp);
        return dp[i][j] = take or notTake;
    }
    return dp[i][j] = false;
}

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp array O(n*m)
int solveT(string &s, string &p) {
    int n = s.size();
    int m = size(p);
    vector<vector<bool>> dp(n+1, vector<bool> (m+1));
    dp[0][0] = true;
    for(int i=1; i<=n; i++) {
        dp[i][0] = false;
    }
    for(int j=1; j<=m; j++) {
        bool flag = true;
        for(int jj=j; jj>0; jj--) {
            if(p[jj-1]!='*') {
                flag = false;
                break;
            }
        }
        dp[0][j] = flag;
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(s[i-1]==p[j-1] or p[j-1]=='?') {
                dp[i][j] = dp[i-1][j-1];
            }
            else if(p[j-1]=='*') {
                bool notTake = dp[i][j-1];
                bool take = dp[i-1][j];
                dp[i][j] = take or notTake;
            }
        }
    }
    return dp[n][m];
}


int main() {
    string s = "cb";
    string p = "?a";
    int n = s.size();
    int m = size(p);
    vector<vector<int>> dp(n+1, vector<int> (m+1, -1)); // For Memoization
    
    // Using shifting of index
    cout << solveR(n, m, s, p) << "\n";
    cout << solveM(n, m, s, p, dp) << "\n";
    cout << solveT(s, p);
    
    return 0;
}

/*
Output of the program:
0
0
0
*/