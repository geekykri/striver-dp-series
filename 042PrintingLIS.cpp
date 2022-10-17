// Author: REET
// Problem: Print Longest Increasing Subsequence
// Link: https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>
using namespace std;

// Approach: Tabulation
// Time Complexity: O(n*n)
// Reason: Nested for loops
// Space Complexity: O(n)
// Reason: Dp array O(n) + Hash array O(n)
void solveT(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    vector<int> hash(n);
    int maxi = 1;
    int idx = 0;
    for(int i=0; i<n; i++) {
        hash[i] = i;
        for(int prev=0; prev<i; prev++) {
            if(nums[prev]<nums[i] and dp[prev]+1 > dp[i]) {
                dp[i] = dp[prev]+1;
                hash[i] = prev;
            }
        }
        if(dp[i]>maxi) {
            idx = i;
            maxi = dp[i];
        }
    }
    cout << "Size of LIS: " << maxi << "\n";
    vector<int> tmp;
    tmp.push_back(nums[idx]);
    while(hash[idx]!=idx) {
        idx = hash[idx];
        tmp.push_back(nums[idx]);
    }
    reverse(begin(tmp), end(tmp));
    for(int el: tmp) {
        cout << el << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> nums {10,9,2,5,3,7,101,18};
    int n = nums.size();

    solveT(nums);

    return 0;
}

/*
Output of the program:
Size of LIS: 4
2 5 7 101
*/