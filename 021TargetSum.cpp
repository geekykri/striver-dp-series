// Author: REET
// Problem: Target Sum
// Link: https://leetcode.com/problems/target-sum/

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
// Space Complexity: O(n*t)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n*t)
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
// Space Complexity: O(n*t)
// Reason: Dp Array O(n*t)
int solveT(vector<int> &num, int t) {
    int n = num.size();
    vector<vector<int>> dp(n, vector<int> (t+1));
    dp[0][0] = (num[0]==0) ? 2 : 1;
    if(num[0]!=0 and num[0]<=t) {
        dp[0][num[0]] = 1;
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=t; j++) {
            int notPick = dp[i-1][j];
            int pick = 0;
            if(j>=num[i]) {
                pick = dp[i-1][j-num[i]];
            }
            dp[i][j] = pick + notPick;
        }
    }
    return dp[n-1][t];
}

// Approach: Space Optimized
// Time Complexity: O(n)
// Reason: Storing and using previous values
// Space Complexity: O(t)
// Reason: Two Dp Array O(t)
int solveS(vector<int> &num, int t) {
    int n = num.size();
    vector<int> prev(t+1);
    vector<int> curr(t+1);
    prev[0] = (num[0]==0 ? 2 : 1);
    if(num[0]!=0 and num[0]<=t) {
        prev[num[0]] = 1;
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=t; j++) {
            int notPick = prev[j];
            int pick = 0;
            if(j>=num[i]) {
                pick = prev[j-num[i]];
            }
            curr[j] = (pick + notPick);
        }
        prev = curr;
    }
    return prev[t];
}

int main() {
    vector<int> num{1, 1, 1, 1, 1};
    int target = 3;
    int n = num.size();
    int ts = accumulate(begin(num), end(num), 0);
    int t = (ts-target);
    if(t<0 or t&1) {
        cout << "0\n";
        return 0;
    }
    t /= 2;
    vector<vector<int>> dp(n, vector<int> (t+1, -1)); // For Memoization
    
    cout << solveR(n-1, num, t) << "\n";
    cout << solveM(n-1, num, t, dp) << "\n";
    cout << solveT(num, t) << "\n";
    cout << solveS(num, t);
    
    return 0;
}

/*
Output of the program:
5
5
5
5
*/