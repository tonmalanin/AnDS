#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int sz;
  int cap;
  std::cin >> sz >> cap;
  std::vector<int> wgt(sz);
  for (int i = 0; i < sz; ++i) {
    std::cin >> wgt[i];
  }
  std::vector<int> cost(sz);
  for (int i = 0; i < sz; ++i) {
    std::cin >> cost[i];
  }
  std::vector<std::vector<int>> dp(sz + 1, std::vector<int>(cap + 1, 0));
  for (int i = 1; i <= sz; ++i) {
    for (int j = 1; j <= cap; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= wgt[i - 1] and
          dp[i - 1][j - wgt[i - 1]] + cost[i - 1] > dp[i][j]) {
        dp[i][j] = dp[i - 1][j - wgt[i - 1]] + cost[i - 1];
      }
    }
  }
  int ans = 0;
  int curr_wgt = 0;
  for (int i = 0; i <= cap; ++i) {
    if (dp[sz][i] > ans) {
      ans = dp[sz][i];
      curr_wgt = i;
    }
  }
  std::vector<int> ids;
  for (int i = sz; i > 0; --i) {
    if (curr_wgt >= wgt[i - 1] and
        dp[i][curr_wgt] == dp[i - 1][curr_wgt - wgt[i - 1]] + cost[i - 1]) {
      ids.push_back(i);
      curr_wgt -= wgt[i - 1];
    }
  }
  std::reverse(ids.begin(), ids.end());
  for (auto item : ids) {
    std::cout << item << std::endl;
  }
}
