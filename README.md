# Warehouse Management System (C++26)

A terminal-based Warehouse Management System implemented in C++ to manage inventory with efficient search and priority management.

## Features

1.  **Add Item**: Store new items with ID, Name, Stock, Shelf Location, and Priority.
2.  **Search Item**: Fast lookup using Hash Table by ID.
3.  **Display All Items**: View the entire inventory.
4.  **Highest Priority Item**: View the next item to be processed.
5.  **Remove Item**: Process and remove items based on priority.
6.  **Priority Queue**: View items sorted by priority.

## Tech Stack

-   **Language**: C++26 (or C++21 as per Specification)
-   **Structure**:
    -   **Hash Table**: For $O(1)$ average time complexity search by ID.
    -   **Min Heap**: For $O(\log n)$ priority management.

## Data Structure: `Barang`

Each item (`Barang`) contains:
-   `int id`: Unique identifier.
-   `string nama`: Name of the item.
-   `int stok`: Quantity in stock.
-   `string lokasiRak`: Storage location.
-   `int prioritas`: Priority level (lower value = higher priority).

## Getting Started

### Prerequisites

-   C++ compiler supporting C++21/C++26 (e.g., GCC 13+, Clang 16+, or MSVC).

### Compilation

```bash
g++ main.cpp & all file need -o sortirBarang
```

### Running

```bash
./sortirBarang
```

## Project Structure

-   `main.cpp`: Entry point and CLI menu logic.
-   `Barang.cpp`: `Barang` class definition.
-   `Specification.md`: Project requirements and goals.
-   `Plan.md`: Development phases.
-   `Tasks.md`: Project roadmap and progress.
