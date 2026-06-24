# Version Control System

A Git-inspired Version Control System implemented in C++ using custom data structures and algorithms.

The project supports version tracking, snapshot management, rollback operations, pattern searching, repository analytics, and command journaling with automatic recovery.

---

## Features

### Version Management

* Create and manage files
* Maintain version history using a version tree
* Create snapshots with messages
* Roll back to previous versions
* Support branching version histories

### Search

* Search patterns in the current version
* Search patterns across all versions
* Knuth-Morris-Pratt (KMP) based pattern matching

### Analytics

* View file history
* Display file statistics
* Track recently modified files
* Track files with the largest version histories

### Persistence

* Command journaling
* Automatic repository recovery on startup
* Repository reset support

---

## Data Structures Used

### Version Tree

Stores file versions as a tree rather than a linear chain, allowing branching histories.

### FileRegistry

Custom open-addressing hash table used for:

filename → FileVersion*

Average lookup complexity: O(1)

### VersionIndex

Direct indexing structure used for:

versionId → TreeNode*

Lookup complexity: O(1)

### PointerIndexMap

Custom pointer-based hash map used by heaps to maintain node positions efficiently.

### Binary Heap

Custom heap implementation used for:

* Recent Files
* Largest Files

Operations:

* Insert: O(log N)
* Remove: O(log N)
* Peek: O(1)

### KMP Pattern Matching

Used for efficient pattern searching.

Complexity:

O(N + M)

where:

* N = text length
* M = pattern length

---

## Supported Commands

### File Operations

CREATE <filename>

READ <filename>

INSERT <filename> <content>

UPDATE <filename> <content>

---

### Version Operations

SNAPSHOT <filename> <message>

ROLLBACK <filename>

ROLLBACK <filename> <versionId>

HISTORY <filename>

---

### Search Operations

SEARCH <filename> <pattern>

SEARCH_HISTORY <filename> <pattern>

---

### Analytics

STATS <filename>

RECENT_FILES <count>

BIGGEST_FILES <count>

---

### Repository Management

CLEAR

---

## Recovery Mechanism

All mutating operations are appended to a command journal.

On application startup:

1. commands.log is loaded
2. Commands are replayed internally
3. Repository state is reconstructed automatically

This provides lightweight persistence without requiring full object serialization.

---

## Complexity Analysis

| Operation      | Complexity   |
| -------------- | ------------ |
| File Lookup    | O(1) Average |
| Version Lookup | O(1)         |
| Snapshot       | O(1)         |
| Rollback       | O(1)         |
| Pattern Search | O(N + M)     |
| Heap Insert    | O(log N)     |
| Heap Remove    | O(log N)     |

---

## Technologies

* C++17
* Object-Oriented Programming
* Hash Tables
* Binary Heaps
* Trees
* KMP Pattern Matching
* Command Journaling
