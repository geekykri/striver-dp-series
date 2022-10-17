// Author: REET
// Problem: Buy and Sell Stock
// Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include <bits/stdc++.h>
using namespace std;

// Approach: Space Optimized
// Time Complexity: O(n)
// Reason: Single iteration
// Space Complexity: O(1)
// Reason: Using variables
int solveS(vector<int> &prices) {
    int res = 0;
    int minPrice = INT_MAX;
    for(int &price: prices) {
        minPrice = min(minPrice, price);
        res = max(res, price-minPrice);
    }
    return res;
}

int main() {
    vector<int> prices {7, 1, 5, 3, 6, 4};
    
    cout << solveS(prices);
    
    return 0;
}

/*
Output of the program:
5
*/