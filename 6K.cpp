#include <algorithm>
#include <iostream>
#include <vector>
int package_solving(std::vector<std::vector<int>>& dp,
                    std::vector<int>& req_source, std::vector<int>& reward) {
  int tasks_num = reward.size();
  int source_num = dp[0].size() - 1;
  for (int i = 1; i <= tasks_num; ++i) {
    for (int j = 1; j <= source_num; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= req_source[i - 1] and
          dp[i - 1][j - req_source[i - 1]] + reward[i - 1] > dp[i][j]) {
        dp[i][j] = dp[i - 1][j - req_source[i - 1]] + reward[i - 1];
      }
    }
  }
  int ans = 0;
  int curr_source_waste = 0;
  for (int i = 0; i <= source_num; ++i) {
    if (dp[tasks_num][i] > ans) {
      ans = dp[tasks_num][i];
      curr_source_waste = i;
    }
  }
  return curr_source_waste;
}
int main() {
  int tasks_num;
  int source_num;
  std::cin >> tasks_num >> source_num;
  std::vector<int> req_source(tasks_num);
  for (int i = 0; i < tasks_num; ++i) {
    std::cin >> req_source[i];
  }
  std::vector<int> reward(tasks_num);
  for (int i = 0; i < tasks_num; ++i) {
    std::cin >> reward[i];
  }
  std::vector<std::vector<int>> dp(tasks_num + 1,
                                   std::vector<int>(source_num + 1, 0));
  int curr_source_waste = package_solving(dp, req_source, reward);
  std::vector<int> tasks_id;
  for (int i = tasks_num; i > 0; --i) {
    if (curr_source_waste >= req_source[i - 1] and
        dp[i][curr_source_waste] ==
            dp[i - 1][curr_source_waste - req_source[i - 1]] + reward[i - 1]) {
      tasks_id.push_back(i);
      curr_source_waste -= req_source[i - 1];
    }
  }
  std::reverse(tasks_id.begin(), tasks_id.end());
  for (auto item : tasks_id) {
    std::cout << item << std::endl;
  }
}
