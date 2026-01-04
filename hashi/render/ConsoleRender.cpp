#include "ConsoleRender.h"
#include "../engine/GameUtils.h"
#include <iostream>
#include <iomanip>
#include <string>

const int GRID_SIZE = 8;

void renderMap(const GameState& state) {
    // Create a grid to display
    std::string grid[GRID_SIZE][GRID_SIZE];
    
    // Initialize grid with empty spaces
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
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
                int startCol = std::min(islandA.y, islandB.y);
                int endCol = std::max(islandA.y, islandB.y);
                
                for(int col = startCol + 1; col < endCol; col++) {
                    if(conn.bridges == 1) {
                        grid[row][col] = " — ";
                    } else if(conn.bridges == 2) {
                        grid[row][col] = " = ";
                    }
                }
            } else if(conn.orientation == Orientation::VERTICAL) {
                int col = islandA.y;
                int startRow = std::min(islandA.x, islandB.x);
                int endRow = std::max(islandA.x, islandB.x);
                
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
    
    // Place islands on the grid
    for(const Island& island : state.islands) {
        if(island.x >= 0 && island.x < GRID_SIZE && island.y >= 0 && island.y < GRID_SIZE) {
            grid[island.x][island.y] = std::string(" ") + char('0' + island.requiredDegree) + " ";
        }
    }
    
    // Print the grid
    std::cout << "\n╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         HASHIWOKAKERO PUZZLE SOLUTION            ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║      ";
    
    // Print column headers
    for(int j = 0; j < GRID_SIZE; j++) {
        std::cout << " " << j << "  ";
    }
    std::cout << "    ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════╣" << std::endl;
    
    // Print each row
    for(int i = 0; i < GRID_SIZE; i++){
        std::cout << "║  " << i << " ║";
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j].find('0') != std::string::npos || 
               grid[i][j].find('1') != std::string::npos || 
               grid[i][j].find('2') != std::string::npos || 
               grid[i][j].find('3') != std::string::npos || 
               grid[i][j].find('4') != std::string::npos || 
               grid[i][j].find('5') != std::string::npos || 
               grid[i][j].find('6') != std::string::npos || 
               grid[i][j].find('7') != std::string::npos || 
               grid[i][j].find('8') != std::string::npos || 
               grid[i][j].find('9') != std::string::npos) {
                // Island - color in cyan
                std::cout << "\033[1;36m" << grid[i][j] << "\033[0m";
            } else if(grid[i][j].find("—") != std::string::npos || 
                      grid[i][j].find("=") != std::string::npos || 
                      grid[i][j].find("|") != std::string::npos || 
                      grid[i][j].find("‖") != std::string::npos) {
                // Bridge - color in yellow
                std::cout << "\033[1;33m" << grid[i][j] << "\033[0m";
            } else {
                // Empty water
                std::cout << grid[i][j];
            }
        }
        std::cout << "║" << std::endl;
    }
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;
}

void renderConnections(const GameState& state) {
    std::cout << "\n\033[1;33mAvailable Connections:\033[0m\n";
    std::cout << "\033[1;37m" << std::setw(4) << "ID" << " | " << std::setw(10) << "Islands" 
         << " | " << std::setw(11) << "Orientation" << " | " << std::setw(8) << "Bridges" << "\033[0m\n";
    std::cout << "\033[1;30m" << std::string(45, '-') << "\033[0m\n";
    
    for (size_t i = 0; i < state.connections.size(); i++) {
        const auto& c = state.connections[i];
        std::string orientation = (c.orientation == Orientation::HORIZONTAL) ? "Horizontal" : "Vertical";
        std::string bridgeDisplay = "";
        
        if (c.bridges == 0) bridgeDisplay = "None";
        else if (c.bridges == 1) bridgeDisplay = "Single";
        else if (c.bridges == 2) bridgeDisplay = "Double";
        
        std::string color = "\033[0m";
        if (c.bridges == 1) color = "\033[1;33m";
        else if (c.bridges == 2) color = "\033[1;31m";
        
        std::cout << color << std::setw(4) << i << " | " 
             << std::setw(4) << c.islandA << " <-> " << std::setw(2) << c.islandB 
             << " | " << std::setw(11) << orientation 
             << " | " << std::setw(8) << bridgeDisplay << "\033[0m\n";
    }
}

void renderStats(const GameState& state) {
    std::cout << "\n\033[1;36mGame Statistics:\033[0m\n";
    std::cout << "\033[1;37m" << std::setw(8) << "Island" << " | " << std::setw(15) << "Current/Required" 
         << " | " << std::setw(8) << "Status" << "\033[0m\n";
    std::cout << "\033[1;30m" << std::string(35, '-') << "\033[0m\n";
    
    int solvedCount = 0;
    for (const auto& island : state.islands) {
        int current = currentDegree(state, island.id);
        bool isIslandSolved = (current == island.requiredDegree);
        if (isIslandSolved) solvedCount++;
        
        std::string status = isIslandSolved ? "\033[1;32mOK\033[0m" : "\033[1;31mNeed more\033[0m";
        
        std::cout << std::setw(8) << island.id << " | " 
             << std::setw(8) << current << "/" << std::setw(6) << island.requiredDegree 
             << " | " << status << "\n";
    }
    
    std::cout << "\n\033[1;33mProgress: " << solvedCount << "/" << state.islands.size() 
         << " islands completed\033[0m\n";
}