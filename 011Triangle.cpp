// Author: REET
// Problem: Triangle
// Link: https://leetcode.com/problems/triangle/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: (2^(1+2+3+...+n)) states
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int x, int y, int m, int n, vector<vector<int>> &t) {
    if(x==m-1) {
        return t[x][y];
    }
    int d = solveR(x+1, y, m, n, t);
    int dg = solveR(x+1, y+1, m, n, t);
    return t[x][y] + min(d, dg);
}

// Approach: Memoization
// Time Complexity: O(n^2)
// Reason: 1+2+3+...+n = n(n+1)/2 ~= n^2 states
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveM(int x, int y, int m, int n, vector<vector<int>> &t, vector<vector<int>> &dp) {
    if(x==m-1) {
        return t[x][y];
    }
    if(dp[x][y]!=-1) {
        return dp[x][y];
    }
    int d = solveM(x+1, y, m, n, t, dp);
    int dg = solveM(x+1, y+1, m, n, t, dp);
    return dp[x][y] = t[x][y] + min(d, dg);
}

// Approach: Tabulation
// Time Complexity: O(n^2)
// Reason: 1+2+3+...+n = n(n+1)/2 ~= n^2 
// Space Complexity: O(m*n)
// Reason: Dp array O(m*n)
int solveT(vector<vector<int>> &t) {
    // Space optimized soln
    int m = t.size();
    int n = t[m-1].size();
    vector<vector<int>> dp(m, vector<int> (n));
    for(int j=0; j<n; j++) {
        dp[m-1][j] = t[m-1][j];
    }
    for(int x=n-2; x>=0; x--) {
        for(int y=x; y>=0; y--) {
            int d = dp[x+1][y];
            int dg = dp[x+1][y+1];
            dp[x][y] = t[x][y] + min(d, dg);
        }
    }
    return dp[0][0];
}

// Approach: Space Optimized
// Time Complexity: O(n^2)
// Reason: 1+2+3+...+n = n(n+1)/2 ~= n^2
// Space Complexity: O(n)
// Reason: Dp array O(n)[where n is size of last row]
int sovleS(vector<vector<int>> &t) {
    int m = t.size();
    int n = t[m-1].size();
    vector<int> dp(n);
    for(int j=0; j<n; j++) {
        dp[j] = t[m-1][j];
    }
    for(int x=m-2; x>=0; x--) {
        for(int y=0; y<t[x].size(); y++) {
            int d = dp[y];
            int dg = dp[y+1];
            dp[y] = t[x][y] + min(d, dg);
        }
    }
    return dp[0];
}

int main() {
    vector<vector<int>> t {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    int m = t.size();
    int n = t.back().size();
    vector<vector<int>> dp(m, vector<int> (n, -1)); // For Memoization
    
    cout << solveR(0, 0, m, n, t) << "\n";
    cout << solveM(0, 0, m, n, t, dp) << "\n";
    cout << solveT(t) << "\n";
    cout << sovleS(t);

    return 0;
}

/*
Output of the program:
11
11
11
11
*/