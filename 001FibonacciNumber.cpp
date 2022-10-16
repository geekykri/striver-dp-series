// Author: REET
// Problem: Fibonacci Number
// Link: https://leetcode.com/problems/fibonacci-number/

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(2^n)
// Reason: Two different calls for every value of n
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
long long solveR(long long n) {
    if(n<=1) {
        return n;
    }
    return solveR(n-1) + solveR(n-2);
}

// Approach: Memoization
// Time Complexity: O(n)
// Reason: Storing results in Dp Array 
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n)
long long solveM(int n, vector<long long> &dp) {
    if(n<=1) {
        return n;
    }
    if(dp[n]!= -1) {
        return dp[n];
    }
    return dp[n] = solveM(n-1,dp) + solveM(n-2,dp);
}


// Approach: Tabulation
// Time Complexity: O(n)
// Reason: Storing results in Dp Array 
// Space Complexity: O(n)
// Reason: Dp Array O(n)
long long solveT(int n) {
    vector<long long> t(n+1);  
    t[1] = 1;
    for(int i=2; i<=n; i++) {
        t[i] = t[i-1] + t[i-2];
    }
    return t[n];
}

// Approach: Space Optimized
// Time Complexity: O(n)
// Reason: Using variables to store previous 2 states 
// Space Complexity: O(1)
// Reason: Using variables
long long solveS(int n) {
    long long prev2 = 0;
    long long prev = 1;
    if(n==0) {
        return prev2;
    }
    for(int i=2; i<=n; i++) {
        long long curr = prev+prev2;
        prev2 = prev;
        prev = curr;
    }
    return prev;
}

int main() {
    int n = 80;
    vector<long long> dp(n+1, -1); // For Memoization

    cout << solveR(10) << "\n";
    cout << solveM(n, dp) << "\n";
    cout << solveT(n) << "\n";
    cout << solveS(n);
    
    return 0;
}

/*
Output of the program: 
55
23416728348467685
23416728348467685
23416728348467685
*/