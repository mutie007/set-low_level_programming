# AI: Preemptive Bug Fixing

## Task Overview
This folder contains the work for the "AI: Preemptive Bug Fixing" assignment.  
A vulnerable C function that adds a node to the end of a singly linked list was reviewed using an AI tool. Both a logical linking error and a memory-safety issue (missing NULL check after malloc) were identified and fixed.

## Files

| File              | Description                                      |
|-------------------|--------------------------------------------------|
| `initial_code.c`  | Original vulnerable version of `add_node_end`    |
| `corrected_code.c`| Fixed version with proper linking + NULL check   |
| `README.md`       | This documentation file                          |

## AI Tool Used
**Claude**

## Key Fixes Applied
1. **Logical fix**: After the while loop `current` is NULL. The original code only updated the local pointer. The corrected version stops at the last real node and updates `current->next`.
2. **Memory safety fix**: Added an immediate NULL check after `malloc`. If allocation fails, the function returns NULL instead of causing a Segmentation Fault.
