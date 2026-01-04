#include "Validators.h"
#include "GameUtils.h"

bool validateCrossings(const GameState& state) {
    // In this simplified version, we don't check bridge crossings
    // This can be implemented later for more complex validation
    return true;
}

bool isSolved(const GameState& state) {
    // Check if all islands have their required degree
    for (const auto& island : state.islands) {
        if (currentDegree(state, island.id) != island.requiredDegree) {
            return false;
        }
    }
    
    // Check if all islands are connected
    return validateConnectivity(state);
}