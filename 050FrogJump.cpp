// Author: REET
// Problem: Frog Jump
// Link: https://www.codingninjas.com/codestudio/problems/frog-jump_3621012

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: Exponential
// Reason: Exponential Calls
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int idx, vector<int> &heights) {
    if(idx==0) {
        return 0;
    }
    
    int oneStep = INT_MAX;
    int twoStep = INT_MAX;
    
    oneStep = abs(heights[idx-1] - heights[idx]) + solveR(idx-1, heights);    
    if(idx>1) {
        twoStep = abs(heights[idx-2] - heights[idx]) + solveR(idx-2, heights);    
    }
    
    return min(oneStep, twoStep);
}

// Approach: Memoization
// Time Complexity: O(n)
// Reason: Storing results in Dp Array 
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n)
int solveM(int idx, vector<int> &heights, vector<int> &dp) {
    if(idx==0) {
        return 0;
    }
    
    if(dp[idx]!=-1) {
        return dp[idx];
    }
    
    int oneStep = INT_MAX;
    int twoStep = INT_MAX;
    
    oneStep = abs(heights[idx-1] - heights[idx]) + solveM(idx-1, heights, dp);    
    if(idx>1) {
        twoStep = abs(heights[idx-2] - heights[idx]) + solveM(idx-2, heights, dp);    
    }
    
    return dp[idx] = min(oneStep, twoStep);
}

// Approach: Tabulation
// Time Complexity: O(n)
// Reason: Storing results in Dp Array 
// Space Complexity: O(n)
// Reason: Dp Array O(n)
int solveT(int n, vector<int> &heights) {
    if(n<=1) {
        return n;
    }
    vector<int> t(n);
    for(int i=1; i<n; i++) {
        int oneStep = INT_MAX;
        int twoStep = INT_MAX;
        oneStep = abs(heights[i-1] - heights[i]) + t[i-1];    
        if(i>1) {
            twoStep = abs(heights[i-2] - heights[i]) + t[i-2];    
        }
        t[i] = min(oneStep, twoStep);
    }
    return t[n-1];
}

// Approach: Space Optimized
// Time Complexity: O(n)
// Reason: Using variables to store previous 2 states 
// Space Complexity: O(1)
// Reason: Using variables
int solveS(int n, vector<int> &heights) {
    if(n<=1) {
        return n;
    }
    int prev = 0;
    int prev2 = 0;
    for(int i=1; i<n; i++) {
        int oneStep = INT_MAX;
        int twoStep = INT_MAX;
        oneStep = abs(heights[i-1] - heights[i]) + prev;    
        if(i>1) {
            twoStep = abs(heights[i-2] - heights[i]) + prev2;    
        }
        int curr = min(oneStep, twoStep);
        prev2 = prev;
        prev = curr;
    }
    return prev;
}

int main() {
    vector<int> heights{10, 20, 30, 10};
    int n = heights.size();
    vector<int> dp(n+1, -1); // For Memoization

    cout << solveR(n-1, heights) << "\n";
    cout << solveM(n-1, heights, dp) << "\n";
    cout << solveT(n, heights) << "\n";
    cout << solveS(n, heights) << "\n";

    return 0;
}

/*
Output of the program: 
20
20
20
20
*/