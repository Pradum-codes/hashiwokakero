# Hashiwokakero Engine (Bridges Puzzle)

A **logic-first, console-based implementation of the Hashiwokakero (Bridges) puzzle**, built in C++ with a clean, modular architecture.

This project focuses on **graph modeling, constraint validation, and engine design**, rather than UI or animations.  
All game rules are enforced through deterministic graph logic.

---

## 🧠 About Hashiwokakero

Hashiwokakero is a Japanese logic puzzle where:
- Each island has a required number of bridges
- Bridges connect islands horizontally or vertically
- At most two bridges can connect the same pair of islands
- Bridges may not cross
- All islands must form a single connected graph

This project models the puzzle as a **constrained undirected graph**.

---

## ✨ Features

- Graph-based core model (islands = nodes, connections = edges)
- Deterministic move validation
- Degree constraint enforcement
- Bridge crossing detection
- Connectivity validation
- Modular engine / renderer / UI separation
- Interactive ANSI-colored console interface
- Clean Makefile with dependency tracking

---

## 🏗️ Project Structure
.
├── model/ # Core data structures (Island, Connection, GameState)
├── engine/ # Game logic, validators, graph construction
├── render/ # Console rendering (no game logic)
├── ui/ # Console input & interaction
├── levels/ # Puzzle definitions
├── main.cpp # Entry point
├── Makefile
└── README.md


**Design rule:**  
Each layer depends only on layers below it — never sideways or upward.

---

## 🚀 Build & Run

### Requirements
- `g++` (C++17 or newer)
- GNU Make

### Build
```bash
make
```
### Run
```bash
./hashi
```

### Debug build
```bash
make debug
```

## 🎮 Controls (Console)
```bash
Enter a connection number → toggle bridges (0 → 1 → 2 → 0)
m → show menu
c → list all connections
s → show island statistics
q → quit
```

## 🧩 Architecture Notes

- Islands are immutable nodes
- Connections are precomputed edges
- The only mutable state is the bridge count per connection
- Island degrees are derived, never stored
- Rendering is strictly read-only
- This design allows easy extension to:
- solvers (DFS / backtracking)
- undo/redo
- GUI or Android frontends
- Kotlin or Java ports