// Author: REET
// Problem: House Robber 2
// Link: https://leetcode.com/problems/house-robber-ii/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n)
// Reason: Using variables to store previous 2 states 
// Space Complexity: O(n) 
// Reason: Using temp vectors
long long solve(vector<int> &nums) {
    int n = nums.size();
    if(n==1) {
        return nums[0];
    }
    long long prev2 = 0;
    long long prev1 = nums[0];
    long long curr = nums[0];
    for(int i=1; i<n; i++) {
        long long pick = nums[i] + prev2;
        long long notPick = prev1;
        curr = max(pick, notPick);
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

int main() {
    vector<int> nums{2, 1, 4, 9};
    int n = nums.size();
    if(n==1) {
        return nums[0];
    }
    vector<int> tmp1;
    vector<int> tmp2;
    for(int i=0; i<n; i++) {
        if(i!=0) {
            tmp1.push_back(nums[i]);
        }
        if(i!=n-1) {
            tmp2.push_back(nums[i]);
        }
    }
    cout << max(solve(tmp1), solve(tmp2));
}

/*
Output of the program: 
10
*/