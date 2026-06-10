// Copyright 2026 Anna
//
// Implementation of a singly linked list.
// The public interface and function documentation are in linked_list.h.

#include "../include/singly_linked_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../include/print_utils.h"

SLLItem* SLLCreate(void* data, size_t data_size) {
  SLLItem* node = (SLLItem*)calloc(1, sizeof(SLLItem));
  if (node == NULL) return NULL;

  if (data != NULL) {
    node->data = calloc(1, data_size);
    if (node->data == NULL) {
      free(node);
      return NULL;
    }
    memcpy(node->data, data, data_size);
  }

  node->data_size = data_size;
  return node;
}

void SLLAppend(SLLItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  SLLItem* new_node = SLLCreate(value, data_size);
  if (new_node == NULL) return;

  // if the list is empty, the new node is the head
  if (*head == NULL) {
    *head = new_node;
    return;
  }

  SLLItem* current_item = *head;
  while (current_item->next != NULL) {
    current_item = current_item->next;
  }

  current_item->next = new_node;
}

void SLLPropend(SLLItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  SLLItem* new_node = SLLCreate(value, data_size);
  if (new_node == NULL) return;

  new_node->next = *head;
  *head = new_node;
}

void SLLPopFront(SLLItem** head) {
  if (head == NULL) return;

  SLLItem* temp = *head;
  *head = (*head)->next;

  temp->data = NULL;
  temp->next = NULL;
  free(temp);
}

void SLLPopBack(SLLItem** head) {
  if (head == NULL) return;

  // list with a single node.
  if ((*head)->next == NULL) {
    (*head)->data = NULL;  // zero it before freeing
    free(*head);
    *head = NULL;
    return;
  }

  // list with multiple nodes.
  SLLItem* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  // use an auxiliary variable to reset it before the free event,
  //  same as PopFront.
  SLLItem* last = current->next;
  last->data = NULL;
  last->next = NULL;
  free(last);
  current->next = NULL;
}

SLLItem* SLLFind(SLLItem* head, void* value) {
  SLLItem* current = head;

  while (current != NULL) {
    if (memcmp(value, current->data, current->data_size) == 0) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

void SLLInsertAt(SLLItem** head, void* value, size_t index) {
  if (head == NULL) return;
  if (SLLCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  SLLItem* current = *head;
  SLLItem* new_node = SLLCreate(value, current->data_size);
  if (new_node == NULL) return;

  if (index == 0) {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  // traverses the list until the node with index - 1
  // and while current is different from NULL
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) {
    free(new_node);  // index outside the limit
    return;
  }

  new_node->next = current->next;
  current->next = new_node;
}

void SLLDeleteAt(SLLItem** head, size_t index) {
  if (head == NULL) return;

  SLLItem* to_free;

  if (index == 0) {
    to_free = *head;
    (*head) = (*head)->next;  // advances the head before releasing the node
    free(to_free);            // free the old node
    return;
  }

  SLLItem* current = *head;
  // traverse to the node with the passed index
  for (size_t i = 0; i < index - 1 && current != NULL; i++) {
    current = current->next;
  }

  if (current->next == NULL) return;  // index outside the likit

  to_free = current->next;
  current->next = to_free->next;
  free(to_free);
}

void SLLNodes(SLLItem* head, void (*PrintData)(void*)) {
  if (PrintData == NULL) return;

  SLLItem* current_item = head;
  while (current_item != NULL) {
    PrintData(current_item->data);
    if (current_item->next != NULL) {
      printf(" --> ");
    }
    current_item = current_item->next;
  }
  printf(" --> NULL\n");
}

void SLLFree(SLLItem** head) {
  if (head == NULL) return;

  SLLItem* temp;
  while (*head != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }

  *head = NULL;
}

size_t SLLCountNodes(SLLItem* head) {
  size_t count = 0;
  SLLItem* current = head;

  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}

void SLLReverse(SLLItem** head) {
  SLLItem* current = *head;
  SLLItem* previous = NULL;
  SLLItem* next = NULL;

  // swap the values in the list
  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  *head = previous;
}

SinglyLinkedList* SLLFilter(SLLItem* head, bool (*FilterFunction)(void*)) {
  if (head == NULL) return NULL;

  SinglyLinkedList* new_list = NULL;
  SLLItem* current = head;

  while (current != NULL) {
    // for each node data that FilterFunction returned true,
    // append it on the new list
    if (FilterFunction(current->data)) {
      SLLAppend(&new_list, current->data, current->data_size);
    }

    current = current->next;
  }

  return new_list;
}

SLLItem* SLLMap(SLLItem* head, void* (*MapFunction)(void*)) {
  if (head == NULL) return NULL;

  SinglyLinkedList* new_list = NULL;
  SLLItem* current = head;

  while (current != NULL) {
    // mapped_data: the result of MapFunction in current->data
    void* mapped_data = MapFunction(current->data);

    // add the new data to the new list
    SLLAppend(&new_list, mapped_data, current->data_size);

    // release to make room for the next value 
    // (and also avoid memory leak)
    free(mapped_data);

    current = current->next;
  }

  return new_list;
}

void SLLEditNode(SLLItem** head, void* new_value, size_t index) {
  if (head == NULL) return;

  SLLItem* current = *head;
  // traverse to the node with the passed index
  for (size_t i = 0; i < index && current != NULL; i++) {
    current = current->next;
  }

  if (current == NULL) return; // index out of eange

  // assigns the value of new_value to current->data
  memcpy(current->data, new_value, current->data_size);
}
