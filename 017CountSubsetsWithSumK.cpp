// Author: REET
// Problem: Subset Sum Equal To K
// Link: https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: Pick and Not Pick for every index
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int idx, vector<int> &num, int t) {
    if(idx==0) {
        if(t==0 and num[0]==0) {
            return 2;
        }
        if(t==0 or t==num[0]) {
            return 1;
        }
        return 0;
    }
    int notPick = solveR(idx-1, num, t);
    int pick = 0;
    if(t>=num[idx]) {
        pick = solveR(idx-1, num, t-num[idx]);
    }
    return pick + notPick;
}

// Approach: Memoization
// Time Complexity: O(n)
// Reason: Storing and using previous values
// Space Complexity: O(n*k)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n*k)
int solveM(int idx, vector<int> &num, int t, vector<vector<int>> &dp) {
    if(idx==0) {
        if(t==0 and num[0]==0) {
            return 2;
        }
        if(t==0 or t==num[0]) {
            return 1;
        }
        return 0;
    }
    if(dp[idx][t]!=-1) {
        return dp[idx][t];
    }
    int notPick = solveM(idx-1, num, t, dp);
    int pick = 0;
    if(t>=num[idx]) {
        pick = solveM(idx-1, num, t-num[idx], dp);
    }
    return dp[idx][t] = pick + notPick;
}

// Approach: Tabulation
// Time Complexity: O(n)
// Reason: Storing and using previous values
// Space Complexity: O(n*k)
// Reason: Dp Array O(n*k)
int solveT(vector<int> &num, int k) {
    int n = num.size();
    vector<vector<int>> dp(n, vector<int> (k+1));
    dp[0][0] = (num[0]==0) ? 2 : 1;
    if(num[0]!=0 and num[0]<=k) {
        dp[0][num[0]] = 1;
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<=k; j++) {
            int notPick = dp[i-1][j];
            int pick = 0;
            if(j>=num[i]) {
                pick = dp[i-1][j-num[i]];
            }
            dp[i][j] = pick + notPick;
        }
    }
    return dp[n-1][k];
}

// Approach: Space Optimized
// Time Complexity: O(n)
// Reason: Storing and using previous values
// Space Complexity: O(k)
// Reason: Two Dp Array O(k)
int solveS(vector<int> &num, int k) {
    int n = num.size();
    vector<int> prev(k+1);
    vector<int> curr(k+1);
    vector<vector<int>> dp(n, vector<int> (k+1));
    prev[0] = 2;
    curr[0] = 1;
    if(num[0]>=k) {
        prev[num[0]] = 1;
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<=k; j++) {
            int notPick = prev[j];
            int pick = 0;
            if(j>=num[i]) {
                pick = prev[j-num[i]];
            }
            curr[j] = pick + notPick;
        }
        prev = curr;
    }
    return prev[k];
}

int main() {
    int n = 6;
    int k = 5;
    vector<int> num{4, 3, 2, 1, 0, 0};
    vector<vector<int>> dp(n, vector<int> (k+1, -1)); // For Memoization
    
    cout << solveR(n-1, num, k) << "\n";
    cout << solveM(n-1, num, k, dp) << "\n";
    cout << solveT(num, k) << "\n";
    cout << solveS(num, k);
    
    return 0;
}

/*
Output of the program:
8
8
8
8
*/