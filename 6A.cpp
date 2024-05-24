#include <algorithm>
#include <iostream>
#include <vector>

int find_lns(std::vector<int>& lns, std::vector<int>& array) {
  int size = array.size();
  std::vector<int> dp(size);
  const int kIntMin = -2147483647 - 1;
  std::vector<int> max_end(size, kIntMin);
  for (int i = 0; i < size; ++i) {
    int l = -1;
    int r = size - 1;
    while (r - l > 1) {
      int md = (l + r) / 2;
      if (max_end[md] < array[i]) {
        r = md;
      } else {
        l = md;
      }
    }
    max_end[r] = array[i];
    dp[i] = r + 1;
  }
  int answer = 0;
  for (auto elem : dp) {
    answer = std::max(answer, elem);
  }
  int counter = answer;
  for (int i = size - 1; i > -1; --i) {
    if (dp[i] == counter) {
      lns.push_back(i + 1);
      --counter;
    }
  }
  std::reverse(lns.begin(), lns.end());
  return answer;
}

int main() {
  int size;
  std::cin >> size;
  std::vector<int> array(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  std::vector<int> lns;
  int answer = find_lns(lns, array);
  std::cout << answer << std::endl;
  for (auto index : lns) {
    std::cout << index << " ";
  }
}
