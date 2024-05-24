#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int destination;
  int weight;
};

void Dijkstra(std::vector<std::vector<Edge>>& graph, int start,
              std::vector<int>& distances) {
  distances[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      queue;
  queue.emplace(0, start);
  while (!queue.empty()) {
    int current_vertex = queue.top().second;
    if (distances[current_vertex] < queue.top().first) {
      queue.pop();
      continue;
    }
    queue.pop();
    for (auto edge : graph[current_vertex]) {
      if (distances[edge.destination] >
          distances[current_vertex] + edge.weight) {
        distances[edge.destination] = distances[current_vertex] + edge.weight;
        queue.emplace(distances[edge.destination], edge.destination);
      }
    }
  }
}

int main() {
  const int cIntMax = 2009000999;
  int case_number;
  std::cin >> case_number;
  for (int i = 0; i < case_number; ++i) {
    int vertex_number;
    int edge_number;
    std::cin >> vertex_number >> edge_number;
    std::vector<std::vector<Edge>> graph(vertex_number);
    for (int j = 0; j < edge_number; ++j) {
      int start;
      int finish;
      int weight;
      std::cin >> start >> finish >> weight;
      graph[start].push_back({finish, weight});
      graph[finish].push_back({start, weight});
    }
    int start;
    std::cin >> start;
    std::vector<int> distances(vertex_number, cIntMax);
    Dijkstra(graph, start, distances);
    for (auto distance : distances) {
      std::cout << distance << " ";
    }
    std::cout << std::endl;
  }
}
