// Author: REET
// Problem: Maximum Path Sum in the Matrix
// Link: https://www.codingninjas.com/codestudio/problems/maximum-path-sum-in-the-matrix_797998

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(3^(m*n))
// Reason: Performing up, diagonally left and right at every cell
// Space Complexity: O(Length of the longest path with maximum sum)
// Reason: That many calls will be made
int solveR(int x, int y, vector<vector<int>> &m) {
    if(y<0 or y>=m[x].size()) {
        return INT_MIN;
    }
    if(x==0) {
        return m[x][y];
    }
    int up = solveR(x-1, y, m);
    int dl = solveR(x-1, y-1, m);
    int dr = solveR(x-1, y+1, m);
    return m[x][y] + max(up, max(dl, dr));
}

// Approach: Memoization
// Time Complexity: O(m*n)
// Reason: One time computation only, after that value is being reused
// Space Complexity: O(Length of the longest path with maximum sum)
// Reason: That many calls will be made
int solveM(int x, int y, vector<vector<int>> &m, vector<vector<int>> &dp) {
    if(y<0 or y>=m[x].size()) {
        return INT_MIN;
    }
    if(x==0) {
        return m[x][y];
    }
    if(dp[x][y]!=-1) {
        return dp[x][y];
    }
    int up = solveM(x-1, y, m, dp);
    int dl = solveM(x-1, y-1, m, dp);
    int dr = solveM(x-1, y+1, m, dp);
    return dp[x][y] = m[x][y] + max(up, max(dl, dr));
}

// Approach: Tabulation
// Time Complexity: O(m*n)
// Reason: Taking up value from the previous state, two loops
// Space Complexity: O(m*n)
// Reason: Dp array O(m*n)
int solveT(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[m-1].size();
    vector<vector<int>> dp(m, vector<int> (n));
    for(int j=0; j<n; j++) {
        dp[0][j] = matrix[0][j];
    }
    for(int x=1; x<m; x++) {
        for(int y=0; y<n; y++) {
            int up = INT_MIN;
            int dl = INT_MIN;
            int dr = INT_MIN;
            up = dp[x-1][y];
            if(y>0) {
                dl = dp[x-1][y-1];                
            }
            if(y<n-1) {
                dr = dp[x-1][y+1];
            }
            dp[x][y] = matrix[x][y] + max(up, max(dl, dr));
        }
    }
    return *max_element(dp[m-1].begin(), dp[m-1].end());
}

// Approach: Space Optimized
// Time Complexity: O(m*n)
// Reason: Taking up value from the previous state, two loops
// Space Complexity: O(n)
// Reason: Using row size vector to store the states
int solveS(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[m-1].size();
    vector<int> prev(n);
    for(int j=0; j<n; j++) {
        prev[j] = matrix[0][j];
    }
    for(int x=1; x<m; x++) {
        vector<int> curr(n);
        for(int y=0; y<n; y++) {
            int up = INT_MIN;
            int dl = INT_MIN;
            int dr = INT_MIN;
            up = prev[y];
            if(y>0) {
                dl = prev[y-1];                
            }
            if(y<n-1) {
                dr = prev[y+1];
            }
            curr[y] = matrix[x][y] + max(up, max(dl, dr));
        }
        prev = curr;
    }
    return *max_element(prev.begin(), prev.end());
}

int main() {
    vector<vector<int>> matrix {{1, 2, 10, 4}, {100, 3, 2, 1}, {1, 1, 20, 2}, {1, 2, 2, 1}};
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> dp(n, vector<int> (n, -1)); // For Memoization
    
    int res = INT_MIN;
    for(int j=0; j<n; j++) {
        res = max(res, solveR(m-1, j, matrix));
    }
    cout << res << "\n";
    res = INT_MIN;
    for(int j=0; j<n; j++) {
        res = max(res, solveM(m-1, j, matrix, dp));
    }
    cout << res << "\n";
    res = INT_MIN;
    cout << solveT(matrix) << "\n";
    cout << solveS(matrix);
    
    return 0;
}

/*
Output of the program:
105
105
105
105
*/