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
  if (head == NULL || node == NULL) return;

  node->size = 0;
  node->prev = NULL;
  node->next = NULL;

  if (*head == NULL) {
    *head = node;
    (*head)->size = 1;
    return;
  }

  if ((*head)->size >= LINKED_LIST_MAX_NODES) return;

  DLLNode* current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  node->prev = current;
  current->next = node;
  (*head)->size++;
}
