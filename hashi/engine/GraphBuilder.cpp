#include "GraphBuilder.h"
#include <algorithm>

std::vector<Connection> computeConnections(const std::vector<Island>& islands) {
    std::vector<Connection> result;

    for (const auto& a : islands) {
        for (const auto& b : islands) {
            if (a.id >= b.id) continue;

            // Horizontal connections (same row)
            if (a.x == b.x) {
                bool blocked = false;
                for (const auto& c : islands) {
                    if (c.x == a.x &&
                        c.y > std::min(a.y, b.y) &&
                        c.y < std::max(a.y, b.y)) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    result.push_back({
                        a.id, b.id,
                        Orientation::HORIZONTAL,
                        0
                    });
                }
            }

            // Vertical connections (same column)
            if (a.y == b.y) {
                bool blocked = false;
                for (const auto& c : islands) {
                    if (c.y == a.y &&
                        c.x > std::min(a.x, b.x) &&
                        c.x < std::max(a.x, b.x)) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    result.push_back({
                        a.id, b.id,
                        Orientation::VERTICAL,
                        0
                    });
                }
            }
        }
    }

    return result;
}