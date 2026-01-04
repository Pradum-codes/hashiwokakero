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

