#include "model/GameState.h"
#include "engine/GraphBuilder.h"
#include "engine/Validators.h"
#include "levels/LevelManager.h"
#include "ui/ConsoleUI.h"

int main() {
    // Create game state
    GameState state;
    
    // Load level 1
    state.islands = createLevel1();
    
    // Compute all possible connections
    state.connections = computeConnections(state.islands);
    
    // Start the console interface
    runConsoleGame(state);
    
    return 0;
}
