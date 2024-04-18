#include <iostream>
#include <vector>

int Log(int num) {
  int cnt = 1;
  int log = 0;
  while (cnt < num) {
    cnt *= 2;
    ++log;
  }
  return log;
}

int main() {
  int max_hgt;
  int pl_num;
  std::cin >> max_hgt >> pl_num;
  int log = Log(max_hgt);
  if (pl_num >= log) {
    std::cout << log;
    return 0;
  }
  if (pl_num == 0) {
    std::cout << -1;
    return 0;
  }
  std::vector<std::vector<int>> dp(pl_num, std::vector<int>(max_hgt + 1));
  for (int i = 1; i <= max_hgt; ++i) {
    dp[0][i] = i - 1;
  }
  for (int i = 0; i < pl_num; ++i) {
    dp[i][1] = 0;
  }
  for (int i = 1; i < pl_num; ++i) {
    for (int j = 2; j <= max_hgt; ++j) {
      int bot_lim = 1;
      int up_lim = j;
      while (up_lim - bot_lim > 1) {
        int curr = (bot_lim + up_lim) / 2;
        if (dp[i - 1][curr] <= dp[i][j - curr]) {
          bot_lim = curr;
        } else {
          up_lim = curr;
        }
      }
      dp[i][j] = std::max(dp[i - 1][bot_lim], dp[i][j - bot_lim]);
      if (up_lim != j) {
        dp[i][j] = std::min(std::max(dp[i - 1][up_lim], dp[i][j - up_lim]), dp[i][j]);
      }
      ++dp[i][j];
    }
  }
  std::cout << dp[pl_num - 1][max_hgt];
}
