#pragma once
#include "../model/GameState.h"

// Utility functions for game state management
const Island* findIsland(const GameState& state, int id);
int currentDegree(const GameState& state, int islandId);
bool isReachable(const GameState& state, int fromId, int toId);
bool validateConnectivity(const GameState& state);