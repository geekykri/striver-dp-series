// Author: REET
// Problem: Coin Change 2
// Link: https://leetcode.com/problems/coin-change-2/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursion
// Time Complexity: >= O(2^n) [Just say exponential]
// Reason: Perfoming pick not pick for every indices
// Space Complexity: >= O(n) Max O(amount)
// Reason: Pick & Not Move Oprn will add up more auxiliary stack space
int solveR(int idx, int amount, vector<int> &coins) {
    if(idx==0) {
        if(amount%coins[0]==0) {
            return amount/coins[0];
        }
        return 1e9;
    }
    int notPick = solveR(idx-1, amount, coins);
    int pick = 1e9;
    if(amount>=coins[idx]) {
        pick = 1 + solveR(idx, amount-coins[idx], coins);
    }
    return min(pick,notPick);
}

// Approach: Memoization
// Time Complexity: O(n*amount)
// Reason: At max n*amount operations are getting performed
// Space Complexity: O(n*amount)
// Reason: Dp array of size O(n*amount) + Auxiliary Stack Space O(amount)
int solveM(int idx, int amount, vector<int> &coins, vector<vector<int>> &dp) {
    if(idx==0) {
        if(amount%coins[0]==0) {
            return amount/coins[0];
        }
        return 1e9;
    }
    if(dp[idx][amount]!=-1) {
        return dp[idx][amount];
    }
    int notPick = solveM(idx-1, amount, coins, dp);
    int pick = 1e9;
    if(amount>=coins[idx]) {
        pick = 1 + solveM(idx, amount-coins[idx], coins, dp);
    }
    return dp[idx][amount] = min(pick,notPick);
}

// Approach: Tabulation
// Time Complexity: O(n*amount)
// Reason: Nested for loops
// Space Complexity: O(n*amount)
// Reason: Dp Array O(n*amount)
int solveT(int amount, vector<int> &nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int> (amount+1));
    for(int j=0; j<=amount; j++) {
        if(j%nums[0]==0) {
            dp[0][j] = j/nums[0];
        }
        else {
            dp[0][j] = 1e9;
        }
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=amount; j++) {
            int notPick = dp[i-1][j];
            int pick = INT_MAX;
            if(j>=nums[i]) {
                pick = 1 + dp[i][j-nums[i]];
            }
            dp[i][j] = min(pick, notPick);
        }
    }
    return dp[n-1][amount];
}

// Approach: Space Optimized
// Time Complexity: O(n*amount)
// Reason: Nested for loops
// Space Complexity: O(amount)
// Reason: 2 Dp Array O(amount+amount)
int solveS(int amount, vector<int> &nums) {
    int n = nums.size();
    vector<int> prev(amount+1);
    vector<int> curr(amount+1);
    for(int j=0; j<=amount; j++) {
        if(j%nums[0]==0) {
            prev[j] = j/nums[0];
        }
        else {
            prev[j] = 1e9;
        }
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=amount; j++) {
            int notPick = prev[j];
            int pick = INT_MAX;
            if(j>=nums[i]) {
                pick = 1 + curr[j-nums[i]];
            }
            curr[j] = min(pick, notPick);
        }
        prev = curr;
    }
    return prev[amount];
}

// Approach: Super Space Optimized
// Time Complexity: O(n*amount)
// Reason: Nested for loops
// Space Complexity: O(amount)
// Reason: Dp Array O(amount)
int solveSS(int amount, vector<int> &nums) {
    int n = nums.size();
    vector<int> curr(amount+1);
    for(int j=0; j<=amount; j++) {
        if(j%nums[0]==0) {
            curr[j] = j/nums[0];
        }
        else {
            curr[j] = 1e9;
        }
    }
    for(int i=1; i<n; i++) {
        for(int j=0; j<=amount; j++) {
            int notPick = curr[j];
            int pick = INT_MAX;
            if(j>=nums[i]) {
                pick = 1 + curr[j-nums[i]];
            }
            curr[j] = min(pick, notPick);
        }
        curr = curr;
    }
    return curr[amount];
}

int main() {
    vector<int> nums {1, 2, 5};
    int n = nums.size();
    int amount = 11;
    vector<vector<int>> dp(n, vector<int> (amount+1, -1)); // For Memoization
    
    cout << solveR(n-1, amount, nums) << "\n";
    cout << solveM(n-1, amount, nums, dp) << "\n";
    cout << solveT(amount, nums) << "\n";
    cout << solveS(amount, nums) << "\n";
    cout << solveSS(amount, nums);
    
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