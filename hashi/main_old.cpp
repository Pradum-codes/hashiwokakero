#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

enum class Orientation {
    HORIZONTAL,
    VERTICAL
};

struct Island {
    int id;
    int x;
    int y;
    int requiredDegree;
};

struct Connection {
    int islandA;
    int islandB;
    Orientation orientation;
    int bridges;   // 0, 1, 2
};

struct GameState {
    vector<Island> islands;
    vector<Connection> connections;
};

//// ------------------ Utility ------------------

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

//// ------------------ Connection Discovery ------------------

vector<Connection> computeConnections(const vector<Island>& islands) {
    vector<Connection> result;

    for (const auto& a : islands) {
        for (const auto& b : islands) {
            if (a.id >= b.id) continue;

            // Horizontal
            if (a.x == b.x) {
                bool blocked = false;
                for (const auto& c : islands) {
                    if (c.x == a.x &&
                        c.y > min(a.y, b.y) &&
                        c.y < max(a.y, b.y)) {
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

            // Vertical
            if (a.y == b.y) {
                bool blocked = false;
                for (const auto& c : islands) {
                    if (c.y == a.y &&
                        c.x > min(a.x, b.x) &&
                        c.x < max(a.x, b.x)) {
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

//// ------------------ Crossing Detection ------------------

bool bridgesCross(const GameState& state,
                  const Connection& a,
                  const Connection& b) {

    if (a.bridges == 0 || b.bridges == 0) return false;
    if (a.orientation == b.orientation) return false;

    const Island* a1 = findIsland(state, a.islandA);
    const Island* a2 = findIsland(state, a.islandB);
    const Island* b1 = findIsland(state, b.islandA);
    const Island* b2 = findIsland(state, b.islandB);

    if (!a1 || !a2 || !b1 || !b2) return false;

    // a horizontal, b vertical
    if (a.orientation == Orientation::HORIZONTAL) {
        int row = a1->x;
        int col = b1->y;

        if (b1->x < row && b2->x > row &&
            a1->y < col && a2->y > col)
            return true;
    } else {
        // a vertical, b horizontal
        int row = b1->x;
        int col = a1->y;

        if (a1->x < row && a2->x > row &&
            b1->y < col && b2->y > col)
            return true;
    }
    return false;
}

bool validateCrossings(const GameState& state) {
    for (size_t i = 0; i < state.connections.size(); i++) {
        for (size_t j = i + 1; j < state.connections.size(); j++) {
            if (bridgesCross(state, state.connections[i], state.connections[j]))
                return false;
        }
    }
    return true;
}

//// ------------------ Connectivity ------------------

bool validateConnectivity(const GameState& state) {
    if (state.islands.empty()) return true;

    queue<int> q;
    vector<bool> visited(state.islands.size(), false);

    q.push(state.islands[0].id);
    visited[0] = true;

    while (!q.empty()) {
        int id = q.front(); q.pop();

        for (const auto& c : state.connections) {
            if (c.bridges == 0) continue;

            int next = -1;
            if (c.islandA == id) next = c.islandB;
            else if (c.islandB == id) next = c.islandA;

            if (next != -1) {
                for (size_t i = 0; i < state.islands.size(); i++) {
                    if (state.islands[i].id == next && !visited[i]) {
                        visited[i] = true;
                        q.push(next);
                    }
                }
            }
        }
    }

    for (bool v : visited)
        if (!v) return false;

    return true;
}

//// ------------------ Move Logic ------------------

bool tryToggleBridge(GameState& state, int idx) {
    auto& c = state.connections[idx];
    int old = c.bridges;
    c.bridges = (c.bridges + 1) % 3;

    // Degree check
    for (const auto& i : state.islands) {
        if (currentDegree(state, i.id) > i.requiredDegree) {
            c.bridges = old;
            return false;
        }
    }

    // Crossing check
    if (!validateCrossings(state)) {
        c.bridges = old;
        return false;
    }

    return true;
}

//// ------------------ Win Check ------------------

bool isSolved(const GameState& state) {
    for (const auto& i : state.islands) {
        if (currentDegree(state, i.id) != i.requiredDegree)
            return false;
    }
    return validateConnectivity(state);
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

void printMenu() {
    cout << "\n\033[1;32m=== HASHIWOKAKERO CONSOLE GAME ===\033[0m\n";
    cout << "\n\033[1;33mCommands:\033[0m\n";
    cout << "  [number] - Toggle bridge connection (0, 1, or 2 bridges)\n";
    cout << "  'm'      - Show this menu\n";
    cout << "  'c'      - Show all connections\n";
    cout << "  's'      - Show game statistics\n";
    cout << "  'q'      - Quit game\n";
    cout << "\n\033[1;36mGoal:\033[0m Connect all islands with bridges so that each\n";
    cout << "      island has exactly the number of bridges shown.\n";
}

void printConnections(const GameState& state) {
    cout << "\n\033[1;33mAvailable Connections:\033[0m\n";
    cout << "\033[1;37m" << setw(4) << "ID" << " | " << setw(10) << "Islands" 
         << " | " << setw(11) << "Orientation" << " | " << setw(8) << "Bridges" << "\033[0m\n";
    cout << "\033[1;30m" << string(45, '-') << "\033[0m\n";
    
    for (size_t i = 0; i < state.connections.size(); i++) {
        const auto& c = state.connections[i];
        string orientation = (c.orientation == Orientation::HORIZONTAL) ? "Horizontal" : "Vertical";
        string bridgeDisplay = "";
        
        if (c.bridges == 0) bridgeDisplay = "None";
        else if (c.bridges == 1) bridgeDisplay = "Single";
        else if (c.bridges == 2) bridgeDisplay = "Double";
        
        // Color coding based on bridge count
        string color = "\033[0m"; // default
        if (c.bridges == 1) color = "\033[1;33m"; // yellow for single
        else if (c.bridges == 2) color = "\033[1;31m"; // red for double
        
        cout << color << setw(4) << i << " | " 
             << setw(4) << c.islandA << " <-> " << setw(2) << c.islandB 
             << " | " << setw(11) << orientation 
             << " | " << setw(8) << bridgeDisplay << "\033[0m\n";
    }
}

void printStatistics(const GameState& state) {
    cout << "\n\033[1;36mGame Statistics:\033[0m\n";
    cout << "\033[1;37m" << setw(8) << "Island" << " | " << setw(15) << "Current/Required" 
         << " | " << setw(8) << "Status" << "\033[0m\n";
    cout << "\033[1;30m" << string(35, '-') << "\033[0m\n";
    
    int solvedCount = 0;
    for (const auto& island : state.islands) {
        int current = currentDegree(state, island.id);
        bool isIslandSolved = (current == island.requiredDegree);
        if (isIslandSolved) solvedCount++;
        
        string status = isIslandSolved ? "\033[1;32mOK\033[0m" : "\033[1;31mNeed more\033[0m";
        
        cout << setw(8) << island.id << " | " 
             << setw(8) << current << "/" << setw(6) << island.requiredDegree 
             << " | " << status << "\n";
    }
    
    cout << "\n\033[1;33mProgress: " << solvedCount << "/" << state.islands.size() 
         << " islands completed\033[0m\n";
}

//// ------------------ Level ------------------

vector<Island> createLevel() {
    return {
        {1,1,1,2}, {2,1,3,4}, {3,1,6,1},
        {4,2,4,4}, {5,2,7,2},
        {6,3,1,4}, {7,3,3,5},
        {8,4,4,3}, {9,4,6,1},
        {10,5,3,3}, {11,5,5,5}, {12,5,7,4},
        {13,6,1,2}, {14,6,4,1},
        {15,7,1,1}, {16,7,5,2}, {17,7,7,1}
    };
}

void printMap(const GameState& state) {
    // Create a grid to display
    string grid[8][8];
    
    // Initialize grid with empty spaces
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            grid[i][j] = " · ";
        }
    }
    
    // Add connections to the grid first
    for(const Connection& conn : state.connections) {
        if(conn.bridges > 0) {
            // Find the island positions
            Island islandA, islandB;
            for(const Island& island : state.islands) {
                if(island.id == conn.islandA) islandA = island;
                if(island.id == conn.islandB) islandB = island;
            }
            
            // Draw bridges between islands
            if(conn.orientation == Orientation::HORIZONTAL) {
                int row = islandA.x;
                int startCol = min(islandA.y, islandB.y);
                int endCol = max(islandA.y, islandB.y);
                
                for(int col = startCol + 1; col < endCol; col++) {
                    if(conn.bridges == 1) {
                        grid[row][col] = " — ";
                    } else if(conn.bridges == 2) {
                        grid[row][col] = " = ";
                    }
                }
            } else if(conn.orientation == Orientation::VERTICAL) {
                int col = islandA.y;
                int startRow = min(islandA.x, islandB.x);
                int endRow = max(islandA.x, islandB.x);
                
                for(int row = startRow + 1; row < endRow; row++) {
                    if(conn.bridges == 1) {
                        grid[row][col] = " | ";
                    } else if(conn.bridges == 2) {
                        grid[row][col] = " ‖ ";
                    }
                }
            }
        }
    }
    
    // Place islands on the grid (this will overwrite any bridge characters at island positions)
    for(const Island& island : state.islands) {
        if(island.x >= 0 && island.x < 8 && island.y >= 0 && island.y < 8) {
            grid[island.x][island.y] = string(" ") + char('0' + island.requiredDegree) + " ";
        }
    }
    
    // Print the grid with nice formatting
    cout << "\n╔══════════════════════════════════════════════════╗" << endl;
    cout << "║         HASHIWOKAKERO PUZZLE SOLUTION            ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║      ";
    
    // Print column headers
    for(int j = 0; j < 8; j++) {
        cout << " " << j << "  ";
    }
    cout << "    ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    
    // Print each row
    for(int i = 0; i < 8; i++){
        cout << "║  " << i << " ║";
        for(int j = 0; j < 8; j++){
            if(grid[i][j].find('0') != string::npos || 
               grid[i][j].find('1') != string::npos || 
               grid[i][j].find('2') != string::npos || 
               grid[i][j].find('3') != string::npos || 
               grid[i][j].find('4') != string::npos || 
               grid[i][j].find('5') != string::npos || 
               grid[i][j].find('6') != string::npos || 
               grid[i][j].find('7') != string::npos || 
               grid[i][j].find('8') != string::npos || 
               grid[i][j].find('9') != string::npos) {
                // Island - color in cyan
                cout << "\033[1;36m" << grid[i][j] << "\033[0m";
            } else if(grid[i][j].find("—") != string::npos || 
                      grid[i][j].find("=") != string::npos || 
                      grid[i][j].find("|") != string::npos || 
                      grid[i][j].find("‖") != string::npos) {
                // Bridge - color in yellow
                cout << "\033[1;33m" << grid[i][j] << "\033[0m";
            } else {
                // Empty water
                cout << grid[i][j];
            }
        }
        cout << "║" << endl;
    }
    cout << "╚══════════════════════════════════════════════════╝" << endl;
}

//// ------------------ Console Driver ------------------

int main() {
    GameState state;
    state.islands = createLevel();
    state.connections = computeConnections(state.islands);

    clearScreen();
    printMenu();
    
    string input;
    while (true) {
        // Display current game state
        printMap(state);
        
        // Check if solved
        if (isSolved(state)) {
            cout << "\n\033[1;32m🎉 CONGRATULATIONS! PUZZLE SOLVED! 🎉\033[0m\n";
            cout << "\033[1;33mAll islands have the correct number of bridges!\033[0m\n";
            break;
        }
        
        cout << "\n\033[1;37mEnter command (or number for connection): \033[0m";
        cin >> input;
        
        if (input == "q" || input == "quit") {
            cout << "\033[1;33mThanks for playing!\033[0m\n";
            break;
        }
        else if (input == "m" || input == "menu") {
            clearScreen();
            printMenu();
        }
        else if (input == "c" || input == "connections") {
            printConnections(state);
        }
        else if (input == "s" || input == "stats") {
            printStatistics(state);
        }
        else {
            // Try to parse as connection index
            try {
                int idx = stoi(input);
                if (idx < 0 || idx >= (int)state.connections.size()) {
                    cout << "\033[1;31mInvalid connection ID. Use 'c' to see available connections.\033[0m\n";
                } else {
                    if (!tryToggleBridge(state, idx)) {
                        cout << "\033[1;31mIllegal move! This would exceed an island's degree limit.\033[0m\n";
                    } else {
                        cout << "\033[1;32mBridge toggled successfully!\033[0m\n";
                    }
                }
            } catch (const exception& e) {
                cout << "\033[1;31mInvalid input. Type 'm' for menu or a connection number.\033[0m\n";
            }
        }
        
        // Small pause for readability
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
    return 0;
}