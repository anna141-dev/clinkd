#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

// Copyright 2026 Anna
//
// Function prototypes for implementing a Singly Linked List

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

 /**
  * Recovers a pointer to the parent struct from a pointer to one of its members.
  *
  * @param ptr    Pointer to the embedded member.
  * @param type   Type of the parent struct.
  * @param member Name of the member inside the parent struct.
  */
#define clinkd_container_of(ptr, type, member) \
  ((type *)((char *)(ptr)-offsetof(type, member)))

 /** Defines the maximum number of nodes allowed in a list */
#define LINKED_LIST_MAX_NODES 100000U

typedef struct SLLNode {
  struct SLLNode *next;
} SLLNode;

 /**
  * Adds a node at the end of the list.
  *
  * The node must be embedded in a user allocated struct. 
  * The library does not allocate or copy any data.
  *
  * @param head Pointer to a pointer to the head node.
  * @param node Pointer to the node to append.
  */
void SLLAppend(SLLNode **head, SLLNode *node);

 /**
  * Adds a node at the start of the list.
  *
  * @param head Pointer to a pointer to the head node.
  * @param node Pointer to the node to prepend.
  */

void SLLPrepend(SLLNode **head, SLLNode *node);

 /**
  * Removes the first node from the list.
  *
  * Does not free any memory. The caller is responsible 
  * for freeing the parent struct if needed. 
  * Use clinkd_container_of to recover it before calling this.
  *
  * @param head Pointer to a pointer to the head of the list.
  */
void SLLPopFront(SLLNode **head);

 /**
  * Removes the last node from the list.
  *
  * Does not free any memory. The caller is responsible for freeing the parent
  * struct if needed.
  *
  * @param head Pointer to a pointer to the head of the list.
  */
void SLLPopBack(SLLNode **head);

 /**
  * Finds the first node for which the predicate returns true.
  *
  * The predicate receives each SLLNode* and an optional context pointer (ctx),
  * which can be used to pass comparison data without globals.
  *
  * Example:
  *
  *   bool MatchValue(SLLNode *n, void *ctx) {
  *     MyItem *item = clinkd_container_of(n, MyItem, node);
  *     return item->value == *(int *)ctx;
  *   }
  *
  *   int target = 42;
  *   SLLNode *found = SLLFind(head, MatchValue, &target);
  *
  * @param head      Pointer to the head node.
  * @param predicate Function that returns true when the target is found.
  * @param ctx       Optional context pointer forwarded to the predicate.
  * @return Pointer to the first matching node, or NULL if not found.
  */
SLLNode *SLLFind(SLLNode *head, bool (*predicate)(SLLNode *, void *),
                 void *ctx);

 /**
  * Inserts a node at a given zero based index.
  *
  * @param head  Pointer to a pointer to the head of the list.
  * @param node  Pointer to the node to insert.
  * @param index Zero based position to insert at.
  */
void SLLInsertAt(SLLNode **head, SLLNode *node, size_t index);

  /**
  * Removes the node at a given zero based index.
  *
  * Does not free any memory.
  *
  * @param head  Pointer to a pointer to the head of the list.
  * @param index Zero based position of the node to remove.
  */
void SLLDeleteAt(SLLNode **head, size_t index);

 /**
  * Iterates over the list, calling print_node for each node.
  *
  * The caller uses clinkd_container_of inside print_node to access the parent struct.
  *
  * @param head       Pointer to the head of the list.
  * @param print_node Function called for each node.
 */
void SLLNodes(SLLNode *head, void (*print_node)(SLLNode *));

 /**
  * Detaches all nodes from the list by setting head to NULL.
  *
  * Does NOT free any memory, the caller owns each parent struct and is
  * responsible for releasing them. This function only resets the list state.
  *
  * @param head Pointer to a pointer to the head of the list.
  */
void SLLClear(SLLNode **head);

 /**
  * Returns the number of nodes in the list.
  *
  * @param head Pointer to the head of the list.
  * @return Total number of nodes.
 */
size_t SLLCountNodes(SLLNode *head);
 
 /**
  * Reverses the list in place.
  *
  * @param head Pointer to a pointer to the head of the list.
  */
void SLLReverse(SLLNode **head);

 /**
  * Builds a new list containing only nodes for which the predicate returns true.
  *
  * The new list reuses the same nodes, no allocation is performed. Because of
  * this, each node can only belong to one list at a time after filtering. If
  * you need to keep the original list intact, do not use this function.
  *
  * @param head      Pointer to the head of the original list.
  * @param predicate Function that returns true for nodes to keep.
  * @return Pointer to the head of the filtered list, or NULL if empty.
  */
SLLNode *SLLFilter(SLLNode *head, bool (*predicate)(SLLNode *));

#ifdef __cplusplus
}
#endif

#endif
