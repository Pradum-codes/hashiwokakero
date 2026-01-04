#include "ConsoleUI.h"
#include "../render/ConsoleRender.h"
#include "../engine/Moves.h"
#include "../engine/Validators.h"
#include <iostream>
#include <string>

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void printMenu() {
    std::cout << "\n\033[1;32m=== HASHIWOKAKERO CONSOLE GAME ===\033[0m\n";
    std::cout << "\n\033[1;33mCommands:\033[0m\n";
    std::cout << "  [number] - Toggle bridge connection (0, 1, or 2 bridges)\n";
    std::cout << "  'm'      - Show this menu\n";
    std::cout << "  'c'      - Show all connections\n";
    std::cout << "  's'      - Show game statistics\n";
    std::cout << "  'q'      - Quit game\n";
    std::cout << "\n\033[1;36mGoal:\033[0m Connect all islands with bridges so that each\n";
    std::cout << "      island has exactly the number of bridges shown.\\n";
}

void runConsoleGame(GameState& state) {
    clearScreen();
    printMenu();
    
    std::string input;
    while (true) {
        // Display current game state
        renderMap(state);
        
        // Check if solved
        if (isSolved(state)) {
            std::cout << "\n\033[1;32m🎉 CONGRATULATIONS! PUZZLE SOLVED! 🎉\033[0m\n";
            std::cout << "\033[1;33mAll islands have the correct number of bridges!\033[0m\n";
            break;
        }
        
        std::cout << "\n\033[1;37mEnter command (or number for connection): \033[0m";
        std::cin >> input;
        
        if (input == "q" || input == "quit") {
            std::cout << "\033[1;33mThanks for playing!\033[0m\n";
            break;
        }
        else if (input == "m" || input == "menu") {
            clearScreen();
            printMenu();
        }
        else if (input == "c" || input == "connections") {
            renderConnections(state);
        }
        else if (input == "s" || input == "stats") {
            renderStats(state);
        }
        else {
            // Try to parse as connection index
            try {
                int idx = std::stoi(input);
                if (idx < 0 || idx >= static_cast<int>(state.connections.size())) {
                    std::cout << "\033[1;31mInvalid connection ID. Use 'c' to see available connections.\033[0m\n";
                } else {
                    if (!tryToggleBridge(state, idx)) {
                        std::cout << "\033[1;31mIllegal move! This would exceed an island's degree limit.\033[0m\n";
                    } else {
                        std::cout << "\033[1;32mBridge toggled successfully!\033[0m\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cout << "\033[1;31mInvalid input. Type 'm' for menu or a connection number.\033[0m\n";
            }
        }
        
        // Small pause for readability
        std::cout << "\\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}