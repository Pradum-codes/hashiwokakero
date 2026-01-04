#pragma once
#include "../model/GameState.h"

int currentDegree(const GameState& state, int islandId);
bool validateCrossings(const GameState& state);
bool validateConnectivity(const GameState& state);
bool isSolved(const GameState& state);
