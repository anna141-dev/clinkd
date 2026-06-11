//
// Copyright 2026 Anna
//
// Implementation of a singly linked list.
// The public interface and function documentation are in singly_linked_list.h.
//

#include "../include/singly_linked_list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void SLLAppend(SLLNode** head, SLLNode* node) {
  if (head == NULL || node == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  node->next = NULL;

  if (*head == NULL) {
    *head = node;
    return;
  }

  SLLNode* current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = node;
}

void SLLPrepend(SLLNode** head, SLLNode* node) {
  if (head == NULL || node == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  node->next = *head;
  *head = node;
}

void SLLPopFront(SLLNode** head) {
  if (head == NULL || *head == NULL) return;

  *head = (*head)->next;
}

void SLLPopBack(SLLNode** head) {
  if (head == NULL || *head == NULL) return;

  // List with a single node.
  if ((*head)->next == NULL) {
    *head = NULL;
    return;
  }

  // List with multiple nodes: traverse to the second-to-last.
  SLLNode* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  current->next = NULL;
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

void SLLInsertAt(SLLNode** head, SLLNode* node, size_t index) {
  if (head == NULL || node == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  if (index == 0) {
    node->next = *head;
    *head = node;
    return;
  }

  SLLNode* current = *head;
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) return;  // Index outside the list bounds.

  node->next = current->next;
  current->next = node;
}

void SLLDeleteAt(SLLNode** head, size_t index) {
  if (head == NULL || *head == NULL) return;

  if (index == 0) {
    *head = (*head)->next;
    return;
  }

  SLLNode* current = *head;
  for (size_t i = 0; i < index - 1 && current->next != NULL; i++) {
    current = current->next;
  }

  if (current->next == NULL) return;  // Index outside the list bounds.

  current->next = current->next->next;
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

void SLLClear(SLLNode** head) {
  if (head == NULL) return;
  *head = NULL;
}

size_t SLLCountNodes(SLLNode* head) {
  size_t count = 0;
  SLLNode* current = head;

  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}

void SLLReverse(SLLNode** head) {
  if (head == NULL) return;

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
