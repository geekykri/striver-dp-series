// Author: REET
// Problem: Longest Common Substring
// Link: https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1

#include <bits/stdc++.h>
using namespace std;

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp Array O(n*m)
int solveT(string &text1, string &text2, int n, int m) {
    vector<vector<int>> dp(n+1, vector<int> (m+1));
    int res = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(text1[i-1]==text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                res = max(res, dp[i][j]);
            }
        }
    }
    return res;
}

// Approach: Space Optimized
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(m)
// Reason: 2 Dp Array O(m+m)
int solveS(string &text1, string &text2, int n, int m) {
    vector<int> prev(m+1);
    vector<int> curr(m+1);
    int res = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(text1[i-1]==text2[j-1]) {
                curr[j] = prev[j-1] + 1;
                res = max(res, curr[j]);
            }
            else {
                // This line is very much important
                // Otherwise it'll give wrong output
                // as previous value remains stored in curr
                curr[j] = 0;
            }
        }
        prev = curr;
    }
    return res;
}

int main() {
    string text1 = "acdghr";
    string text2 = "abcdgh";
    int n = text1.size();
    int m = text2.size();
    
    cout << solveT(text1, text2, n, m) << "\n";
    cout << solveS(text1, text2, n, m);
    
    return 0;
}

/*
Output of the program:
4
4
*/