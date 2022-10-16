// Author: REET
// Problem: Ninja's Training
// Link: https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003

#include <bits/stdc++.h>
using namespace std;

// Approach: Memoization
// Time Complexity: O(N*4*3)
// Reason: Pick & Not Pick
// Space Complexity: O(n) + O(N*4)
// Reason: Auxiliary Stack Space O(n) + Dp Array O(N*4)
int solveM(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp) {
    if(day==0) {
        int maxi = 0;
        for(int task=0; task<3; task++) {
            if(task!=last) {
                maxi = max(maxi, points[day][task]);
            }
        }
        return maxi;
    }
    
    if(dp[day][last]!=-1) {
        return dp[day][last];
    }
    
    int maxi = 0;
    for(int task=0; task<3; task++) {
        if(task!=last) {
            maxi = max(maxi, points[day][task]+solveM(day-1, task, points, dp));
        }
    }
    
    return dp[day][last] = maxi;
}

// Approach: Tabulation
// Time Complexity: O(N*4*3)
// Reason: Pick & Not Pick
// Space Complexity: O(N*4)
// Reason: Dp Array O(N*4)
int solveT(int n, vector<vector<int>> &points) {
    vector<vector<int>> dp(n, vector<int> (4, -1));
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));
    
    for(int day=1; day<n; day++) {
        for(int last=0; last<4; last++) {
            int maxi = 0;
            for(int task=0; task<3; task++) {
                if(task!=last) {
                    maxi = max(maxi, points[day][task]+dp[day-1][task]);            
                }
            }
            dp[day][last] = maxi;
        }
    }
    return dp[n-1][3];
}

// Approach: Space Optimized
// Time Complexity: O(N*4)*3
// Reason: Pick & Not Pick
// Space Complexity: O(1)
// Reason: Dp Array O(1)
int solveS(int n, vector<vector<int>> &points) {
    vector<int> dp(4);
    dp[0] = max(points[0][1], points[0][2]);
    dp[1] = max(points[0][0], points[0][2]);
    dp[2] = max(points[0][0], points[0][1]);
    dp[3] = max(points[0][0], max(points[0][1], points[0][2]));
    
    for(int day=1; day<n; day++) {
        vector<int> tmp(4);
        for(int last=0; last<4; last++) {
            int maxi = 0;
            for(int task=0; task<3; task++) {
                if(task!=last) {
                    maxi = max(maxi, points[day][task]+dp[task]); 
                }
            }
            tmp[last] = maxi;
        }
        dp = tmp;
    }
    return dp[3]; 
}

int main() {
    int n = 3;
    vector<vector<int>> points {{18, 11, 19}, {4, 13, 7}, {1, 8, 13}};
    vector<vector<int>> dp(n, vector<int> (4, -1));
    
    cout << solveM(n-1, 3, points, dp) << "\n";
    cout << solveT(3, points) << "\n";
    cout << solveS(3, points);

    return 0;
}

/*
Output of the program: 
45
45
45
*/