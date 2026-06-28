//
// Copyright 2026 Anna
//
// Implementation of a singly linked list.
// The public interface and function documentation are in singly_linked_list.h.
//

#include "singly_linked_list.h"

#include <stdbool.h>
#include <stdio.h>

#include "clinkd_common.h"

ClinkdStatus SLLAppend(SLLNode** head, SLLNode* node) {
  // rejects null pointers, avoiding undefined behavior
  if (head == NULL || node == NULL) return CLINKD_ERROR;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) 
      return CLINKD_FULL;

  // respects the node limit
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) 
      return CLINKD_FULL;

  // initialize list data
  node->size = 0;
  node->next = NULL; 

  // empty list
  if (*head == NULL) {
    *head = node;
    (*head)->size = 1;
    (*head)->tail = node; // tail points to itself
    return CLINKD_OK;
  }

  (*head)->tail->next = node;
  (*head)->tail = node; // updates tail
  (*head)->size++; // Increases the node counter

  return CLINKD_OK;
}

ClinkdStatus SLLPrepend(SLLNode** head, SLLNode* node) {
  // rejects null pointers, avoiding undefined behavior
  if (head == NULL || node == NULL) return CLINKD_ERROR;

  // respects the node limit
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  // if the head is not empty, the node counter
  // remains at the current one, otherwise it remains at 0
  size_t current_size = (*head != NULL) ? (*head)->size : 0;

  node->next = *head;
  *head = node;
  (*head)->size = current_size + 1; // Increases the node counter
  return CLINKD_OK;
}

ClinkdStatus SLLPopFront(SLLNode** head) {
  if (head == NULL || *head == NULL) return CLINKD_ERROR;

  // save the new total of nodes
  // if the head is not empty, the node counter
  // remains at the current one - 1, otherwise it remains at 0
  size_t new_size = (*head != NULL) ? (*head)->size : 0;

  *head = (*head)->next;

  // If the list is not empty, update the size 
  if (*head != NULL) {
    (*head)->size = new_size - 1;
  }

  return CLINKD_OK;
}

ClinkdStatus SLLPopBack(SLLNode** head) {
  if (head == NULL || *head == NULL) return CLINKD_ERROR;

  // save the new total of nodes
  // if the head is not empty, the node counter
  // remains at the current one - 1, otherwise it remains at 0
  size_t new_size = (*head != NULL) ? (*head)->size - 1 : 0;

  // List with a single node.
  if ((*head)->next == NULL) {
    *head = NULL;
    return CLINKD_OK;
  }

  // List with multiple nodes: traverse to the second-to-last.
  SLLNode* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  current->next = NULL;
  (*head)->size = new_size; // updates the total of nodes

  return CLINKD_OK;;
}

SLLNode* SLLFind(SLLNode* head, bool (*predicate)(SLLNode*, void*), void* ctx) {
  // rejects null pointers, avoiding undefined behavior
  if (predicate == NULL) return NULL;

  SLLNode* current = head;
  while (current != NULL) {
    if (predicate(current, ctx)) return current;
    current = current->next;
  }

  return NULL;
}

ClinkdStatus SLLInsertAt(SLLNode** head, SLLNode* node, size_t index) {
  // Reject null pointers; *head == NULL is valid (empty list),
  // but node == NULL cannot be inserted.
  if (head == NULL || node == NULL) return CLINKD_ERROR;

  // respects the node limit
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  if (index == 0) {
    // preserve the current size before reassigning *head
    size_t current_size = (*head != NULL) ? (*head)->size : 0;

    node->next = *head; // chain the current list after the new node
    *head = node; // new node becomes the head
    (*head)->size = current_size + 1;
    return CLINKD_OK;
  }

  SLLNode* current = *head;
  // advances to the node immediately before the target (index - 1).
  // the condition current->next != NULL avoids going beyond the end of the list
  // when index is greater than its length.
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  // current == NULL means that index points beyond the end of the list.
  // unlike SLLDeleteAt, here we do not check current->next, as
  // inserting after the last node (append) is a legitimate case
  if (current == NULL) return CLINKD_OUT_OF_BOUNDS;

  // snap the new node between current and current->next
  // if current->next is NULL (insertion at the end), node->next is NULL
  node->next = current->next;
  current->next = node;

  (*head)->size++; // Increases the node counter

  return CLINKD_OK;
}

ClinkdStatus SLLDeleteAt(SLLNode** head, size_t index) {
  // rejects null pointers, avoiding undefined behavior
  if (head == NULL || *head == NULL) return CLINKD_ERROR;

  if (index == 0) {
    // Preserve the current size before reassigning *head
    size_t current_size = (*head != NULL) ? (*head)->size : 0;

    // special case: redirects head to the second node without traversing the list
    *head = (*head)->next;

    (*head)->size = current_size - 1;
    return CLINKD_OK;
  }

  SLLNode* current = *head;
  // advances to the node immediately before the target (index - 1).
  // the condition current->next != NULL avoids going beyond the end of the list
  // when index is greater than its length.
  for (size_t i = 0; i < index - 1 && current->next != NULL; i++) {
    current = current->next;
  }

  // if current->next is NULL, the requested index is beyond the last node
  if (current->next == NULL) return CLINKD_OUT_OF_BOUNDS;

  // current->next becomes the node following the removed one.
  // the removed node is not freed here, its caller's responsibility
  current->next = current->next->next;

  (*head)->size--; // Decreases the node counter

  return CLINKD_OK;
}

void SLLNodes(SLLNode* head, void (*print_node)(SLLNode*)) {
  if (print_node == NULL) return;

  SLLNode* current = head;
  while (current != NULL) {
    print_node(current);
    if (current->next != NULL) printf(" --> ");
    current = current->next;
  }
  printf(" --> NULL\n");
}

ClinkdStatus SLLClear(SLLNode** head) {
  if (head == NULL) return CLINKD_ERROR;
  *head = NULL;

  return CLINKD_OK;
}

size_t SLLCountNodes(SLLNode* head) {
  if (head == NULL) return 0;

  return head->size;
}

ClinkdStatus SLLReverse(SLLNode** head) {
  // reject null pointers to the head pointer
  // *head == NULL is valid and represents an empty list
  // in this case, the loop does not execute and *head remains NULL
  if (head == NULL) return CLINKD_ERROR;

  SLLNode* current = *head;
  SLLNode* previous = NULL;
  SLLNode* next = NULL;

  // with each iteration, redirect current->next to the previous node,
  // advancing the three hands together. when entering the loop,
  // "previous" is the head of the already inverted sublist.
  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  // when exiting the loop, current == NULL and previous points to the last node
  // original, which is now the new head.
  *head = previous;

  return CLINKD_OK;
}

SLLNode* SLLFilter(SLLNode* head, bool (*predicate)(SLLNode*)) {
  // both arguments must be valid, without predicate there is no criterion
  // of filter, and a null list has nothing to filter
  if (head == NULL || predicate == NULL) return NULL;

  SLLNode* new_head = NULL;
  SLLNode* new_tail = NULL; // will be the new *head at the end of the inversion
  SLLNode* current = head; //save next before overwriting current->next

  while (current != NULL) {
    // save the next one before any redirection
    SLLNode* next = current->next;

    if (predicate(current)) {
      // isolates the node, ensures it doesn't drag the rest of the original list.
      // without this, new_tail->next could point to a deprecated node.
      current->next = NULL;

      if (new_head == NULL) {
        // first node approved we initialize
        // the tail and the head of the new list
        new_head = current;
        new_tail = current;
      } else {
        // chain at the end and advance the tail
        new_tail->next = current;
        new_tail = current;
      }
    }

    // deprecated nodes are simply ignored, the responsibility of
    // freeing memory stays with the caller, which still has original head

    current = next;
  }

  // returns NULL if no node passed the predicate (new_head was never set)
  return new_head;
}
