#pragma once
#include <vector>
#include "Island.h"
#include "Connection.h"

struct GameState {
    std::vector<Island> islands;
    std::vector<Connection> connections;
};
