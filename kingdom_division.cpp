#include <iostream>
#include <vector>

#define MOD 1000000007
using namespace std;
enum{good, nearlyGood};
void DFS(int u, vector<bool>& visited, const vector<vector<int>>& graph, vector<vector<long>>& dp)
{
    visited[u] = true;
    long GNr, BNr;
    GNr = BNr = 1;
    for(int child : graph[u])
    {
        if(visited[child])
            continue;
        DFS(child, visited, graph, dp);
        BNr *= dp[child][good];//BNr *= GchildB and GchildB = GchildR
        BNr %= MOD;
        GNr *= (2*dp[child][good] + dp[child][nearlyGood]); // GNr *= (GchildR + GchildB + BchildR)
        GNr %= MOD;
    }
    GNr -= BNr;//subtraction case all child are GNb
    GNr += MOD;//in partical GNr will alaways greater than BNr but when %MOD :
               //if GNr = 10^9 + 8 -> GNr = 1;
               //   BNr = 10^9 + 7 -> BNr = 10^9 + 7
    GNr %= MOD;
    dp[u][good] = GNr;
    dp[u][nearlyGood] = BNr;
}
int kingdomDivision(int N, const vector<vector<int>>& roads)
{
    int ans;
    //build graph
    vector<vector<int>> graph(N);
    for(vector<int> road : roads)
    {
        //undirected
        graph[road[0]-1].push_back(road[1]-1);
        graph[road[1]-1].push_back(road[0]-1);
    }

    //use DFS to build configuration of parent by its child
    vector<vector<long>> dp(N, vector<long>(2));
        //4 var is two couple : GNr = GNb ; BNr = BNb
    vector<bool> visited(N, false);
    DFS(0, visited, graph, dp);
    ans = (2*dp[0][good])%MOD;//G0r + G0b
    return ans;
}
int main()
{
    vector<vector<int>> roads;
    roads = {   {1, 2},
                {1, 3},
                {3, 4},
                {3, 5}
                };
    int N = roads.size()+1;
    int ans = kingdomDivision(N, roads);
    cout << ans;

    return 0;
}
