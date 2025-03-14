#include <algorithm>
#include <iostream>
#include <vector>

void package_solving(std::vector<int>& answer, std::vector<int>& weight,
                     std::vector<int>& cost, int volume) {
  int number = cost.size();
  std::vector<std::vector<int>> dp(number + 1, std::vector<int>(volume + 1, 0));
  for (int i = 1; i <= number; ++i) {
    for (int j = 1; j <= volume; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= weight[i - 1] and
          dp[i - 1][j - weight[i - 1]] + cost[i - 1] > dp[i][j]) {
        dp[i][j] = dp[i - 1][j - weight[i - 1]] + cost[i - 1];
      }
    }
  }
  int max_cost = 0;
  int optimal_weight = 0;
  for (int i = 0; i <= volume; ++i) {
    if (dp[number][i] > max_cost) {
      max_cost = dp[number][i];
      optimal_weight = i;
    }
  }
  for (int i = number; i > 0; --i) {
    if (optimal_weight >= weight[i - 1] and
        dp[i][optimal_weight] ==
            dp[i - 1][optimal_weight - weight[i - 1]] + cost[i - 1]) {
      answer.push_back(i);
      optimal_weight -= weight[i - 1];
    }
  }
  std::reverse(answer.begin(), answer.end());
}

int main() {
  int number;
  int volume;
  std::cin >> number >> volume;
  std::vector<int> weight(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> weight[i];
  }
  std::vector<int> cost(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> cost[i];
  }
  std::vector<int> answer;
  package_solving(answer, weight, cost, volume);
  for (auto index : answer) {
    std::cout << index << std::endl;
  }
}
