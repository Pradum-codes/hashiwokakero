#pragma once
#include "../model/Island.h"
#include "../model/Connection.h"
#include <vector>

std::vector<Connection> computeConnections(
    const std::vector<Island>& islands
);
