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
  struct DLLNode* prev; /**< Previous Node */
  struct DLLNode* next; /**< Next Node */
  struct DLLNode* tail; /**< Last Node */
  size_t size;          /**< Total nodes in the list, auto increment/decrement */
} DLLNode;

/**
 * Adds a node on the end of the list
 *
 * The node must be embedded on a user define struct.
 * The library does not allocate or copy any data.
 *
 * @param head Pointer to a pointer to the head node.
 * @param node Pointer to the node to append.
 * @return CLINKD_OK on success,
 *         CLINKD_ERROR if head or node is null
 *         CLINKD_FULL if the node limit is reached
 */
ClinkdStatus DLLAppend(DLLNode** head, DLLNode* node);

/**
 * Adds a node on the start of the list.
 *
 * @param head Pointer to a pointer to the head of the list
 * @param node Pointer to the node to append
 * @return CLINKD_OK on success,
 *         CLINKD_ERROR if head or node is null
 *         CLINKD_FULL if the node limit is reached
 */
ClinkdStatus DLLPrepend(DLLNode** head, DLLNode* node);

/**
 * Removes the node on the start of the list.
 *
 * @param head Pointer to a pointer to the head of the list
 * @return CLINKD_OK on success,
 *         CLINKD_ERROR if head or node is null
 */
ClinkdStatus DLLPopFront(DLLNode** head);

/**
 * Removes the node on the end of the list.
 *
 * @param head Pointer to a pointer to the head of the list
 * @return CLINKD_OK on success,
 *         CLINKD_ERROR if head or node is null
 */
ClinkdStatus DLLPopBack(DLLNode** head);

/**
 * Iterates through the list, calling print_node for each node.
 *
 * The caller uses clinkd_container_of inside print_node to access the parent struct.
 *
 * @param head Pointer to the head of the list.
 * @param print_node Function called to each node.
 */
void DLLNodes(DLLNode* head, void(*print_node)(DLLNode *));

/**
 * Returns the number of nodes in the list
 *
 * @param head Pointer to the head of the list
 * @return The total number of nodes in the list
 */
size_t DLLCountNodes(DLLNode* head);

#ifdef __cplusplus
}
#endif

#endif
