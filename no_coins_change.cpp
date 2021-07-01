#include <iostream>
#include <vector>

using namespace std;

//use recursion
int noWay(int amount, const vector<int>& coins)
{
    int ans = 0;
    //base case
    if(amount == 0)
        return 1;
    if(amount < 0)
        return 0;
    for(int coin : coins)
        ans += noWay(amount-coin, coins);
    return ans;
}

//dynamic programing
int formAmount(int amount, const vector<int>& coins)
{
    int n = coins.size();
    vector<vector<int>> dp(n+1,vector<int>(amount+1));
    //Fill 1st row with 0 because no amount (except 0) can be formed without any coin
    int i,j;
    for(i = 1;i <= amount; ++i)
        dp[0][i] = 0;
    //Fill 1st col by 1 (assuming amount 0 can always be formed)
    for(i=0;i<=n;++i)
        dp[i][0] = 1;

    //Fill DP-Table
    for(i=1;i<=n;++i)
    {
        for(j=1;j<=amount;++j)
        {
            if(j>=coins[i-1])
                dp[i][j] = dp[i][j-coins[i-1]]+dp[i-1][j];
                        //including coins[i-1] excluding coins[i-1]
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][amount];

}
int main()
{
    int n = 5;
    vector<int> c = {1, 2, 5};
    //find number of ways to form a given amount by coins
    //no_coins are infinity

    //way 1 : use recursion but it will build same subproblem : 5 = 1+2+2 = 2+2+1
    //int ans = noWay(n, c);

    //way 2 : use dynamic programing
    //no_way[c][A] = no_way[c][A-ci] + no_way[c-1][A]
    //               including c1      excluding ci
    int ans = formAmount(n, c);
    cout << ans;
    return 0;
}
