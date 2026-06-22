//
// Copyright 2026 Anna
//
// Implementation of a doubly linked list.
// The public interface and function documentation are in doubly_linked_list.h.
//

#include "doubly_linked_list.h"

#include <stdio.h>
#include <stdbool.h>

#include "clinkd_common.h"

ClinkdStatus DLLAppend(DLLNode** head, DLLNode* node) {
  // reject null pointers, avoiding undefined behavior
  if (head == NULL || node == NULL) return CLINKD_ERROR;

  // initialize the isolated node (without neighbors and size)
  node->size = 0;
  node->prev = NULL;
  node->next = NULL;
  node->tail = NULL;

  // empty list: the node becomes the head of the list
  if (*head == NULL) {
    *head = node;
    (*head)->size = 1;
    (*head)-> tail = node;
    return CLINKD_OK;
  }

  // respects the maximum number of nodes defined by the lib
  if ((*head)->size >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  // chain the new node directly to the tail
  node->prev = (*head)->tail;
  (*head)->tail->next = node;
  (*head)->tail = node; // head updates its tail

  (*head)->size++;
  
  return CLINKD_OK;
}

ClinkdStatus DLLPrepend(DLLNode** head, DLLNode* node) {
  if (head == NULL || node == NULL) return CLINKD_ERROR;

  size_t current_size = (*head) != NULL ? (*head)->size + 1 : 0;

  // first case: empty list
  if (*head == NULL) {
    *head = node;
    (*head)->size = 1;
    return CLINKD_OK;
  }

  if (DLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  // second case: list with multiple nodes
  node->next = *head;
  *head = node;
  node->prev = NULL;

  // increase the node count in the list
  (*head)->size = current_size;

  return CLINKD_OK;
}

ClinkdStatus DLLPopFront(DLLNode** head) {
  if (head == NULL) return CLINKD_ERROR;

  size_t current_size = (*head) != NULL ? (*head)->size - 1: 0;

  *head = (*head)->next;

  if (*head != NULL) {
    (*head)->size = current_size;
  }

  return CLINKD_OK;
}

ClinkdStatus DLLPopBack(DLLNode** head) {
  if (head == NULL) return CLINKD_ERROR;

  size_t current_size = (*head) != NULL ? (*head)->size - 1: 0;

  // first case: list with a single node
  if ((*head)->next == NULL) {
    *head = NULL;
    return CLINKD_OK;
  }

  // second case: list with multiple nodes
  DLLNode* current = *head;

  // traverses to the last-to-last node
  while (current->next->next != NULL) {
    current = current->next;
  }

  current->next = NULL;
  current->prev = current;

  (*head)->size = current_size;

  return CLINKD_OK;
}

ClinkdStatus DLLInsertAt(DLLNode** head, DLLNode* node, size_t index) {
  if (head == NULL || node == NULL) return CLINKD_ERROR;

  // first case: index == 0
  if (index == 0) {
    size_t current_size = *head != NULL ? (*head)->size + 1 : 0;

    node->next = *head;
    node->prev = NULL;

    // updates the node counter
    (*head)->size = current_size + 1;

    return CLINKD_OK;
  }

  if (DLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  // traverses to the last-to-last node
  DLLNode* current = *head;
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) return CLINKD_OUT_OF_BOUNDS;

  node->next = current->next;
  current->next = node;
  current->next->prev = current;

  (*head)->size++;

  return CLINKD_OK;
}

ClinkdStatus DLLDeleteAt(DLLNode** head, size_t index) {
  if (head == NULL) return CLINKD_ERROR;

  if (index == 0) {
    size_t current_size = (*head) != NULL ? (*head)->size : 0;

    (*head) = (*head)->next;
    (*head)->prev = NULL;

    (*head)->size = current_size - 1;
  }

  if (DLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  // traverses to the last-to-last node
  DLLNode* current = *head;
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) return CLINKD_OUT_OF_BOUNDS;

  current->next = current->next->next;
  current->prev = current->prev->prev;

  (*head)->size--;

  return CLINKD_OK;
}

void DLLNodes(DLLNode* head, void(*print_node)(DLLNode*)) {
  if (print_node == NULL) return;

  DLLNode* current = head;
  while (current != NULL) {
    print_node(current);
    if (current->next != NULL) printf(" <-> ");
    current = current->next;
  }
  printf(" <-> NULL\n");
}

size_t DLLCountNodes(DLLNode* head) {
  if (head == NULL) return 0;

  return head->size;
}

ClinkdStatus DLLClear(DLLNode** head) {
  if (head == NULL) return CLINKD_ERROR;

  *head = NULL;

  return CLINKD_OK;
}
