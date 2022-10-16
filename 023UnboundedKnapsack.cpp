// Author: REET
// Problem: Unbounded Knapsack
// Link: https://www.codingninjas.com/codestudio/problems/unbounded-knapsack_1215029

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursion
// Time Complexity: Exponential
// Reason: Standing at the same index even after picking
// Space Complexity: O(w)
// Reason: Auxiliary stack space O(w), Assume wt[4, 5, 1] w = 10 So at max 10/1 calls will be made
int solveR(int idx, int w, vector<int> &wt, vector<int> &val) {
    if(idx==0) {
        return (w/wt[idx]) * val[idx];
    }
    int notPick = solveR(idx-1, w, wt, val);
    int pick = -1e9;
    if(w>=wt[idx]) {
        pick = val[idx] + solveR(idx, w-wt[idx], wt, val);
    }
    return max(notPick, pick);
}

// Approach: Memoization
// Time Complexity: O(n*w)
// Reason: n*w operations are getting performed
// Space Complexity: O(n*w)
// Reason: Auxiliary Stack Space O(w) + Dp Array O(n*w)
int solveM(int idx, int w, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp) {
    if(idx==0) {
        return (w/wt[idx]) * val[idx];
    }
    if(dp[idx][w]!=-1) {
        return dp[idx][w];
    }
    int notPick = solveM(idx-1, w, wt, val, dp);
    int pick = -1e9;
    if(w>=wt[idx]) {
        pick = val[idx] + solveM(idx, w-wt[idx], wt, val, dp);
    }
    return dp[idx][w] = max(notPick, pick);
}

// Approach: Tabulation
// Time Complexity: O(n*w)
// Reason: Nested for loops
// Space Complexity: O(n*w)
// Reason: Dp Array O(n*w)
int solveT(int w, vector<int> &wt, vector<int> &val) {
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int> (w+1));
    for(int j=wt[0]; j<=w; j++) {
        dp[0][j] = (j/wt[0])*val[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=w; j++) {
            int notPick = dp[i-1][j];
            int pick = -1e9;
            if(j>=wt[i]) {
                pick = val[i] + dp[i][j-wt[i]];
            }
            dp[i][j] = max(pick, notPick);
        }
    }
    return dp[n-1][w];
}

// Approach: Space Optimized
// Time Complexity: O(n*w)
// Reason: Nested for loops
// Space Complexity: O(w)
// Reason: 2 Dp Array O(w+w)
int solveS(int w, vector<int> &wt, vector<int> &val) {
    int n = wt.size();
    vector<int> prev(w+1);
    vector<int> curr(w+1);
    vector<vector<int>> dp(n, vector<int> (w+1));
    for(int j=wt[0]; j<=w; j++) {
        prev[j] = (j/wt[0])*val[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=w; j++) {
            int notPick = prev[j];
            int pick = -1e9;
            if(j>=wt[i]) {
                pick = val[i] + curr[j-wt[i]];
            }
            curr[j] = max(pick, notPick);
        }
        prev = curr;
    }
    return prev[w];
}

// Approach: Super Space Optimized
// Time Complexity: O(n*w)
// Reason: Nested for loops
// Space Complexity: O(w)
// Reason: Dp Array O(w)
int solveSS(int w, vector<int> &wt, vector<int> &val) {
    int n = wt.size();
    vector<int> curr(w+1);
    vector<vector<int>> dp(n, vector<int> (w+1));
    for(int j=wt[0]; j<=w; j++) {
        curr[j] = (j/wt[0])*val[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=w; j++) {
            int notPick = curr[j];
            int pick = -1e9;
            if(j>=wt[i]) {
                pick = val[i] + curr[j-wt[i]];
            }
            curr[j] = max(pick, notPick);
        }
    }
    return curr[w];
}

int main() {
    vector<int> wt {3, 2, 5};
    vector<int> val {30, 40, 60};
    int w = 6;
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int> (w+1, -1));
    
    cout << solveR(n-1, w, wt, val) << "\n";
    cout << solveM(n-1, w, wt, val, dp) << "\n";
    cout << solveT(w, wt, val) << "\n";
    cout << solveS(w, wt, val) << "\n";
    cout << solveSS(w, wt, val);
    
    return 0;
}

/*
Output of the program:
120
120
120
120
120
*/