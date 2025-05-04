# Finite State Machine Regex

A robust regular expression engine implemented using finite state automata principles, offering efficient pattern matching without traditional backtracking algorithms.

## Introduction

This project implements a regular expression engine based on finite state machines (FSM). Unlike conventional regex libraries that rely on backtracking algorithms, our implementation directly constructs and traverses state machines derived from regex patterns, providing efficient and predictable performance characteristics.

## Features

- **Pattern Matching**: Evaluate strings against regex patterns with deterministic results
- **Automata-Based**: Uses finite state machine theory for reliable pattern recognition
- **Efficient Execution**: Avoids potential exponential complexity issues of backtracking algorithms

### Supported Syntax

| Operator | Description | Example |
|----------|-------------|---------|
| `.` | Matches any single character | `a.c` matches "abc", "adc", etc. |
| `*` | Matches zero or more occurrences of the preceding element | `ab*c` matches "ac", "abc", "abbc", etc. |
| `+` | Matches one or more occurrences of the preceding element | `ab+c` matches "abc", "abbc", but not "ac" |
| `[abc]` | Character class - matches any character listed | `[aeiou]` matches any vowel |
| `[a-z]` | Character range - matches any character in the range | `[a-z]` matches any lowercase letter |
| `[^0-9]` | Negated character class - matches any character not listed | `[^0-9]` matches any non-digit |

## Architecture

The implementation follows object-oriented design principles with a hierarchy of state classes representing different components of the regular expression:

```
State (Abstract Base Class)
??? StartState
??? TerminationState
??? AsciiState
??? DotState
??? AsciiRangeState
??? ClassState
```

### Component Descriptions

- **State**: Abstract base class defining the interface for all states
- **StartState**: Marks the entry point of the automaton
- **TerminationState**: Represents accepting/final states
- **AsciiState**: Matches a specific character
- **DotState**: Wildcard state that matches any single character
- **AsciiRangeState**: Handles character ranges (e.g., a-z)
- **ClassState**: Processes character classes with optional negation

### FSM Construction Process

1. Parse the regex pattern character by character
2. Create appropriate states for each element in the pattern
3. Connect states with transitions based on operators
4. Handle special operators like `*` and `+` by creating appropriate loops and branches
5. Establish paths to the termination state

## Building and Running

### Prerequisites

- C++17 compatible compiler
- CMake (3.10 or higher)
- Standard C++ libraries

### Installation

#### Step 1: Clone the Repository

```bash
git clone https://github.com/SmaugSatou/Discrete-math-Finite-state-machine-regex.git
cd Discrete-math-Finite-state-machine-regex
```

#### Step 2: Build the Project

**For Unix-based Systems (Linux, macOS):**

```bash
mkdir build && cd build
cmake ..
make
```

**For Windows:**

```bash
mkdir build
cd build
cmake ..
```

Then either:

```bash
cmake --build . --config Debug
```

Or for optimized build:

```bash
cmake --build . --config Release
```

### Usage

The program accepts a regex pattern followed by one or more strings to match:

```bash
./regex_fsm <regex_pattern> <string1> <string2> ... <stringN>
```

### Examples

**Example 1: Basic Pattern**

```bash
./Debug/regex_fsm "a.c*" "abc" "abccc" "adc" "ab"
```

Output:
```
Checking "abc": Matched
Checking "abccc": Matched
Checking "adc": Matched
Checking "ab": Matched
```

**Example 2: Character Classes**

```bash
./Debug/regex_fsm "[a-z]+[0-9]*" "abc123" "123abc" "abc" "123"
```

Output:
```
Checking "abc123": Matched
Checking "123abc": Not matched
Checking "abc": Matched
Checking "123": Not matched
```

**Example 3: Negated Character Class**

```bash
./Debug/regex_fsm "[^0-9]+" "abc" "123" "abc123"
```

Output:
```
Checking "abc": Matched
Checking "123": Not matched
Checking "abc123": Not matched
```

## Implementation Details

### RegexFSM Class

The core of the implementation is the `RegexFSM` class that orchestrates:

1. **Pattern Parsing**: Converts the regex string into a sequence of tokens
2. **FSM Construction**: Builds states and transitions based on the parsed pattern
3. **String Evaluation**: Traverses the FSM to determine if strings match the pattern

### State Traversal Algorithm

The matching algorithm follows these steps:

1. Start at the initial state
2. For each character in the input string:
   - Compute all possible next states (including epsilon transitions)
   - Transition to these states
3. After processing the entire string, check if any current state is an accepting state
4. Return match result based on whether an accepting state was reached

### Time and Space Complexity

- **Time Complexity**: O(m × n)
  - m = length of the input string
  - n = number of states in the FSM
- **Space Complexity**: O(n)
  - Storage for the state machine

## Design Considerations

### NFA vs DFA

This implementation uses a Nondeterministic Finite Automaton (NFA) approach, allowing it to:
- Directly represent regex constructs more naturally
- Handle epsilon transitions for operations like `*`
- Support simultaneous active states during matching

## Limitations

### Current Limitations

- No support for grouping with parentheses `()`
- No support for alternation with the pipe operator `|`
- No support for precise quantifiers like `{n}`, `{n,}`, or `{n,m}`
- No support for anchors `^` and `$` (except for `^` in character classes)
- No backreferences or lookahead/lookbehind assertions
