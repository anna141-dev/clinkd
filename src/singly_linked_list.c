// Copyright 2026 Anna
//
// Implementation of a singly linked list.
// The public interface and function documentation are in linked_list.h.

#include "singly_linked_list.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "print_utils.h"

NodeItem* SLLCreateNode(void* data, size_t data_size) {
  NodeItem* node = (NodeItem*)calloc(1, sizeof(NodeItem));
  if (node == NULL) return NULL;

  /**
   * If the data is NULL, the new node starts empty.
   * Otherwise, if the data is not null, the new node data
   * is set to the data passed to the function
   */
  node->data = data;
  node->data_size = data_size;
    // node->next is already NULL because of calloc

  return node;
}

void SLLAppend(NodeItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  NodeItem* new_node = SLLCreateNode(value, data_size);
  if (new_node == NULL) return;

  // irck f the list is empty, the new node is the head
  if (*head == NULL) {
    *head = new_node;
    return;
  }

  NodeItem* current_item = *head;
  while (current_item->next != NULL) {
    current_item = current_item->next;
  }

  current_item->next = new_node;
}

void SLLPropend(NodeItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  NodeItem* new_node = SLLCreateNode(value, data_size);
  if (new_node == NULL) return;

  new_node->next = *head;
  *head = new_node;
}

void SLLPopFront(NodeItem** head) {
  if (head == NULL) return;

  NodeItem* temp = *head;
  *head = (*head)->next;

  temp->data = NULL;
  temp->next = NULL;
  free(temp);
}

void SLLPopBack(NodeItem** head) {
  if (head == NULL) return;

  // list with a single node.
  if ((*head)->next == NULL) {
    (*head)->data = NULL;  // zero it before freeing
    free(*head);
    *head = NULL;
    return;
  }

  // list with multiple nodes.
  NodeItem* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  
  //use an auxiliary variable to reset it before the free event,
	// same as PopFront.
  NodeItem* last = current->next;
  last->data = NULL;
  last->next = NULL;
  free(last);
  current->next = NULL;
}

NodeItem* SLLFind(NodeItem* head, void* value) {
  NodeItem* current = head;

  while (current != NULL) {
    if (memcmp(value, current->data, current->data_size) == 0) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

void SLLInsertAt(NodeItem** head, void* value, size_t index) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  NodeItem* current = *head;
  NodeItem* new_node = SLLCreateNode(value, current->data_size);
  if (new_node == NULL) return;

  if (index == 0) {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) {
    free(new_node); // index outside the limit
    return;
  }

  new_node->next = current->next;
  current->next = new_node;
}

void SLLDeleteAt(NodeItem** head, size_t index) {
  if (head == NULL) return;

  NodeItem* to_free;

  if (index == 0) {
    to_free = *head;
    (*head) = (*head)->next;
    free(to_free); // free the old node
    return;
  }

  NodeItem* current = *head;
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current->next == NULL) return; // index outside the likit

  to_free = current->next;
  current->next = to_free->next;
  free(to_free);
}

void SLLNodes(NodeItem* head, void (*print_data)(void*)) {
  if (print_data == NULL) return;

  NodeItem* current_item = head;
  while (current_item != NULL) {
    print_data(current_item->data);
    if (current_item->next != NULL) {
      printf(" --> ");
    }
    current_item = current_item->next;
  }
  printf(" --> NULL\n");
}

void SLLFree(NodeItem** head) {
  if (head == NULL) return;

  NodeItem* temp;
  while (*head != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }

  *head = NULL;
}

size_t SLLCountNodes(NodeItem* head) {
  size_t count = 0;
  NodeItem* current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}

void SLLReverse(NodeItem** head) {
  NodeItem* current = *head;
  NodeItem* previous = NULL;
  NodeItem* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  *head = previous;
}
