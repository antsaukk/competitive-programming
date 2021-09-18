#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class Graph {
 public: 
 	explicit Graph(size_t size = 0) : size_(size) {
 	 if (size != N) throw invalid_argument("Bad init");
 	}

 	void AddEdge(T node, T edge) {
 	 assert(node <= Size() - 1);
 	 adjacent_edges[node].push_back(edge);
 	}

 	void NodeToString(T node) {
     order += to_string(node) + " ";
 	}

 	void DFS(T node) {
 	 if (visited[node]) return; 
 	 visited[node] = true;
     NodeToString(node);
 	 for (auto current_node : adjacent_edges[node]) {
 	 	DFS(current_node);
 	 }
 	}

   void BFS(T starting_node) {
    visited[starting_node] = true;
    distance[starting_node] = 0; 
    qnodes.push(starting_node);

    while(!qnodes.empty()) {
      T front_node = qnodes.front();
      qnodes.pop();
      NodeToString(front_node);

      for(auto current_node : adjacent_edges[front_node]) {
         if (visited[current_node]) continue;
         visited[current_node] = true;
         distance[current_node] = distance[front_node] + 1;
         qnodes.push(current_node);
      }
    }
   }

 	size_t Size() const { return size_; }

 	string TraversalOrder() const { return order; }
 private:
 	vector<T> adjacent_edges[N];
   queue<T> qnodes;
 	bool visited[N] = {false};
   T distance[N];
 	size_t size_ = 0;
 	string order = "";
};