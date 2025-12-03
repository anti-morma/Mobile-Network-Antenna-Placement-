# Mobile Network Antenna Placement

## Project Overview
This repository contains a C implementation for solving the "Mobile Network Antenna Placement" problem.

The goal is to select a set of non-adjacent cities to install antennas in, such that the total population covered is maximized.

[cite_start]This exercise is derived from the **Algorithms and Data Structures** course at **Politecnico di Torino**[cite: 3, 5, 7].

## Approach: Dynamic Programming vs. Brute Force
This project marks my transition from brute-force approaches to **Dynamic Programming**.

* **Naive Approach (Powerset):** A brute-force solution would evaluate all valid subsets of antennas. [cite_start]This results in an exponential time complexity of $O(2^n)$, which is inefficient for large datasets[cite: 28, 29].
* [cite_start]**Dynamic Programming (Implemented):** By identifying optimal substructures, this solution solves the problem in **linear time $O(n)$**[cite: 25, 82].

The first city is hardcoded due to an explicit costraint from the exercise description.
### Algorithm Logic
Let `opt[i]` be the maximum population covered considering cities from 1 to `i`. The recurrence relation is defined as:

$$opt[i] = \max(opt[i-1], \text{population}[i] + opt[i-2])$$

* **Case 1:** Antenna not placed at `i`. [cite_start]The value is the same as the optimal solution for `i-1`[cite: 38, 48].
* **Case 2:** Antenna placed at `i`. [cite_start]The value is the population of city `i` plus the optimal solution for `i-2` (since `i-1` cannot be selected)[cite: 39, 47].

## Technical Implementation
* **Language:** C
* **Build System:** Make
* **Refactoring:** Code structure, English comments, and the Makefile were refined with the assistance of AI tools to ensure standard formatting and clarity.

## Usage

### Compilation
Use the provided Makefile to compile the project:
```bash
make
