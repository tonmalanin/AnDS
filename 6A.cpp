#include <algorithm>
#include <iostream>
#include <vector>
void find_gds(std::vector<int>& dp, std::vector<int>& seq) {
  int seq_sz = dp.size();
  const int kIntMin = -2147483647 - 1;
  std::vector<int> max_ds_end(seq_sz, kIntMin);
  for (int i = 0; i < seq_sz; ++i) {
    int bot_lim = -1;
    int up_lim = seq_sz - 1;
    while (up_lim - bot_lim > 1) {
      int curr = (bot_lim + up_lim) / 2;
      if (max_ds_end[curr] < seq[i]) {
        up_lim = curr;
      } else {
        bot_lim = curr;
      }
    }
    max_ds_end[up_lim] = seq[i];
    dp[i] = up_lim + 1;
  }
}

int main() {
  int seq_sz;
  std::cin >> seq_sz;
  std::vector<int> seq(seq_sz);
  for (int i = 0; i < seq_sz; ++i) {
    std::cin >> seq[i];
  }
  std::vector<int> dp(seq_sz);
  find_gds(dp, seq);
  int ans = 0;
  for (auto item : dp) {
    ans = std::max(ans, item);
  }
  std::cout << ans << std::endl;
  int cnt = ans;
  std::vector<int> elem_nums;
  for (int i = seq_sz - 1; i > -1; --i) {
    if (dp[i] == cnt) {
      elem_nums.push_back(i + 1);
      --cnt;
    }
  }
  std::reverse(elem_nums.begin(), elem_nums.end());
  for (auto item : elem_nums) {
    std::cout << item << " ";
  }
}
