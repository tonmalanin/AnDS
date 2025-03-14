#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  long long destination;
  long long weight;
};

void FordBellman(std::vector<std::vector<Edge>>& graph,
                 std::vector<long long>& distance,
                 std::vector<long long>& parent) {
  int vertex_number = graph.size();
  for (int i = 0; i < vertex_number; ++i) {
    for (int j = 0; j < vertex_number; ++j) {
      for (auto edge : graph[j]) {
        if (distance[j] > distance[edge.destination] + edge.weight) {
          distance[j] = distance[edge.destination] + edge.weight;
          parent[j] = edge.destination;
        }
      }
    }
  }
}

void BuildCycle(std::vector<long long>& cycle, std::vector<long long>& parent,
                long long start) {
  int vertex_number = parent.size();
  for (int i = 0; i < vertex_number; ++i) {
    start = parent[start];
  }
  cycle.push_back(start);
  long long curr = parent[start];
  while (curr != start) {
    cycle.push_back(curr);
    curr = parent[curr];
  }
  cycle.push_back(curr);
  std::reverse(cycle.begin(), cycle.end());
}

int main() {
  const long long cIntMax = 30000000;
  const long long cMaxWeight = 100000;
  long long vertex_number;
  std::cin >> vertex_number;
  std::vector<std::vector<Edge>> graph(vertex_number);
  for (int i = 0; i < vertex_number; ++i) {
    for (int j = 0; j < vertex_number; ++j) {
      long long weight;
      std::cin >> weight;
      if (weight != cMaxWeight) {
        graph[j].push_back({i, weight});
      }
    }
  }
  std::vector<long long> distance(vertex_number, cIntMax);
  std::vector<long long> parent(vertex_number, -1);
  FordBellman(graph, distance, parent);
  bool flag = true;
  long long start;
  for (int j = 0; j < vertex_number; ++j) {
    for (auto edge : graph[j]) {
      if (distance[j] > distance[edge.destination] + edge.weight) {
        flag = false;
        start = j;
      }
    }
  }
  if (flag) {
    std::cout << "NO";
    return 0;
  }
  std::vector<long long> cycle;
  BuildCycle(cycle, parent, start);
  std::cout << "YES" << std::endl << cycle.size() << std::endl;
  for (auto vertex : cycle) {
    std::cout << vertex + 1 << " ";
  }
}
