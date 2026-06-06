#include "linked_list.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "print_utils.h"

#define LINKED_LIST_MAX_NODES 100000U

NodeItem* LinkedListCreateNode(void* data, size_t data_size) {
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

void LinkedListAppend(NodeItem** head, void* value, size_t data_size) {
  if (head == NULL) return;
  if (LinkedListCountNodes(*head) >= LINKED_LIST_MAX_NODES) return;

  NodeItem* new_node = LinkedListCreateNode(value, data_size);
  if (new_node == NULL) return;

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

void LinkedListPopFront(NodeItem** head) {
  if (head == NULL || *head == NULL) return;

  NodeItem* temp = *head;
  *head = (*head)->next;

  temp->data = NULL;
  temp->next = NULL;
  free(temp);
}

void LinkedListPopBack(NodeItem** head) {
  if (head == NULL || *head == NULL) return;

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

NodeItem* LinkedListFind(NodeItem* head, void* value) {
  NodeItem* current = head;

  while (current != NULL) {
    if (memcmp(value, current->data, current->data_size) == 0) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

NodeItem* LinkedListInsertAt(NodeItem* head, void* value, size_t index) {
  // TODO: Implement insertion by index.
  return NULL;
}

NodeItem* LinkedListDeleteAt(NodeItem* head, size_t index) {
  // TODO: Implement deletion by index.
  return NULL;
}

void LinkedListNodes(NodeItem* head, void (*print_data)(void*)) {
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

void LinkedListFree(NodeItem** head) {
  if (head == NULL) return;

  NodeItem* temp;
  while (*head != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }

  *head = NULL;
}

size_t LinkedListCountNodes(NodeItem* head) {
  size_t count = 0;
  NodeItem* current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}
