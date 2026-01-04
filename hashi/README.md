# Hashiwokakero (Bridge Puzzle) Game

A console-based implementation of the classic Hashiwokakero puzzle game written in C++.

## Project Structure

The project is organized into modular components:

```
hashi/
├── main.cpp              # Entry point
├── Makefile             # Build configuration
├── model/               # Data structures
│   ├── GameState.h      # Game state container
│   ├── Island.h         # Island structure
│   └── Connection.h     # Connection structure
├── engine/              # Game logic
│   ├── GraphBuilder.h   # Connection discovery
│   ├── GraphBuilder.cpp
│   ├── GameUtils.h      # Utility functions
│   ├── GameUtils.cpp
│   ├── Moves.h          # Move validation
│   ├── Moves.cpp
│   ├── Validators.h     # Game state validation
│   └── Validators.cpp
├── levels/              # Level definitions
│   ├── LevelManager.h   # Level creation
│   └── LevelManager.cpp
├── render/              # Display system
│   ├── ConsoleRender.h  # Console rendering
│   └── ConsoleRender.cpp
└── ui/                  # User interface
    ├── ConsoleUI.h      # Console interface
    └── ConsoleUI.cpp
```

## Building and Running

### Prerequisites
- C++17 compatible compiler (g++)
- Make

### Build
```bash
make
```

### Run
```bash
make run
# or
./hashi
```

### Clean
```bash
make clean
```

## Game Controls

- **[number]** - Toggle bridge connection (0 → 1 → 2 → 0 bridges)
- **'c'** - Show all connections
- **'s'** - Show game statistics
- **'m'** - Show help menu
- **'q'** - Quit game

## Game Rules

1. Connect islands with bridges (horizontal or vertical only)
2. Each island must have exactly the number of bridges shown
3. Bridges cannot cross each other
4. All islands must be connected in a single network
5. Maximum 2 bridges between any pair of islands

## Module Descriptions

### Model
- **GameState**: Contains the complete game state (islands and connections)
- **Island**: Represents an island with position and required degree
- **Connection**: Represents a possible connection between islands

### Engine
- **GraphBuilder**: Discovers valid connections between islands
- **GameUtils**: Core utility functions for game state management
- **Moves**: Handles bridge placement and validation
- **Validators**: Validates game completion and connectivity

### Levels
- **LevelManager**: Creates and manages different puzzle levels

### Render
- **ConsoleRender**: Handles visual display of the game state

### UI
- **ConsoleUI**: Manages user input and game flow

## Adding New Features

### New Level
1. Add level function to `levels/LevelManager.cpp`
2. Declare in `levels/LevelManager.h`
3. Call from `main.cpp`

### New Validation Rule
1. Add function to `engine/Validators.cpp`
2. Update `isSolved()` function to include new check

### New Display Mode
1. Add rendering function to `render/ConsoleRender.cpp`
2. Update interface in `ui/ConsoleUI.cpp`

## Dependencies

- Standard C++ library
- ANSI terminal color support (for colored output)

## License

This is educational/demonstration code.