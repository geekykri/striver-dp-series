// Author: REET
// Problem: Print Longest Common Subsequence

#include <bits/stdc++.h>
using namespace std;

// Approach: Tabulation
// Time Complexity: O(n*m)
// Reason: Nested for loops
// Space Complexity: O(n*m)
// Reason: Dp Array O(n*m)
string solveT(string &text1, string &text2) {
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n, vector<int> (m));
    for(int idx1=0; idx1<n; idx1++) {
        for(int idx2=0; idx2<m; idx2++) {
            if(text1[idx1]==text2[idx2]) {
                dp[idx1][idx2] = 1;
                if(idx1>0 and idx2>0) {
                    dp[idx1][idx2] += dp[idx1-1][idx2-1];
                }
            }
            else {
                int l = INT_MIN;
                int r = INT_MIN;
                if(idx1>0) {
                    l = dp[idx1-1][idx2];
                }
                if(idx2>0) {
                    r = dp[idx1][idx2-1];
                }
                if(l==INT_MIN and r==INT_MIN) {
                    dp[idx1][idx2] = 0;
                }
                else {
                    dp[idx1][idx2] = max(l, r);
                }
            }
        }
    }
    int i = n-1;
    int j = m-1;
    string res;
    while(i>=0 and j>=0) {
        if(text1[i]==text2[j] and ((i==0 and j==0) or (i>0 and j>0 and dp[i][j] == dp[i-1][j-1]+1))) {
            res += text1[i];
            i--;
            j--;
        }
        else {
            if(i>0 and dp[i-1][j] == dp[i][j]) {
                i--;
            }
            else {
                j--;
            }
        }
    }
    reverse(begin(res), end(res));
    return res;
}

int main() {
    string text1 = "abcde";
    string text2 = "ace"; 
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n, vector<int> (m, -1)); // For Memoization
    
    cout << solveT(text1, text2);
    
    return 0;
}

/*
Output of the program:
ace
*/