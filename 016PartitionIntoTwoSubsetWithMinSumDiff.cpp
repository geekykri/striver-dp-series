// Author: REET
// Problem: Partition a set into two subsets such that the difference of subset sums is minimum
// Link: https://www.codingninjas.com/codestudio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494

#include <bits/stdc++.h>
using namespace std;

// Approach: Tabulation
// Time Complexity: O(n*target)
// Reason: For computing sum O(n) + Nested loop O(n*target) + Finding min diff O(n)
// Space Complexity: O(n*target)
// Reason: Dp array O(n*target)
int solveT(vector<int> &arr) {
    int ts = accumulate(begin(arr), end(arr), 0);
    int t = ts/2;
    int n = arr.size();
    vector<vector<bool>> dp(n, vector<bool> (ts+1));
    if(arr[0]>=t) {
        dp[0][arr[0]] = true;
    }
    for(int i=0; i<n; i++) {
        dp[i][0] = true;
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<=t; j++) {
            bool notPick = dp[i-1][j];
            bool pick = false;
            if(arr[i]<=j) {
                pick = dp[i-1][j-arr[i]];
            }
            dp[i][j] = pick or notPick;
        }
    }
    cout << boolalpha;
    for(int i=0; i<n; i++) {
        for(int j=0; j<=t; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    int diff = INT_MAX;
    for(int j=0; j<=t; j++) {
        if(dp[n-1][j]) {
            diff = min(diff, abs(j-(ts-j)));
        }
    }
    return diff;
}

// Approach: Space Optimized
// Time Complexity: O(n*target)
// Reason: For computing sum [O(n)] + Nested loop [O(n*target)] + Finding min diff [O(n)]
// Space Complexity: O(target)
// Reason: Dp array O(target)
int solveS(vector<int> &arr) {
    int ts = accumulate(begin(arr), end(arr), 0);
    int t = ts/2;
    int n = arr.size();
    vector<bool> prev(ts+1);
    vector<bool> curr(ts+1);
    vector<vector<bool>> dp(n, vector<bool> (ts+1));
    prev[0] = curr[0] = true;
    if(arr[0]>=t) {
        prev[arr[0]] = true;
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<=t; j++) {
            bool notPick = prev[j];
            bool pick = false;
            if(arr[i]<=j) {
                pick = prev[j-arr[i]];
            }
            curr[j] = pick or notPick;
        }
        prev = curr;
    }
    int diff = INT_MAX;
    for(int j=0; j<=t; j++) {
        if(prev[j]) {
            diff = min(diff, abs(j-(ts-j)));
        }
    }
    return diff;
}

int main() {
    vector<int> arr {1, 2, 2, 3};
    
    cout << solveT(arr) << "\n";
    cout << solveS(arr) << "\n";
    
    return 0;
}