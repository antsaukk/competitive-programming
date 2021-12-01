#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>

// https://cses.fi/386/task/D - not finished

using namespace std;
#define INF INT_MAX

int x, n;
vector<int> cuts;
vector<int> dp;

int solve(int s, int e){
  int mem = dp[s + e*n];
  if(mem != INF){
    return mem;
  }

  int mcost = INF;
  for(int c = s + 1; c < e; c++){
    int l = e - s;
    int cost = l + solve(s, c) + solve(c, e);
    if(cost < mcost){
      mcost = cost;
    }
  }

  if(mcost == INF) mcost = 0;

  dp[s + e*n] = mcost;

  return mcost;
}

int main(){
  cin >> x >> n;

  int c;
  cuts.resize(n);
  dp.resize(n*n, INF);
  for(int i = 0; i < n; i++){
    cin >> c;
    cuts[i] = c;
  }

  cout << solve(0, x) << "\n";

  return 0;
}