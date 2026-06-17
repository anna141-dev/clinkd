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

void DLLAppend(DLLNode** head, DLLNode* node) {
  // reject null pointers, avoiding undefined behavior
  if (head == NULL || node == NULL) return;

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
    return;
  }

  // respects the maximum number of nodes defined by the lib
  if ((*head)->size >= LINKED_LIST_MAX_NODES) return;

  // traverse to the last node
  DLLNode* current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  // Chain the new node to the end and update the counter
  // in the head
  node->prev = current;
  current->next = node;
  (*head)->size++;
  (*head)->tail = node;
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
