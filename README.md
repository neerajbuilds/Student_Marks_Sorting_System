# Student Marks Sorting System

**Course:** Design and Analysis of Algorithms (DAA)  
**Language:** C++  
**Type:** Menu-Driven Console Application

---

## Project Overview

A beginner-friendly C++ application that allows a user to manage student records,
sort them by marks using two classic sorting algorithms, search for a student by name,
and measure the performance (time taken) of each sorting algorithm.

---

## Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Input Students** | Enter any number of student names and marks |
| 2 | **Display Records** | View all students in a formatted table |
| 3 | **Bubble Sort** | Sort students by marks using Bubble Sort |
| 4 | **Quick Sort** | Sort students by marks using Quick Sort |
| 5 | **Linear Search** | Find a student record by their full name |
| 6 | **Highest Marks** | Display the student with the highest score |
| 7 | **Lowest Marks** | Display the student with the lowest score |
| 8 | **Timing** | Measure and display the time taken by each sort algorithm |

---

## Menu Options

```
1. Display Students
2. Bubble Sort by Marks
3. Quick Sort by Marks
4. Search Student by Name
5. Highest Marks
6. Lowest Marks
7. Exit
```

---

## Algorithms Used

### 1. Bubble Sort
- **Type:** Comparison-based, iterative
- **Strategy:** Repeatedly compares adjacent pairs and swaps if out of order
- **Optimization:** Uses a `swapped` flag to stop early if already sorted

### 2. Quick Sort
- **Type:** Comparison-based, divide-and-conquer, recursive
- **Strategy:** Picks a pivot (last element), partitions array, then recursively sorts sub-arrays
- **Pivot choice:** Last element of the current sub-array

### 3. Linear Search
- **Type:** Sequential search
- **Strategy:** Checks each element one by one until the target is found
- **Match:** Case-sensitive exact name match

---

## Time Complexity Analysis

| Algorithm | Best Case | Average Case | Worst Case | Space |
|-----------|-----------|--------------|------------|-------|
| **Bubble Sort** | O(n) | O(n²) | O(n²) | O(1) |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) |
| **Linear Search** | O(1) | O(n) | O(n) | O(1) |

> **Note:** Quick Sort's worst case occurs when the pivot is always the smallest or largest element (e.g., already sorted data).

---

## Data Structures Used

- **Array of Structures (`Student[]`)** — Stores all student records
- **`struct Student`** — Contains `name` (string) and `marks` (float)

---

## How to Compile and Run

### Using g++ (MinGW / GCC)
```bash
g++ main.cpp -o StudentSortingSystem
StudentSortingSystem
```

### Using Visual Studio Code
1. Open the project folder in VS Code
2. Compile with: `g++ main.cpp -o StudentSortingSystem`
3. Run with: `.\StudentSortingSystem`

### Using Online Compiler
Paste the `main.cpp` code into any C++ online compiler such as:
- https://www.onlinegdb.com/
- https://cpp.sh/
- https://ideone.com/

---

## Project File Structure

```
DAA_PROJECT/
│
├── main.cpp           ← Main C++ source code
├── README.md          ← Project documentation (this file)
├── report.txt         ← Formal project report
└── sample_input.txt   ← Sample student data for testing
```

---

## Author Notes

- The original student array is **never modified** during sorting — a copy is used each time.
- Timing is measured using `std::chrono::high_resolution_clock` (microsecond precision).
- Input validation ensures marks stay within 0–100.
