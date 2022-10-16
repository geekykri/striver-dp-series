// Author: REET
// Problem: Grid Unique Path
// Link: https://leetcode.com/problems/unique-paths/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^(m*n))
// Reason: Performing up left at every cell
// Space Complexity: O(Length of the longest path)
// Reason: Length of the longest path will determine the stack space
int solveR(int x, int y, int m, int n) {
    if(x==0 and y==0) {
        return 1;
    }
    if(x<0 or y<0) {
        return 0;
    }
    int up = solveR(x-1, y, m, n);
    int left = solveR(x, y-1, m, n);
    return up+left;
}

// Approach: Memoization
// Time Complexity: O(m*n)
// Reason: One time computation only, after that value is being reused
// Space Complexity: O(Length of the longest path)
// Reason: Length of the longest path will determine the stack space
int solveM(int x, int y, int m, int n, vector<vector<int>> &dp) {
    if(x==0 and y==0) {
        return 1;
    }
    if(x<0 or y<0) {
        return 0;
    }
    if(dp[x][y]!=-1) {
        return dp[x][y];
    }
    int up = solveM(x-1, y, m, n, dp);
    int left = solveM(x, y-1, m, n, dp);
    return dp[x][y] = up+left;
}

// Approach: Tabulation
// Time Complexity: O(m*n)
// Reason: Taking up value from the previous state, two loops
// Space Complexity: O(m*n)
// Reason: Dp array O(m*n)
int solveT(int m, int n) {
    vector<vector<int>> dp(m, vector<int> (n));
    for(int x=0; x<m; x++) {
        for(int y=0; y<n; y++) {
            if(x==0 and y==0) {
                dp[x][y] = 1;
                continue;
            }
            int up = 0;
            int left = 0;
            if(x>0) {
                up = dp[x-1][y];
            }
            if(y>0) {
                left = dp[x][y-1];
            }
            dp[x][y] = up+left;
        }
    }
    return dp[m-1][n-1];
}

// Approach: Space Optimized
// Time Complexity: O(m*n)
// Reason: Taking up value from the previous state, two loops
// Space Complexity: O(n)
// Reason: Using row size vector to store the states
int solveS(int m, int n) {
    vector<int> prev(n);
    for(int x=0; x<m; x++) {
        vector<int> curr(n);
        for(int y=0; y<n; y++) {
            if(x==0 and y==0) {
                curr[y] = 1;
                continue;
            }
            int up = 0;
            int left = 0;
            if(x>0) {
                up = prev[y];
            }
            if(y>0) {
                left = curr[y-1];
            }
            curr[y] = up+left;
        }
        prev = curr;
    }
    return prev[n-1];
}

int main() {
    int m = 3;
    int n = 3;
    vector<vector<int>> dp(m, vector<int> (n, -1)); // For Memoization
    
    cout << solveR(m-1, n-1, m, n) << "\n";
    cout << solveM(m-1, n-1, m, n, dp) << "\n";
    cout << solveT(m, n) << "\n";
    cout << solveS(m, n);
    
    return 0;
}

/*
Output of the program:
6
6
6
6
*/