// Author: REET
// Problem: Shortest Common Supersequence
// Link: https://leetcode.com/problems/shortest-common-supersequence

#include <bits/stdc++.h>
using namespace std;

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp array O(n*m)
void solveT(string &s, string &t, vector<vector<int>> &dp) {
    int n = s.size();
    int m = t.size();
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(s[i-1]==t[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
}

int main() {
    string s = "abac";
    string t = "cab";
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1));
    
    // Fill the dp table
    solveT(s, t, dp);
    int i = n;
    int j = m;
    string res;
    while(i>0 and j>0) {
        if(s[i-1]==t[j-1]) {
            res += s[i-1];
            i--;
            j--;
        }
        else if(dp[i-1][j] > dp[i][j-1]) {
            res += s[i-1];
            i--;
        }
        else {
            res += t[j-1];
            j--;
        }
    }
    while(i>0) {
        res += s[i-1];
        i--;
    }
    while(j>0) {
        res += t[j-1];
        j--;
    }
    reverse(begin(res), end(res));
    cout << res;

    return 0;
}

/*
Output of the program:
cabac
*/