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
  if (head == NULL || node == NULL) return CLINKD_ERROR;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) 
      return CLINKD_FULL;

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
  if (head == NULL || node == NULL) return CLINKD_ERROR;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  size_t current_size = (*head != NULL) ? (*head)->size : 0;
  node->next = *head;
  *head = node;
  (*head)->size = current_size + 1; // Increases the node counter

  return CLINKD_OK;
}

ClinkdStatus SLLPopFront(SLLNode** head) {
  if (head == NULL || *head == NULL) return CLINKD_ERROR;

  // save the new total of nodes
  size_t new_size = (*head)->size;
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
  size_t new_size = (*head)->size - 1;

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
  (*head)->size = new_size;

  return CLINKD_OK;;
}

SLLNode* SLLFind(SLLNode* head, bool (*predicate)(SLLNode*, void*), void* ctx) {
  if (predicate == NULL) return NULL;

  SLLNode* current = head;
  while (current != NULL) {
    if (predicate(current, ctx)) return current;
    current = current->next;
  }

  return NULL;
}

ClinkdStatus SLLInsertAt(SLLNode** head, SLLNode* node, size_t index) {
  if (head == NULL || node == NULL) return CLINKD_ERROR;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES)
      return CLINKD_FULL;

  if (index == 0) {
    size_t current_size = (*head != NULL) ? (*head)->size : 0;
    node->next = *head;
    *head = node;
    (*head)->size = current_size + 1;
    return CLINKD_OK;
  }

  SLLNode* current = *head;
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) return CLINKD_OUT_OF_BOUNDS;

  node->next = current->next;
  current->next = node;

  (*head)->size++; // Increases the node counter

  return CLINKD_OK;
}

ClinkdStatus SLLDeleteAt(SLLNode** head, size_t index) {
  if (head == NULL || *head == NULL) return CLINKD_ERROR;

  if (index == 0) {
    *head = (*head)->next;
    return CLINKD_OK;
  }

  SLLNode* current = *head;
  for (size_t i = 0; i < index - 1 && current->next != NULL; i++) {
    current = current->next;
  }

  if (current->next == NULL) return CLINKD_OUT_OF_BOUNDS;

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
  if (head == NULL) return CLINKD_ERROR;

  SLLNode* current = *head;
  SLLNode* previous = NULL;
  SLLNode* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  *head = previous;

  return CLINKD_OK;
}

SLLNode* SLLFilter(SLLNode* head, bool (*predicate)(SLLNode*)) {
  if (head == NULL || predicate == NULL) return NULL;

  SLLNode* new_head = NULL;
  SLLNode* new_tail = NULL;
  SLLNode* current = head;

  while (current != NULL) {
    SLLNode* next = current->next;

    if (predicate(current)) {
      current->next = NULL;

      if (new_head == NULL) {
        new_head = current;
        new_tail = current;
      } else {
        new_tail->next = current;
        new_tail = current;
      }
    }

    current = next;
  }

  return new_head;
}
