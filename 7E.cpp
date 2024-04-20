#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int dest;
  int num;
};

struct Graph {
  int vert_num;
  std::vector<std::vector<Edge>> adj_list;
  Graph(int vert_num, std::vector<std::pair<int, int>>& edge_list)
      : vert_num(vert_num) {
    adj_list.resize(vert_num);
    int counter = 0;
    for (auto pair : edge_list) {
      int start = pair.first;
      int fin = pair.second;
      adj_list[start - 1].push_back({fin - 1, counter + 1});
      adj_list[fin - 1].push_back({start - 1, counter + 1});
      ++counter;
    }
  }

  int Dfs(int curr_vert, std::vector<int>& depth, std::vector<int>& ans,
          int curr_depth, int parent) {
    depth[curr_vert] = curr_depth;
    int highest_reachable = curr_depth;
    for (auto vert : adj_list[curr_vert]) {
      int dest = vert.dest;
      int num = vert.num;
      if (depth[dest] != -1 and dest != parent) {
        highest_reachable = std::min(highest_reachable, depth[dest]);
      } else if (depth[dest] == -1) {
        int subtree_result = Dfs(dest, depth, ans, curr_depth + 1, curr_vert);
        if (subtree_result > curr_depth) {
          ans.push_back(num);
        } else {
          highest_reachable = std::min(highest_reachable, subtree_result);
        }
      }
    }
    return highest_reachable;
  }

  std::vector<int> FindBridges() {
    std::vector<int> ans;
    std::vector<int> depth(vert_num, -1);
    for (int i = 0; i < vert_num; ++i) {
      if (depth[i] == -1) {
        Dfs(i, depth, ans, 0, -1);
      }
    }
    return ans;
  }
};

int main() {
  int vert_num;
  int edge_num;
  std::cin >> vert_num >> edge_num;
  std::vector<std::pair<int, int>> edge_list(edge_num);
  for (int i = 0; i < edge_num; ++i) {
    std::cin >> edge_list[i].first >> edge_list[i].second;
  }
  Graph graph(vert_num, edge_list);
  std::vector<int> ans = graph.FindBridges();
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << std::endl;
  for (auto edge : ans) {
    std::cout << edge << " ";
  }
}
