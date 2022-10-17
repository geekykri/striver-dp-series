// Author: REET
// Problem: Longest Increasing Subsequence
// Link: https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: 2 calls at every instance
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int idx, vector<int> &nums, int prev) {
    if(idx==nums.size()) {
        return 0;
    }
    int notTake = solveR(idx+1, nums, prev);
    int take = 0;
    if(prev==-1 or nums[idx]>nums[prev]) {
        take = 1 + solveR(idx+1, nums, idx);
    }
    return max(take, notTake);
}

// Approach: Memoization
// Time Complexity: O(n*n)
// Reason: That many states
// Space Complexity: O(n*n)
// Reason: Dp array O(n*n) + Auxiliary Stack Space O(n)
int solveM(int idx, vector<int> &nums, int prev, vector<vector<int>> &dp) {
    if(idx==nums.size()) {
        return 0;
    }
    if(dp[idx][prev+1]!=-1) {
        return dp[idx][prev+1];
    }
    int notTake = solveM(idx+1, nums, prev, dp);
    int take = 0;
    if(prev==-1 or nums[idx]>nums[prev]) {
        take = 1 + solveM(idx+1, nums, idx, dp);
    }
    return dp[idx][prev+1] = max(take, notTake);
}

// Approach: Tabulation
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n*n)
// Reason: Dp array O(n*n)
int solveT(vector<int> &nums) {
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int> (n+1));
    for(int idx=n-1; idx>=0; idx--) {
        for(int prev=idx-1; prev>=-1; prev--) {
            int notTake = dp[idx+1][prev+1];
            int take = 0;
            if(prev==-1 or nums[idx]>nums[prev]) {
                take = 1 + dp[idx+1][idx+1];
            }
            dp[idx][prev+1] = max(take, notTake);
        }
    }
    return dp[0][0];
}

// Approach: Space Optimized
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n)
// Reason: 2 dp array O(n)
int solveS(vector<int> &nums) {
    int n = nums.size();
    vector<int> next(n+1);
    vector<int> curr(n+1);
    for(int idx=n-1; idx>=0; idx--) {
        for(int prev=idx-1; prev>=-1; prev--) {
            int notTake = next[prev+1];
            int take = 0;
            if(prev==-1 or nums[idx]>nums[prev]) {
                take = 1 + next[idx+1];
            }
            curr[prev+1] = max(take, notTake);
        }
        next = curr;
    }
    return next[0];
} 

// Approach: Tabulation
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n)
// Reason: Dp array O(n)
int solveT2(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    int maxi = 1;
    for(int i=0; i<n; i++) {
        for(int prev=0; prev<i; prev++) {
            if(nums[prev]<nums[i]) {
                dp[i] = max(dp[i], 1 + dp[prev]);
            }
        }
        maxi = max(maxi, dp[i]);
    }
    return maxi;
}

int main() {
    vector<int> nums {10,9,2,5,3,7,101,18};
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int> (n+1, -1)); // For Memoization

    cout << solveR(0, nums, -1) << "\n";
    cout << solveM(0, nums, -1, dp) << "\n";
    cout << solveT(nums) << "\n";
    cout << solveS(nums) << "\n";
    cout << solveT2(nums);

    return 0;
}

/*
Output of the program:
4
4
4
4
4
*/