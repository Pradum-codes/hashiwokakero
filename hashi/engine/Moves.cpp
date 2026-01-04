#include "Moves.h"
#include "GameUtils.h"

bool tryToggleBridge(GameState& state, int connectionIndex) {
    if (connectionIndex < 0 || connectionIndex >= static_cast<int>(state.connections.size())) {
        return false;
    }

    Connection& conn = state.connections[connectionIndex];
    int originalBridges = conn.bridges;
    
    // Cycle through bridge states: 0 -> 1 -> 2 -> 0
    conn.bridges = (conn.bridges + 1) % 3;

    // Validate that this doesn't exceed any island's required degree
    const Island* islandA = findIsland(state, conn.islandA);
    const Island* islandB = findIsland(state, conn.islandB);

    if (!islandA || !islandB) {
        conn.bridges = originalBridges;  // Revert
        return false;
    }

    // Check if either island would exceed its required degree
    if (currentDegree(state, conn.islandA) > islandA->requiredDegree ||
        currentDegree(state, conn.islandB) > islandB->requiredDegree) {
        conn.bridges = originalBridges;  // Revert
        return false;
    }

    return true;
}