// Author: REET
// Problem: Buy and Sell Stock with Transaction Fees
// Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: Two different states at every call
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int idx, vector<int> &prices, bool isHeld, int fee) {
    if(idx==prices.size()) {
        return 0;
    }
    if(!isHeld) {
        int buy = - prices[idx] - fee + solveR(idx+1, prices, !isHeld, fee);
        int notBuy = solveR(idx+1, prices, isHeld, fee);
        return max(buy, notBuy);
    }
    int sell = prices[idx] + solveR(idx+1, prices, !isHeld, fee);
    int notSell = solveR(idx+1, prices, isHeld, fee);
    return max(sell, notSell);
}

// Approach: Memoization
// Time Complexity: O(2^n)
// Reason: Two different states at every call
// Space Complexity: O(n*2)
// Reason: Auxiliary Stack Space O(n) + Dp array O(n*2)
int solveM(int idx, vector<int> &prices, bool isHeld, int fee, vector<vector<int>> &dp) {
    if(idx==prices.size()) {
        return 0;
    }
    if(dp[idx][isHeld]!=-1) {
        return dp[idx][isHeld];
    }
    if(!isHeld) {
        int buy = - prices[idx] - fee + solveM(idx+1, prices, !isHeld, fee, dp);
        int notBuy = solveM(idx+1, prices, isHeld, fee, dp);
        return dp[idx][isHeld] = max(buy, notBuy);
    }
    int sell = prices[idx] + solveM(idx+1, prices, !isHeld, fee, dp);
    int notSell = solveM(idx+1, prices, isHeld, fee, dp);
    return dp[idx][isHeld] = max(sell, notSell);
}

// Approach: Tabulation
// Time Complexity: O(n*2)
// Reason: Nested for loops
// Space Complexity: O(n*2)
// Reason: Dp Array O(n*2)
int solveT(vector<int> &prices, int fee) {
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int> (2));
    for(int i=n-1; i>=0; i--) {
        for(int j=1; j>=0; j--) {
            if(!j) {
                int buy = - prices[i] - fee + dp[i+1][!j];
                int notBuy = dp[i+1][j];
                dp[i][j] = max(buy, notBuy);
            }
            else {
                int sell = prices[i] + dp[i+1][!j];
                int notSell = dp[i+1][j];
                dp[i][j] = max(sell, notSell);
            }
        }
    }
    return dp[0][0];
}

// Approach: Space Optimized
// Time Complexity: O(n*2)
// Reason: Nested loop
// Space Complexity: O(1)
// Reason: 2 Dp array of size 2
int solveS(vector<int> &prices, int fee) {
    int n = prices.size();
    vector<int> next(2);
    vector<int> curr(2);
    for(int i=n-1; i>=0; i--) {
        for(int j=1; j>=0; j--) {
            if(!j) {
                int buy = - prices[i] - fee + next[!j];
                int notBuy = next[j];
                curr[j] = max(buy, notBuy);
            }
            else {
                int sell = prices[i] + next[!j];
                int notSell = next[j];
                curr[j] = max(sell, notSell);
            }
        }
        next = curr;
    }
    return next[0];
    }

int main() {
    vector<int> prices {1, 3, 2, 8, 4, 9};
    int fee = 2;
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int> (2, -1)); // For Memoization
    
    cout << solveR(0, prices, false, fee) << "\n";
    cout << solveM(0, prices, false, fee, dp) << "\n";
    cout << solveT(prices, fee) << "\n";
    cout << solveS(prices, fee);
    
    return 0;
}

/*
Output of the program:
8
8
8
8
*/