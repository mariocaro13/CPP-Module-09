*This project has been created as part of the 42 curriculum by mcaro-ro*

# CPP Module 09 – STL & Algorithmic Problem Solving

## 📖 Description
CPP Module 09 introduces practical usage of the **C++ Standard Template Library (STL)** within the C++98 standard.  
Across three exercises, you will work with:

- Standard containers (`map`, `stack`, `vector`, `deque`)
- Data parsing and validation
- Efficient searching with `lower_bound`
- Reverse Polish Notation evaluation
- The Ford–Johnson merge-insert sorting algorithm

The module focuses on writing efficient, container‑based solutions and handling real‑world data processing scenarios.

## ⚙️ Instructions
1. Clone the repository from your 42 Git workspace.
2. Navigate into the desired exercise folder (`ex00`, `ex01`, `ex02`).
3. Compile the project using: make
4. Each exercise includes its own `main.cpp` for testing.
5. Clean build artifacts with:
	- make clean
	- make fclean
	- make re

## 📚 Concepts Covered

### 1. STL Containers
Each exercise requires different containers:
- `std::map` for sorted key/value lookups (ex00)
- `std::stack` for expression evaluation (ex01)
- `std::vector` and `std::deque` for high‑performance sorting (ex02)

### 2. Data Parsing & Validation
- Reading files line by line
- Validating dates and numeric values
- Handling malformed input gracefully

### 3. Searching & Efficiency
- Using `lower_bound` to find the closest valid date
- Leveraging ordered containers for logarithmic search time

### 4. Reverse Polish Notation (RPN)
- Evaluating mathematical expressions without parentheses
- Using a stack to process operands and operators

### 5. Ford–Johnson Merge-Insertion Sort
- Implementing the algorithm described by Knuth
- Comparing performance between two different STL containers
- Handling large sequences (3000+ integers)

## 🧱 Exercises

### ex00 – Bitcoin Exchange
Implements a program named **btc** that:
- Loads a CSV database of historical Bitcoin prices.
- Processes an input file with lines formatted as:  
`YYYY-MM-DD | value`
- Validates dates and values.
- Uses `std::map` to find the closest earlier date.
- Outputs the computed result or an appropriate error message.

### ex01 – Reverse Polish Notation (RPN)
Implements a program named **RPN** that:
- Receives a mathematical expression in Reverse Polish Notation.
- Uses a stack to evaluate the expression.
- Supports the operators `+ - * /`.
- Prints the result or an error if the expression is invalid.

### ex02 – PmergeMe
Implements a program named **PmergeMe** that:
- Accepts a sequence of positive integers as arguments.
- Sorts the sequence using **merge-insert sort (Ford–Johnson)**.
- Uses **two different STL containers** (vector and deque).
- Measures and displays execution time for each container.
- Handles large sequences efficiently.
