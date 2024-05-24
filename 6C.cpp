#include <iostream>
#include <vector>

int Log(int number) {
  int counter = 1;
  int log = 0;
  while (counter < number) {
    counter *= 2;
    ++log;
  }
  return log;
}

int main() {
  int max_height;
  int planes_number;
  std::cin >> max_height >> planes_number;
  int log = Log(max_height);
  if (planes_number >= log) {
    std::cout << log;
    return 0;
  }
  if (planes_number == 0) {
    std::cout << -1;
    return 0;
  }
  std::vector<std::vector<int>> dp(planes_number, std::vector<int>(max_height + 1));
  for (int i = 1; i <= max_height; ++i) {
    dp[0][i] = i - 1;
  }
  for (int i = 0; i < planes_number; ++i) {
    dp[i][1] = 0;
  }
  for (int i = 1; i < planes_number; ++i) {
    for (int j = 2; j <= max_height; ++j) {
      int l = 1;
      int r = j;
      while (r - l > 1) {
        int md = (l + r) / 2;
        if (dp[i - 1][md] <= dp[i][j - md]) {
          l = md;
        } else {
          r = md;
        }
      }
      dp[i][j] = std::max(dp[i - 1][l], dp[i][j - l]);
      if (r != j) {
        dp[i][j] = std::min(std::max(dp[i - 1][r], dp[i][j - r]), dp[i][j]);
      }
      ++dp[i][j];
    }
  }
  std::cout << dp[planes_number - 1][max_height];
}
