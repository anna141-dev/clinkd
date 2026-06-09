// Copyright 2026 Anna
//
// Implementation of a singly linked list.
// The public interface and function documentation are in linked_list.h.

#include "singly_linked_list.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "print_utils.h"

SSLItem* SLLCreateSinglyLinkedList(void* data, size_t data_size) {

  SSLItem* node = (SSLItem*)calloc(1, sizeof(SSLItem));
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

void SLLAppend(SSLItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  SSLItem* new_node = SLLCreateSinglyLinkedList(value, data_size);
  if (new_node == NULL) return;

  // irck f the list is empty, the new node is the head
  if (*head == NULL) {
    *head = new_node;
    return;
  }

  SSLItem* current_item = *head;
  while (current_item->next != NULL) {
    current_item = current_item->next;
  }

  current_item->next = new_node;
}

void SLLPropend(SSLItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  SSLItem* new_node = SLLCreateSinglyLinkedList(value, data_size);
  if (new_node == NULL) return;

  new_node->next = *head;
  *head = new_node;
}

void SLLPopFront(SSLItem** head) {
  if (head == NULL) return;

  SSLItem* temp = *head;
  *head = (*head)->next;

  temp->data = NULL;
  temp->next = NULL;
  free(temp);
}

void SLLPopBack(SSLItem** head) {
  if (head == NULL) return;

  // list with a single node.
  if ((*head)->next == NULL) {
    (*head)->data = NULL;  // zero it before freeing
    free(*head);
    *head = NULL;
    return;
  }

  // list with multiple nodes.
  SSLItem* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  
  //use an auxiliary variable to reset it before the free event,
	// same as PopFront.
  SSLItem* last = current->next;
  last->data = NULL;
  last->next = NULL;
  free(last);
  current->next = NULL;
}

SSLItem* SLLFind(SSLItem* head, void* value) {
  SSLItem* current = head;

  while (current != NULL) {
    if (memcmp(value, current->data, current->data_size) == 0) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

void SLLInsertAt(SSLItem** head, void* value, size_t index) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  SSLItem* current = *head;
  SSLItem* new_node = SLLCreateSinglyLinkedList(value, current->data_size);
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

void SLLDeleteAt(SSLItem** head, size_t index) {
  if (head == NULL) return;

  SSLItem* to_free;

  if (index == 0) {
    to_free = *head;
    (*head) = (*head)->next;
    free(to_free); // free the old node
    return;
  }

  SSLItem* current = *head;
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current->next == NULL) return; // index outside the likit

  to_free = current->next;
  current->next = to_free->next;
  free(to_free);
}

void SLLNodes(SSLItem* head, void (*PrintData)(void*)) {
  if (PrintData == NULL) return;

  SSLItem* current_item = head;
  while (current_item != NULL) {
    PrintData(current_item->data);
    if (current_item->next != NULL) {
      printf(" --> ");
    }
    current_item = current_item->next;
  }
  printf(" --> NULL\n");
}

void SLLFree(SSLItem** head) {
  if (head == NULL) return;

  SSLItem* temp;
  while (*head != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }

  *head = NULL;
}

size_t SLLCountNodes(SSLItem* head) {
  size_t count = 0;
  SSLItem* current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}

void SLLReverse(SSLItem** head) {
  SSLItem* current = *head;
  SSLItem* previous = NULL;
  SSLItem* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  *head = previous;
}

SinglyLinkedList* SLLFilter(SSLItem* head, bool (*FilterFunction)(void*)) {
  if (head == NULL) return NULL;

  SinglyLinkedList* NewList = NULL;
  SSLItem* current = head;

  while (current != NULL) {
    // for each node data that FilterFunction returned true,
    // append it on the new list
    if (FilterFunction(current->data)) {
      SLLAppend(&NewList, current->data, current->data_size);
    }

    current = current->next;
  }

  return NewList;
}
