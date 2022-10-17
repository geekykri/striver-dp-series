// Author: REET
// Problem: LIS length using Binary Search
// Link: https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>
using namespace std;

// Approach: Binary Search
// Time Complexity: O(n*log(n))
// Reason: Iteration with binary search
// Space Complexity: O(n)
// Reason: Temp array O(n)
int solve(vector<int> &nums) {
    int n = nums.size();
    vector<int> temp;
    temp.push_back(nums[0]);
    for(int i=1; i<n; i++) {
        if(nums[i] > temp.back()) {
            temp.push_back(nums[i]);
        }
        else {
            int idx = lower_bound(begin(temp), end(temp), nums[i]) - begin(temp);
            temp[idx] = nums[i];
        }
    }
    return (int)temp.size();
}

int main() {
    vector<int> nums {10,9,2,5,3,7,101,18};

    cout << solve(nums);
    
    return 0;
}

/*
Output of the program:
4
*/