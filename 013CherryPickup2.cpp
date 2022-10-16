// Author: REET
// Problem: Chocolate Pickup
// Link: https://www.codingninjas.com/codestudio/problems/ninja-and-his-friends_3125885

#include <bits/stdc++.h>
using namespace std;

// Approach: Recursive
// Time Complexity: O(3^n * 3^n) ~= exponential
// Reason: Number of rows(n), For every column Alice & Bob has 3 options
// Space Complexity: O(n)
// Reason: Auxiliary Stack Space O(n)
int solveR(int i, int j1, int j2, int m, int n, vector<vector<int>> &grid) {
    if(j1<0 or j2<0 or j1>=n or j2>=n) {
        return -1e8;
    }
    if(i==m-1) {
        if(j1==j2) {
            return grid[i][j1];
        }
        return grid[i][j1] + grid[i][j2];
    }
    int maxi = -1e8;
    for(int dj1=-1; dj1<=1; dj1++) {
        for(int dj2=-1; dj2<=1; dj2++) {
            int value = 0;
            if(j1==j2) {
                value = grid[i][j1];
            }
            else {
                value = grid[i][j1] + grid[i][j2];
            }
            value += solveR(i+1, j1+dj1, j2+dj2, m, n, grid);
            maxi = max(maxi, value);
        }
    }
    return maxi;
}

// Approach: Memoization
// Time Complexity: O(n*m*m*9)
// Reason: Internal loop 3*3 [Need to consider as it is close to 10]
// Space Complexity: O(n*m*m)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(n*m*m)
int solveM(int i, int j1, int j2, int m, int n, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp) {
    if(j1<0 or j2<0 or j1>=n or j2>=n) {
        return -1e8;
    }
    if(i==m-1) {
        if(j1==j2) {
            return grid[i][j1];
        }
        return grid[i][j1] + grid[i][j2];
    }
    if(dp[i][j1][j2]!=-1) {
        return dp[i][j1][j2];
    }
    int maxi = -1e8;
    for(int dj1=-1; dj1<=1; dj1++) {
        for(int dj2=-1; dj2<=1; dj2++) {
            int value = 0;
            if(j1==j2) {
                value = grid[i][j1];
            }
            else {
                value = grid[i][j1] + grid[i][j2];
            }
            value += solveM(i+1, j1+dj1, j2+dj2, m, n, grid, dp);
            maxi = max(maxi, value);
        }
    }
    return dp[i][j1][j2] = maxi;
}

// Approach: Tabulation
// Time Complexity: O(m*n*n*9)
// Reason: Nested loops
// Space Complexity: O(m*n*n)
// Reason: Dp Array O(m*n*n)
int solveT(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>> (n, vector<int> (n)));
    for(int j1=0; j1<n; j1++) {
        for(int j2=0; j2<n; j2++) {
            if(j1==j2) {
                dp[m-1][j1][j2] = grid[m-1][j1];
            }
            else {
                dp[m-1][j1][j2] = grid[m-1][j1] + grid[m-1][j2];
            }
        }
    }
    for(int i=m-2; i>=0; i--) {
        for(int j1=0; j1<n; j1++) {
            for(int j2=0; j2<n; j2++) {
                int maxi = -1e8;
                for(int dj1=-1; dj1<=1; dj1++) {
                    for(int dj2=-1; dj2<=1; dj2++) {
                        int value = 0;
                        if(j1==j2) {
                            value = grid[i][j1];
                        }
                        else {
                            value = grid[i][j1] + grid[i][j2];
                        }
                        if(j1+dj1>=0 and j1+dj1<n and j2+dj2>=0 and j2+dj2<n) {
                            value += dp[i+1][j1+dj1][j2+dj2];                        
                        }
                        else {
                            value += -1e8;
                        }
                        maxi = max(maxi, value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    return dp[0][0][n-1];
}

// Approach: Space Optimized
// Time Complexity: O(m*n*n*9)
// Reason: Nested loops
// Space Complexity: O(n*n)
// Reason: Dp Array O(n*n)
int solveS(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> prev(n, vector<int>(n));
    vector<vector<int>> curr(n, vector<int>(n));
    for(int j1=0; j1<n; j1++) {
        for(int j2=0; j2<n; j2++) {
            if(j1==j2) {
                prev[j1][j2] = grid[m-1][j1];
            }
            else {
                prev[j1][j2] = grid[m-1][j1] + grid[m-1][j2];
            }
        }
    }
    for(int i=m-2; i>=0; i--) {
        for(int j1=0; j1<n; j1++) {
            for(int j2=0; j2<n; j2++) {
                int maxi = -1e8;
                for(int dj1=-1; dj1<=1; dj1++) {
                    for(int dj2=-1; dj2<=1; dj2++) {
                        int value = 0;
                        if(j1==j2) {
                            value = grid[i][j1];
                        }
                        else {
                            value = grid[i][j1] + grid[i][j2];
                        }
                        if(j1+dj1>=0 and j1+dj1<n and j2+dj2>=0 and j2+dj2<n) {
                            value += prev[j1+dj1][j2+dj2];                        
                        }
                        else {
                            value += -1e8;
                        }
                        maxi = max(maxi, value);
                    }
                }
                curr[j1][j2] = maxi;
            }
        }
        prev = curr;
    }
    return prev[0][n-1];
}

int main() {
    vector<vector<int>> grid {{2, 3, 1, 2}, {3, 4, 2, 2}, {5, 6, 3, 5}};
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>> (n, vector<int> (n, -1))); // For Memoization
    
    cout << solveR(0, 0, n-1, m, n, grid) << "\n";
    cout << solveM(0, 0, n-1, m, n, grid, dp) << "\n";
    cout << solveT(grid) << "\n";
    cout << solveS(grid);
    
    return 0;
}

/*
Output of the program:
21
21
21
21
*/