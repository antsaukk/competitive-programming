#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <list>
#include <algorithm>

int main() {
    int w, h;
    std::cin >> w >> h;
    std::vector<int> distance;
    std::vector<bool> visited;
    visited.resize(w*h, false);
    std::vector<char> map;
    distance.resize(w*h, std::numeric_limits<int>::max());
    int start_x, start_y;
    map.reserve(w*h);
    for(int i = 0; i < h; ++i) {
        std::string line;
        std::cin >> line;
        for(int j = 0; j < line.size(); ++j) {
            if(line[j] == 'S') {
                start_x = j;
                start_y = i;
                map.push_back('.');
            } else {
                map.push_back(line[j]);
            }
        }
    }

    std::string instructions;
    std::cin >> instructions;

    auto compare = [&](int a, int b) {
        return distance[a] < distance[b];
    };

    auto get_dist = [&](int x, int y) -> int& {
        return distance[x + w*y];
    };

    // Find the shortest paths
    std::vector<int> unvisited;
    for(int i = 0; i < w*h; ++i) {
        unvisited.push_back(i);
    }
    get_dist(start_x, start_y) = 0;
    std::sort(begin(unvisited), end(unvisited), compare);

    while(!unvisited.empty()) {
        int node = *unvisited.begin();
        // found the end?
        if(distance[node] == instructions.size()) {
            break;
        }
        unvisited.erase(unvisited.begin());
        visited[node] = true;
        int x = node % w;
        int y = (node - x) / w;

        char instruction = instructions[distance[node]];

        auto check_nb = [&](int x, int y) {
            if(visited[x + w*y]) return;
            if(map[x + w*y] != '.') return;
            int new_dist = distance[node] + 1;
            int nb = x + w*y;
            if(new_dist < distance[nb]) {
                distance[nb] = new_dist;
                // update by re-inserting into ordered set
                std::sort(begin(unvisited), end(unvisited), compare);
            }
        };

        if(instruction != 'E') {
            check_nb(x+1, y);
        }
        if(instruction != 'W') {
            check_nb(x-1, y);
        }
        if(instruction != 'N') {
            check_nb(x, y-1);
        }
        if(instruction != 'S') {
            check_nb(x, y+1);
        }
    }

    map[start_x + w * start_y] = 'S';
    for(int i = 0; i < map.size(); ++i) {
        if(distance[i] == instructions.size()) {
            map[i] = '!';
        }
    }

    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            std::cout << map[x + w*y];
        }
        std::cout << "\n";
    }
}