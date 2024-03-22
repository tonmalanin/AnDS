#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int dest;
  int num;
};

int Dfs(int curr, std::vector<std::vector<Edge>>& graph,
        std::vector<int>& depth, std::vector<int>& ans, int curr_d, int path) {
  depth[curr] = curr_d;
  int h_anc = curr_d;
  for (auto elem : graph[curr]) {
    int dest = elem.dest;
    int num = elem.num;
    if (depth[dest] != -1 and num != path) {
      h_anc = std::min(h_anc, depth[dest]);
    } else if (depth[dest] == -1) {
      int res = Dfs(dest, graph, depth, ans, curr_d + 1, num);
      if (res > curr_d) {
        ans.push_back(num);
      } else {
        h_anc = std::min(h_anc, res);
      }
    }
  }
  return h_anc;
}

int main() {
  int v_n;
  int e_n;
  std::cin >> v_n >> e_n;
  std::vector<std::vector<Edge>> graph(v_n);
  for (int i = 0; i < e_n; ++i) {
    int start;
    int fin;
    std::cin >> start >> fin;
    graph[start - 1].push_back({fin - 1, i + 1});
    graph[fin - 1].push_back({start - 1, i + 1});
  }
  std::vector<int> ans;
  std::vector<int> depth(v_n, -1);
  for (int i = 0; i < v_n; ++i) {
    if (depth[i] == -1) {
      Dfs(i, graph, depth, ans, 0, -1);
    }
  }
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << std::endl;
  for (auto elem : ans) {
    std::cout << elem << " ";
  }
}
