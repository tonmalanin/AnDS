#include <algorithm>
#include <iostream>
#include <vector>

void Dfs(int curr_vert, std::vector<std::vector<int>>& graph,
         std::vector<bool>& used, std::vector<int>& tout_sort) {
  used[curr_vert] = true;
  for (auto vert : graph[curr_vert]) {
    if (!used[vert]) {
      Dfs(vert, graph, used, tout_sort);
    }
  }
  tout_sort.push_back(curr_vert);
}

void Paint(int curr_vert, std::vector<std::vector<int>>& graph,
           std::vector<int>& comp_num, int curr_comp_num) {
  comp_num[curr_vert] = curr_comp_num;
  for (auto vert : graph[curr_vert]) {
    if (comp_num[vert] == 0) {
      Paint(vert, graph, comp_num, curr_comp_num);
    }
  }
}

int Kosaraju(std::vector<std::vector<int>>& graph, std::vector<int>& comp_num) {
  int v_n = graph.size();
  std::vector<std::vector<int>> r_graph(v_n);
  for (int i = 0; i < v_n; ++i) {
    for (auto vert: graph[i]) {
      r_graph[vert].push_back(i);
    }
  }
  std::vector<bool> used(v_n, false);
  std::vector<int> tout_sort(v_n);
  for (int i = 0; i < v_n; ++i) {
    if (!used[i]) {
      Dfs(i, graph, used, tout_sort);
    }
  }
  std::reverse(tout_sort.begin(), tout_sort.end());
  int curr_comp_num = 1;
  for (auto vert : tout_sort) {
    if (comp_num[vert] == 0) {
      Paint(vert, r_graph, comp_num, curr_comp_num);
      ++curr_comp_num;
    }
  }
  return curr_comp_num;
}

int main() {
  int v_n;
  int e_n;
  std::cin >> v_n >> e_n;
  std::vector<std::vector<int>> graph(v_n);
  for (int i = 0; i < e_n; ++i) {
    int start;
    int fin;
    std::cin >> start >> fin;
    graph[start - 1].push_back(fin - 1);
  }
  std::vector<int> comp_num(v_n, 0);
  int curr_comp_num = Kosaraju(graph, comp_num);
  std::cout << curr_comp_num - 1 << std::endl;
  for (auto vert : comp_num) {
    std::cout << vert << " ";
  }
}
