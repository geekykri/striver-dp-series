// Author: REET
// Problem: Climbing Stairs Jump Within K
// Link: https://takeuforward.org/data-structure/dynamic-programming-frog-jump-with-k-distances-dp-4/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(k^n)
// Reason: Solve(n-1)+Solve(n-2)+Solve(n-3)...(n-k)
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space
int solveR(int idx, int k, vector<int> &heights) {
    if(idx==0) {
        return 0;
    }

    int minEnergy = INT_MAX;
    int jump;

    for(int j=1; j<=k; j++) {
        if(idx-j>=0) {
            jump = solveR(idx-j, k, heights) + abs(heights[idx]-heights[idx-j]);
        }
        minEnergy = min(minEnergy, jump);
    }
    
    return minEnergy;
}

// Approach: Memoization
// Time Complexity: O(n*k)
// Reason: Storing results in DP Array 
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n)
int solveM(int idx, int k, vector<int> &heights, vector<int> &dp) {
    if(idx==0) {
        return 0;
    }
    
    if(dp[idx]!=-1) {
        return dp[idx];
    }

    int minEnergy = INT_MAX;
    int jump;

    for(int j=1; j<=k; j++) {
        if(idx-j>=0) {
            jump = solveM(idx-j, k, heights, dp) + abs(heights[idx]-heights[idx-j]);
        }
        minEnergy = min(minEnergy, jump);
    }
    
    return dp[idx] = minEnergy;
}

// Approach: Tabulation
// Time Complexity: O(n*k)
// Reason: Storing results in DP Array 
// Space Complexity: O(n)
// Reason: Dp Array O(n)
int solveT(int n, int k, vector<int> &heights) {
    if(n<=1) {
        return n;
    }
    vector<int> t(n);
    for(int i=1; i<n; i++) {
        int jump;
        int minEnergy = INT_MAX;
        for(int j=1; j<=k; j++) {
            if(i-j>=0) {
                jump = t[i-j] + abs(heights[i]-heights[i-j]);
            }
            minEnergy = min(minEnergy, jump);
        }
        t[i] = minEnergy;
    }
    return t[n-1];
}

int main() {
    vector<int> heights{10, 20, 30, 10};
    int n = heights.size();
    int k = 2;
    vector<int> dp(n+1, -1); // For Memoization

    cout << solveR(n-1, k, heights) << "\n";
    cout << solveM(n-1, k, heights, dp) << "\n";
    cout << solveT(n, k, heights) << "\n";
    // Space optimized soln is not feasible as we need to store
    // last K elements, which in the worst case can be O(n)
}

/*
Output of the program: 
20
20
20
*/