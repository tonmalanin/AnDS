#include <iostream>
#include <vector>

int Log(int num) {
  int cnt = 1;
  int lg = 0;
  while (cnt < num) {
    cnt *= 2;
    ++lg;
  }
  return lg;
}

int main() {
  int max_h;
  int pl_n;
  std::cin >> max_h >> pl_n;
  int lg = Log(max_h);
  if (pl_n >= lg) {
    std::cout << lg;
    return 0;
  }
  if (pl_n == 0) {
    std::cout << -1;
    return 0;
  }
  std::vector<std::vector<int>> dp(pl_n, std::vector<int>(max_h + 1));
  for (int i = 1; i <= max_h; ++i) {
    dp[0][i] = i - 1;
  }
  for (int i = 0; i < pl_n; ++i) {
    dp[i][1] = 0;
  }
  for (int i = 1; i < pl_n; ++i) {
    for (int j = 2; j <= max_h; ++j) {
      int lp = 1;
      int rp = j;
      while (rp - lp > 1) {
        int md = (lp + rp) / 2;
        if (dp[i - 1][md] <= dp[i][j - md]) {
          lp = md;
        } else {
          rp = md;
        }
      }
      dp[i][j] = std::max(dp[i - 1][lp], dp[i][j - lp]);
      if (rp != j) {
        dp[i][j] = std::min(std::max(dp[i - 1][rp], dp[i][j - rp]), dp[i][j]);
      }
      ++dp[i][j];
    }
  }
  std::cout << dp[pl_n - 1][max_h];
}
