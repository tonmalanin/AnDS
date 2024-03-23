#include <algorithm>
#include <iostream>
#include <vector>

void Dfs(int curr, std::vector<std::vector<int>>& graph,
         std::vector<bool>& used, std::vector<int>& tout_sort) {
  used[curr] = true;
  for (auto elem : graph[curr]) {
    if (!used[elem]) {
      Dfs(elem, graph, used, tout_sort);
    }
  }
  tout_sort.push_back(curr);
}

void Paint(int curr, std::vector<std::vector<int>>& graph,
           std::vector<int>& col, int n_col) {
  col[curr] = n_col;
  for (auto elem : graph[curr]) {
    if (col[elem] == 0) {
      Paint(elem, graph, col, n_col);
    }
  }
}

int main() {
  int v_n;
  int e_n;
  std::cin >> v_n >> e_n;
  std::vector<std::vector<int>> graph(v_n);
  std::vector<std::vector<int>> r_graph(v_n);
  for (int i = 0; i < e_n; ++i) {
    int start;
    int fin;
    std::cin >> start >> fin;
    graph[start - 1].push_back(fin - 1);
    r_graph[fin - 1].push_back(start - 1);
  }
  std::vector<bool> used(v_n, false);
  std::vector<int> tout_sort(v_n);
  for (int i = 0; i < v_n; ++i) {
    if (!used[i]) {
      Dfs(i, graph, used, tout_sort);
    }
  }
  std::reverse(tout_sort.begin(), tout_sort.end());
  std::vector<int> col(v_n, 0);
  int n_col = 1;
  for (auto elem : tout_sort) {
    if (col[elem] == 0) {
      Paint(elem, r_graph, col, n_col);
      ++n_col;
    }
  }
  std::cout << n_col - 1 << std::endl;
  for (auto elem : col) {
    std::cout << elem << " ";
  }
}
