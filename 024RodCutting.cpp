// Author: REET
// Problem: Rod Cutting
// Link: https://www.codingninjas.com/codestudio/problems/rod-cutting-problem_800284

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursion
// Time Complexity: Exponential
// Reason: Standing at the same index even after picking
// Space Complexity: O(len)
// Reason: Auxiliary stack space O(len)
int solveR(int idx, int len, vector<int> &price) {
    if(idx==0) {
        return len*price[0];
    }
    int notPick = solveR(idx-1, len, price);
    int pick = INT_MIN;
    if(len>=idx+1) {
        pick = price[idx] + solveR(idx, len-idx-1, price);
    }
    return max(pick, notPick);
}

// Approach: Memoization
// Time Complexity: O(n*len)
// Reason: n*len operations are getting performed
// Space Complexity: O(n*len)
// Reason: Auxiliary Stack Space O(len) + Dp Array O(n*len)
int solveM(int idx, int len, vector<int> &price, vector<vector<int>> &dp) {
    if(idx==0) {
        return len*price[0];
    }
    if(dp[idx][len]!=-1) {
        return dp[idx][len];
    }
    int notPick = solveM(idx-1, len, price, dp);
    int pick = INT_MIN;
    if(len>=idx+1) {
        pick = price[idx] + solveM(idx, len-idx-1, price, dp);
    }
    return dp[idx][len] = max(pick, notPick);
}

// Approach: Tabulation
// Time Complexity: O(n*len)
// Reason: Nested for loops
// Space Complexity: O(n*len)
// Reason: Dp Array O(n*len)
int solveT(int len, vector<int> &price) {
    int n = price.size(); // len & n are same
    vector<vector<int>> dp(n, vector<int> (len+1, -1));
    for(int j=0; j<=n; j++) {
        dp[0][j] = j*price[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=n; j++) {
            int notPick = dp[i-1][j];
            int pick = INT_MIN;
            if(j>=i+1) {
                pick = price[i] + dp[i][j-i-1];
            }
            dp[i][j] = max(pick, notPick);
        }
    }
    return dp[n-1][len];
}

// Approach: Space Optimized
// Time Complexity: O(n*len)
// Reason: Nested for loops
// Space Complexity: O(len)
// Reason: 2 Dp Array O(len+len)
int solveS(int len, vector<int> &price) {
    int n = price.size(); // len & n are same
    vector<int> prev(len+1);
    vector<int> curr(len+1);
    for(int j=0; j<=n; j++) {
        prev[j] = j*price[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=n; j++) {
            int notPick = prev[j];
            int pick = INT_MIN;
            if(j>=i+1) {
                pick = price[i] + curr[j-i-1];
            }
            curr[j] = max(pick, notPick);
        }
        prev = curr;
    }
    return prev[len];
}

// Approach: Super Space Optimized
// Time Complexity: O(n*len)
// Reason: Nested for loops
// Space Complexity: O(len)
// Reason: Dp Array O(len)
int solveSS(int len, vector<int> &price) {
    int n = price.size(); // len & n are same
    vector<int> curr(len+1);
    for(int j=0; j<=n; j++) {
        curr[j] = j*price[0];
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=n; j++) {
            int notPick = curr[j];
            int pick = INT_MIN;
            if(j>=i+1) {
                pick = price[i] + curr[j-i-1];
            }
            curr[j] = max(pick, notPick);
        }
    }
    return curr[len];
}

int main() {
    vector<int> price {2, 5, 7, 8, 10};
    int len = 5;
    int n = price.size();
    vector<vector<int>> dp(n, vector<int> (len+1, -1));
    
    cout << solveR(n-1, len, price) << "\n";
    cout << solveM(n-1, len, price, dp) << "\n";
    cout << solveT(len, price) << "\n";
    cout << solveS(len, price) << "\n";
    cout << solveSS(len, price);
    
    return 0;
}

/*
Output of the program:
12
12
12
12
12
*/