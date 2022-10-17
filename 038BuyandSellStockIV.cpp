// Author: REET
// Problem: Buy and Sell Stock IV
// Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: Exponential
// Reason: Exponential calls
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int idx, vector<int> &prices, bool isHeld, int k) {
    if(idx==prices.size() or k==0) {
        return 0;
    }
    if(!isHeld) {
        int buy = -prices[idx] + solveR(idx+1, prices, !isHeld, k);
        int notBuy = solveR(idx+1, prices, isHeld, k);
        return max(buy, notBuy);
    }
    int sell = prices[idx] + solveR(idx+1, prices, !isHeld, k-1);
    int notSell = solveR(idx+1, prices, isHeld, k);
    return max(sell, notSell);
}

// Approach: Memoization
// Time Complexity: O(n*2*k)
// Reason: Using previous stored values from dp array
// Space Complexity: O(n*2*k)
// Reason: Auxiliary Stack Space O(n) + Dp array O(n*2*k)
int solveM(int idx, vector<int> &prices, bool isHeld, int k, vector<vector<vector<int>>> &dp) {
    if(idx==prices.size() or k==0) {
        return 0;
    }
    if(dp[idx][isHeld][k]!=-1) {
        return dp[idx][isHeld][k];
    }
    if(!isHeld) {
        int buy = -prices[idx] + solveM(idx+1, prices, !isHeld, k, dp);
        int notBuy = solveM(idx+1, prices, isHeld, k, dp);
        return dp[idx][isHeld][k] = max(buy, notBuy);
    }
    int sell = prices[idx] + solveM(idx+1, prices, !isHeld, k-1, dp);
    int notSell = solveM(idx+1, prices, isHeld, k, dp);
    return dp[idx][isHeld][k] = max(sell, notSell);
}

// Approach: Tabulation
// Time Complexity: O(n*2*k)
// Reason: Nested for loops
// Space Complexity: O(n*2*k)
// Reason: Dp array O(n*2*k)
int solveT(vector<int> &prices, int lim) {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (lim+1)));
    for(int idx=n-1; idx>=0; idx--) {
        for(int isHeld=1; isHeld>=0; isHeld--) {
            for(int k=lim; k>0; k--) {
                if(!isHeld) {
                    int buy = -prices[idx] + dp[idx+1][!isHeld][k];
                    int notBuy = dp[idx+1][isHeld][k];
                    dp[idx][isHeld][k] = max(buy, notBuy);
                }
                else {
                    int sell = prices[idx] + dp[idx+1][!isHeld][k-1];
                    int notSell = dp[idx+1][isHeld][k];
                    dp[idx][isHeld][k] = max(sell, notSell);
                }
            }
        }
    }
    return dp[0][0][lim];
}

// Approach: Space Optimized
// Time Complexity: O(n*2*k)
// Reason: Nested for loops
// Space Complexity: O(k)
// Reason: 2 Dp array of size 2*k
int solveS(vector<int> &prices, int lim) {
    int n = prices.size();
    vector<vector<int>> next(2, vector<int> (lim+1));
    vector<vector<int>> curr(2, vector<int> (lim+1));
    for(int idx=n-1; idx>=0; idx--) {
        for(int isHeld=1; isHeld>=0; isHeld--) {
            for(int k=lim; k>0; k--) {
                if(!isHeld) {
                    int buy = -prices[idx] + next[!isHeld][k];
                    int notBuy = next[isHeld][k];
                    curr[isHeld][k] = max(buy, notBuy);
                }
                else {
                    int sell = prices[idx] + next[!isHeld][k-1];
                    int notSell = next[isHeld][k];
                    curr[isHeld][k] = max(sell, notSell);
                }
            }
        }
        next = curr;
    }
    return next[0][lim];
}

int main() {
    vector<int> prices {3,2,6,5,0,3};
    int n = prices.size();
    int lim = 2;
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (lim+1, -1))); // For Memoization
    
    cout << solveR(0, prices, false, lim) << "\n";
    cout << solveM(0, prices, false, lim, dp) << "\n";
    cout << solveT(prices, lim) << "\n";
    cout << solveS(prices, lim);
    
    return 0;
}

/*
Output of the program:
7
7
7
7
*/