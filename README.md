# C_Ex4

This project implements a simple graph data structure in C, supporting operations such as adding and removing nodes and edges, as well as computing shortest paths between nodes.

## Features

- Create and manage a directed graph with nodes and edges.
- Add or remove nodes and edges dynamically.
- Compute the shortest path between two nodes using Dijkstra's algorithm.

## Project Structure

C_Ex4/

├── edges.c       # Implementation of edge-related functions

├── edges.h       # Declarations for edge-related functions

├── graph.c       # Implementation of graph-related functions

├── graph.h       # Declarations for graph-related functions

├── nodes.c       # Implementation of node-related functions

├── nodes.h       # Declarations for node-related functions

├── main.c        # Entry point of the program

├── makefile      # Build configuration

└── .gitignore    # Git ignore file

## Compilation

To compile the project, ensure you have a C compiler installed (e.g., `gcc`), then run:

```bash
make
```

This will produce an executable named graph.

## Usage

After compilation, run the program using:

```bash
./graph
```

The program accepts commands to manipulate the graph. For example:
	•	A – Add a new node
	•	B – Add or update an edge
	•	D – Delete a node
	•	S – Compute the shortest path between two nodes
	•	T – Terminate the program

Note: Input must follow the expected format; see main.c for parsing logic.

## Project by

Avichai Mizrachi
