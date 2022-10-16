// Author: REET
// Problem: Minimum Elements
// Link: https://www.codingninjas.com/codestudio/problems/minimum-elements_3843091

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursion
// Time Complexity: >= O(2^n) [Just say exponential]
// Reason: Perfoming pick not pick for every indices
// Space Complexity: >= O(n) Max O(t)
// Reason: Pick & Not Move Oprn will add up more auxiliary stack space
int solveR(int idx, int t, vector<int> &num) {
    if(idx==0) {
        if(t%num[0]==0) {
            return t/num[0];
        }
        return 1e9;
    }
    int notPick = solveR(idx-1, t, num);
    int pick = INT_MAX;
    if(t>=num[idx]) {
        pick = 1 + solveR(idx, t-num[idx], num);
    }
    return min(pick, notPick);
}

// Approach: Memoization
// Time Complexity: O(n*t)
// Reason: At max n*t operations are getting performed
// Space Complexity: O(n*t)
// Reason: Dp array of size O(n*t) + Auxiliary Stack Space O(t)
int solveM(int idx, int t, vector<int> &num, vector<vector<int>> &dp) {
    if(idx==0) {
        if(t%num[0]==0) {
            return t/num[0];
        }
        return 1e9;
    }
    if(dp[idx][t]!=-1) {
        return dp[idx][t];
    }
    int notPick = solveM(idx-1, t, num, dp);
    int pick = INT_MAX;
    if(t>=num[idx]) {
        pick = 1 + solveM(idx, t-num[idx], num, dp);
    }
    return dp[idx][t] = min(pick, notPick);
}

// Approach: Tabulation
// Time Complexity: O(n*t)
// Reason: Nested for loops
// Space Complexity: O(n*t)
// Reason: Dp Array O(n*t)
int solveT(int t, vector<int> &num) {
    int n = num.size();
    vector<vector<int>> dp(n, vector<int> (t+1));
    for(int j=0; j<=t; j++) {
        if(j%num[0]==0) {
            dp[0][j] = j/num[0];
        }
        else {
            dp[0][j] = 1e9;
        }
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=t; j++) {
            int notPick = dp[i-1][j];
            int pick = INT_MAX;
            if(j>=num[i]) {
                pick = 1 + dp[i][j-num[i]];
            }
            dp[i][j] = min(pick, notPick);
        }
    }
    return dp[n-1][t];
}

// Approach: Space Optimized
// Time Complexity: O(n*t)
// Reason: Nested for loops
// Space Complexity: O(t)
// Reason: 2 Dp Array O(t+t)
int solveS(int t, vector<int> &num) {
    int n = num.size();
    vector<int> prev(t+1);
    vector<int> curr(t+1);
    for(int j=0; j<=t; j++) {
        if(j%num[0]==0) {
            prev[j] = j/num[0];
        }
        else {
            prev[j] = 1e9;
        }
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=t; j++) {
            int notPick = prev[j];
            int pick = INT_MAX;
            if(j>=num[i]) {
                pick = 1 + curr[j-num[i]];
            }
            curr[j] = min(pick, notPick);
        }
        prev = curr;
    }
    return prev[t];
}

// Approach: Super Space Optimized
// Time Complexity: O(n*t)
// Reason: Nested for loops
// Space Complexity: O(t)
// Reason: Dp Array O(t)
int solveSS(int t, vector<int> &num) {
    int n = num.size();
    vector<int> curr(t+1);
    for(int j=0; j<=t; j++) {
        if(j%num[0]==0) {
            curr[j] = j/num[0];
        }
        else {
            curr[j] = 1e9;
        }
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=t; j++) {
            int notPick = curr[j];
            int pick = INT_MAX;
            if(j>=num[i]) {
                pick = 1 + curr[j-num[i]];
            }
            curr[j] = min(pick, notPick);
        }
        curr = curr;
    }
    return curr[t];
}

int main() {
    vector<int> num {13, 17, 20, 19, 1, 8};
    int n = num.size();
    int t = 10;
    vector<vector<int>> dp(n, vector<int> (t+1, -1)); // For Memoization
    
    cout << solveR(n-1, t, num) << "\n";
    cout << solveM(n-1, t, num, dp) << "\n";
    cout << solveT(t, num) << "\n";
    cout << solveS(t, num) << "\n";
    cout << solveSS(t, num);
    
    return 0;
}

/*
Output of the program:
3
3
3
3
3
*/