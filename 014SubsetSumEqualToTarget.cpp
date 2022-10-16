// Author: REET
// Problem: Subset Sum Equal to K
// Link: https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: Take or not take
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
bool solveR(int i, int target, vector<int> &arr) {
    if(target==0) {
        return true;
    }
    if(i==0) {
        return arr[0] == target;
    }
    bool notPick = solveR(i-1, target, arr);
    bool pick = false;
    if(target>=arr[i]) {
        pick = solveR(i-1, target-arr[i], arr);
    }
    return pick or notPick;
}

// Approach: Memoization
// Time Complexity: O(n*target)
// Reason: That much state is possible
// Space Complexity: O(n*target)
// Reason: Dp array O(n*target) + Auxiliary Stack Space O(n)
bool solveM(int i, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if(target==0) {
        return true;
    }
    if(i==0) {
        return arr[0] == target;
    }
    bool notPick = solveM(i-1, target, arr, dp);
    bool pick = false;
    if(target>=arr[i]) {
        pick = solveM(i-1, target-arr[i], arr, dp);
    }
    return pick or notPick;
}

// Approach: Tabulation
// Time Complexity: O(n*target)
// Reason: Two nested loops
// Space Complexity: O(n*target)
// Reason: Dp Array O(n*target)
bool solveT(int target, vector<int> &arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int> (target)); // For Memoization
    for(int i=0; i<n; i++) {
        dp[i][0] = true;
    }
    if(arr[0]>=target) {
        dp[0][arr[0]] = true;
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<=target; j++) {
            bool notPick = dp[i-1][j];
            bool pick = false;
            if(target>=arr[i]) {
                pick = dp[i-1][j-arr[i]];
            }
            dp[i][j] = pick or notPick;
        }
    }
    return dp[n-1][target];
}

// Approach: Space Optimized
// Time Complexity: O(n*target)
// Reason: Two nested loops
// Space Complexity: O(n)
// Reason: Dp Array O(n)
bool solveS(int target, vector<int> &arr) {
    int n = arr.size();
    vector<bool> prev(target+1);
    vector<bool> curr(target+1);
    prev[0] = curr[0] = true;
    if(arr[0]>=target) {
        prev[arr[0]] = true;
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<=target; j++) {
            bool notPick = prev[j];
            bool pick = false;
            if(target>=arr[i]) {
                pick = prev[j-arr[i]];
            }
            curr[j] = pick or notPick;
        }
        prev = curr;
    }
    return prev[target];
}

int main() {
    int n = 4;
    int k = 5;
    vector<int> arr{4, 3, 2, 1};
    vector<vector<int>> dp(n, vector<int> (1e3+1)); // For Memoization
    
    cout << boolalpha;
    cout << solveR(n-1, k, arr) << "\n";
    cout << solveM(n-1, k, arr, dp) << "\n";
    cout << solveT(k, arr) << "\n";
    cout << solveS(k, arr);
    
    return 0;
}

/*
Output of the program:
true
true
true
true
*/