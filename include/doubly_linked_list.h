#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

// Copyright 2026 Anna
//
// Function prototypes for implementing a Doubly Linked List

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "clinkd_common.h"

/** Template struct of a doubly linked list */
typedef struct DLLNode {
  struct DLLNode* prev; // Previous Node
  struct DLLNode* next; // Next Node
  struct DLLNode* tail; // Last Node
  size_t size;          // Total nodes in the list,
                        // auto increment/decrement
} DLLNode;

/**
 * Adds a node on the end of the list
 *
 * The node must be embedded on a user define struct.
 * The library does not allocate or copy any data.
 *
 * @param head Pointer to a pointer to the head node.
 * @param node Pointer to the node to append.
 */
void DLLAppend(DLLNode** head, DLLNode* node);

#ifdef __cplusplus
}
#endif

#endif
