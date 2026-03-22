# 🔍 String Pattern Matching Algorithms (C++)

This project implements and compares several classical string searching algorithms used to find a pattern in a given text.

## 🚀 Implemented Algorithms

### 1. Naive Search
- Simple brute-force approach
- Time complexity: O(n * m)

### 2. Sunday Algorithm
- Optimization over naive search
- Uses character shift table
- Faster in practice for many cases

### 3. Double Sunday Algorithm
- Advanced version of Sunday algorithm
- Uses pairs of characters for better shifting
- Improves performance on larger inputs

### 4. Knuth-Morris-Pratt (KMP)
- Efficient linear-time algorithm
- Time complexity: O(n + m)
- Uses prefix function (LPS array)

---

## 🧠 Key Concepts

- Pattern matching in strings  
- Time complexity analysis  
- Prefix function (LPS)  
- Optimization of search algorithms  

---

## How to Use

1. Clone the repository:

```bash
git clone https://github.com/khandaEnjoyer/Pattern-Matching-Algorithms.git
```
Change directory to the project folder:

```bash
cd Pattern-Matching-Algorithms
```
Compile the program (replace pattern_matching.cpp with your actual file name if different):

```bash
g++ -std=c++17 -O2 -o pattern_matching pattern_matching.cpp
```
Run the program:

```bash
./pattern_matching
```
Expected output for input="aabaaabaaa", word = "aba":

--- Naive Search ---
Match found at index: 1
Match found at index: 5

--- Sunday Search ---
Match found at index: 1
Match found at index: 5

--- Double Sunday Search ---
Match found at index: 1
Match found at index: 5

--- KMP Search ---
Match found at index: 1
Match found at index: 5
