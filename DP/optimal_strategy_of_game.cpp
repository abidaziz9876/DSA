#include<bits/stdc++.h>
using namespace std;



//two ways to solve this types of questions Leetcode->Predict the Winner
class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n=nums.size();
        int score1=solve(0,n-1,nums);
        int total=accumulate(nums.begin(),nums.end(),0);
        int score2=total-score1;
        if(score1>=score2)
        return true;
        return false;
    }

    int solve(int i,int j,vector<int>& nums){
        if(i>j){
            return 0;
        }

        if(i==j){
            return nums[i];
        }

        int take_i=nums[i]+min(solve(i+2,j,nums),solve(i+1,j-1,nums));
        int take_j=nums[j]+min(solve(i,j-2,nums),solve(i+1,j-1,nums));
        return max(take_i,take_j);
    }
};

class Solution {
    public:
    int solve(vector<int>& nums,int i,int j,vector<vector<int>>& dp){
        if(i>j){
            return 0;
        }

        if(i==j){
            return nums[i];
        }
        
        if(dp[i][j]!=-1)
        return dp[i][j];

        int take_i=nums[i]-solve(nums,i+1,j,dp);
        int take_j=nums[j]-solve(nums,i,j-1,dp);

        return dp[i][j]=max(take_i,take_j);
    }
    bool predictTheWinner(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> dp(n,vector<int>(n,-1));
        return solve(nums,0,n-1,dp)>=0;
    }
};
