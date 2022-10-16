// Author: REET
// Problem: 0-1 Knapsack
// Link: https://www.codingninjas.com/codestudio/problems/0-1-knapsack_920542

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursion
// Time Complexity: O(2^n)
// Reason: Perfoming pick not pick for every indices
// Space Complexity: O(n)
// Reason: Auxiliary stack space O(n)
int solveR(int idx, int w, vector<int> &wt, vector<int> &val) {
    if(idx==0) {
        if(w>=wt[idx]) {
            return val[idx];
        }
        return 0;
    }
    int notPick = solveR(idx-1, w, wt, val);
    int pick = INT_MIN;
    if(w>=wt[idx]) {
        pick = val[idx] + solveR(idx-1, w-wt[idx], wt, val);
    }
    return max(pick, notPick);
}

// Approach: Memoization
// Time Complexity: O(n*w)
// Reason: n*w operations are getting performed
// Space Complexity: O(n*w)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n*w)
int solveM(int idx, int w, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp) {
    if(idx==0) {
        if(w>=wt[idx]) {
            return val[idx];
        }
        return 0;
    }
    if(dp[idx][w]!=-1) {
        return dp[idx][w];
    }
    int notPick = solveM(idx-1, w, wt, val, dp);
    int pick = INT_MIN;
    if(w>=wt[idx]) {
        pick = val[idx] + solveM(idx-1, w-wt[idx], wt, val, dp);
    }
    return dp[idx][w] = max(pick, notPick);
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
        dp[0][j] = val[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=w; j++) {
            int notPick = dp[i-1][j];
            int pick = INT_MIN;
            if(j>=wt[i]) {
                pick = val[i] + dp[i-1][j-wt[i]];
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
    for(int j=wt[0]; j<=w; j++) {
        prev[j] = val[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=w; j++) {
            int notPick = prev[j];
            int pick = INT_MIN;
            if(j>=wt[i]) {
                pick = val[i] + prev[j-wt[i]];
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
    for(int j=wt[0]; j<=w; j++) {
        curr[j] = val[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=w; j>=0; j--) {
            int notPick = curr[j];
            int pick = INT_MIN;
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
    vector<vector<int>> dp(n, vector<int> (w+1, -1)); // For Memoization
    
    cout << solveR(n-1, w, wt, val) << "\n";
    cout << solveM(n-1, w, wt, val, dp) << "\n";
    cout << solveT(w, wt, val) << "\n";
    cout << solveS(w, wt, val) << "\n";
    cout << solveSS(w, wt, val);
    
    return 0;
}

/*
Output of the program:
70
70
70
70
70
*/