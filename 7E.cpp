#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int destination;
  int index;
};

class Graph {
 private:
  int vertex_number;
  std::vector<std::vector<Edge>> adjacency_list;

 public:
  Graph(int vertex_number, std::vector<std::pair<int, int>>& edge_list)
      : vertex_number(vertex_number) {
    adjacency_list.resize(vertex_number);
    int counter = 0;
    for (auto pair : edge_list) {
      int start = pair.first;
      int finish = pair.second;
      adjacency_list[start - 1].push_back({finish - 1, counter + 1});
      adjacency_list[finish - 1].push_back({start - 1, counter + 1});
      ++counter;
    }
  }

  int Dfs(int current_vertex, std::vector<int>& depth, std::vector<int>& answer,
          int current_depth, int parent) {
    depth[current_vertex] = current_depth;
    int highest_reachable = current_depth;
    for (auto vertex : adjacency_list[current_vertex]) {
      int destination = vertex.destination;
      int index = vertex.index;
      if (depth[destination] != -1 and destination != parent) {
        highest_reachable = std::min(highest_reachable, depth[destination]);
      } else if (depth[destination] == -1) {
        int subtree_result =
            Dfs(destination, depth, answer, current_depth + 1, current_vertex);
        if (subtree_result > current_depth) {
          answer.push_back(index);
        } else {
          highest_reachable = std::min(highest_reachable, subtree_result);
        }
      }
    }
    return highest_reachable;
  }

  std::vector<int> FindBridges() {
    std::vector<int> answer;
    std::vector<int> depth(vertex_number, -1);
    for (int i = 0; i < vertex_number; ++i) {
      if (depth[i] == -1) {
        Dfs(i, depth, answer, 0, -1);
      }
    }
    return answer;
  }
};

int main() {
  int vertex_number;
  int edge_number;
  std::cin >> vertex_number >> edge_number;
  std::vector<std::pair<int, int>> edge_list(edge_number);
  for (int i = 0; i < edge_number; ++i) {
    std::cin >> edge_list[i].first >> edge_list[i].second;
  }
  Graph graph(vertex_number, edge_list);
  std::vector<int> answer = graph.FindBridges();
  std::sort(answer.begin(), answer.end());
  std::cout << answer.size() << std::endl;
  for (auto edge : answer) {
    std::cout << edge << " ";
  }
}
