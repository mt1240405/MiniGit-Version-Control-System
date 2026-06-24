# Architecture Overview

## High-Level Structure

```text
CommandProcessor
│
├── FileRegistry
│   └── FileVersion
│       ├── TreeNode
│       └── VersionIndex
│
├── BinaryHeap<RecentFileComparator>
│   └── PointerIndexMap
│
├── BinaryHeap<LargestVersionComparator>
│   └── PointerIndexMap
│
├── KmpPatternMatcher
│
└── CommandJournal
```

---

## Component Responsibilities

### CommandProcessor

Acts as the central controller of the application.

Responsibilities:

* Parse user commands
* Dispatch operations
* Manage recovery process
* Coordinate all subsystems

---

### FileRegistry

Custom hash table that stores all tracked files.

Mapping:

filename → FileVersion*

Features:

* Open addressing
* Linear probing
* Average O(1) lookup

---

### FileVersion

Represents a single tracked file.

Stores:

* File metadata
* Current active version
* Root version
* Version count
* Version index

Provides:

* Insert
* Update
* Snapshot
* Rollback
* Search
* Statistics

---

### TreeNode

Represents a version within a file.

Stores:

* Version ID
* Content
* Snapshot message
* Creation timestamp
* Snapshot timestamp
* Parent pointer
* Child pointers

Together, TreeNodes form a version tree.

---

### VersionIndex

Provides direct access to versions.

Mapping:

versionId → TreeNode*

Allows constant-time rollback to specific versions.

---

### BinaryHeap

Custom heap implementation used for repository analytics.

Instances:

1. Recent Files Heap
2. Largest Files Heap

Complexities:

* Push: O(log N)
* Pop: O(log N)
* Top: O(1)

---

### PointerIndexMap

Supports efficient heap updates.

Mapping:

FileVersion* → Heap Index

Allows existing heap nodes to be updated without rebuilding the heap.

---

### KmpPatternMatcher

Implements the Knuth-Morris-Pratt algorithm.

Used by:

* SEARCH
* SEARCH_HISTORY

Complexity:

O(N + M)

---

### CommandJournal

Provides lightweight persistence.

Responsibilities:

* Record mutating commands
* Store repository activity
* Reconstruct repository state on startup

Journaled Commands:

* CREATE
* INSERT
* UPDATE
* SNAPSHOT
* ROLLBACK

---

## Design Decisions

### Version Tree Instead of Linear History

A tree structure allows branching version histories and more closely resembles real version control systems.

### Custom Hash Tables

Implemented to demonstrate collision handling, probing strategies, and constant-time lookup mechanisms.

### Custom Binary Heap

Provides efficient metadata queries while avoiding reliance on STL priority queues.

### KMP Search

Chosen over naive string matching to achieve linear-time pattern search.

### Command Journaling

Selected instead of full serialization to provide lightweight persistence while preserving repository operation history.

---

## Future Improvements

* Delta-based storage
* Binary serialization
* Concurrent repository access
* Compression of historical versions
* Networked multi-user repository support
