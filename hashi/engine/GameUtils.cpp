#include "GameUtils.h"
#include <queue>
#include <unordered_set>

const Island* findIsland(const GameState& state, int id) {
    for (const auto& i : state.islands)
        if (i.id == id) return &i;
    return nullptr;
}

int currentDegree(const GameState& state, int islandId) {
    int sum = 0;
    for (const auto& c : state.connections) {
        if (c.islandA == islandId || c.islandB == islandId)
            sum += c.bridges;
    }
    return sum;
}

bool isReachable(const GameState& state, int fromId, int toId) {
    if (fromId == toId) return true;

    std::queue<int> q;
    std::unordered_set<int> visited;
    
    q.push(fromId);
    visited.insert(fromId);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (const auto& conn : state.connections) {
            if (conn.bridges == 0) continue;

            int neighborId = -1;
            if (conn.islandA == curr) neighborId = conn.islandB;
            else if (conn.islandB == curr) neighborId = conn.islandA;

            if (neighborId != -1 && visited.find(neighborId) == visited.end()) {
                if (neighborId == toId) return true;
                visited.insert(neighborId);
                q.push(neighborId);
            }
        }
    }
    return false;
}

bool validateConnectivity(const GameState& state) {
    if (state.islands.empty()) return true;

    int baseIslandId = state.islands[0].id;
    for (const auto& island : state.islands) {
        if (!isReachable(state, baseIslandId, island.id)) {
            return false;
        }
    }
    return true;
}