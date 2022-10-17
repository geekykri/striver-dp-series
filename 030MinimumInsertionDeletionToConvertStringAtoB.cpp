// Author: REET
// Problem: Minimum Insertion Deletion to Convert String A to B
// Link: https://www.codingninjas.com/codestudio/problem-details/can-you-make_4244510

#include <bits/stdc++.h>
using namespace std;

// Approach: Space Optimized
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n)
// Reason: Dp Array O(n+n)
int solveS(string &s, string &t) {
    int n = s.size();
    vector<int> prev(n+1);
    vector<int> curr(n+1);
    for(int idx1=1; idx1<=n; idx1++) {
        for(int idx2=1; idx2<=n; idx2++) {
            if(s[idx1-1]==t[idx2-1]) {
                curr[idx2] = 1 + prev[idx2-1];
            }
            else {
                curr[idx2] = max(prev[idx2], curr[idx2-1]);
            }
        }
        prev = curr;
    }
    return prev[n];
}

int main() {
    string s = "abcd";
    string t = "anc";
    int n = s.size();
    int m = t.size();
    
    // Find LCS -> Remove opn (m-LCS) Insertion opn (n-LCS)
    int lcs = solveS(s, t);
    cout << m+n-2*lcs;
    
    return 0;
}

/*
Output of the program:
3
*/