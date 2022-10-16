// Author: REET
// Problem: Maximum Sum of Non Adjacent Element
// Link: https://leetcode.com/problems/house-robber/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: Pick & Not Pick
// Space Complexity: O(n)
// Reason: Recursive Stack Space
int solveR(int idx, vector<int> &nums) {
    if(idx<0) {
        return 0;
    }
    if(idx==0) {
        return nums[0];
    }
    int pick = nums[idx] + solveR(idx-2, nums);
    int notPick = solveR(idx-1, nums);
    
    return max(pick, notPick);
}

// Approach: Memoization
// Time Complexity: O(n)
// Reason: Storing results in DP Array 
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n)
int solveM(int idx, vector<int> &nums, vector<int> &dp) {
    if(idx<0) {
        return 0;
    }
    if(idx==0) {
        return nums[0];
    }
    if(dp[idx]!=-1) {
        return dp[idx];
    }
    int pick = nums[idx] + solveM(idx-2, nums, dp);
    int notPick = solveM(idx-1, nums, dp);
    
    return dp[idx] = max(pick, notPick);
}

// Approach: Tabulation
// Time Complexity: O(n)
// Reason: Storing results in DP Array 
// Space Complexity: O(n)
// Reason: Dp Array O(n)
int solveT(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    dp[1] = nums[0];
    for(int i=2; i<=n; i++) {
        int pick = nums[i-1] + dp[i-2];
        int notPick = dp[i-1];
        dp[i] = max(pick, notPick);
    }
    return dp[n];
}

// Approach: Space Optimized
// Time Complexity: O(n)
// Reason: Using variables to store previous 2 states 
// Space Complexity: O(1)
// Reason: Using variables
int solveS(vector<int> &nums) {
    int n = nums.size();
    if(n==1) {
        return nums[0];
    }
    int prev2 = 0;
    int prev1 = nums[0];
    int curr = nums[0];
    for(int i=1; i<n; i++) {
        int pick = nums[i] + prev2;
        int notPick = prev1;
        curr = max(pick, notPick);
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

int main() {
    vector<int> nums{2, 1, 4, 9};
    int n = nums.size();
    vector<int> dp(n, -1); // For Memoization

    cout << solveR(n-1, nums) << "\n";
    cout << solveM(n-1, nums, dp) << "\n";
    cout << solveT(nums) << "\n";
    cout << solveS(nums) << "\n";

    return 0;
}

/*
Output of the program: 
11
11
11
11
*/