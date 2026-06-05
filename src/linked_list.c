#include "linked_list.h"

#include <stdlib.h>
#include <stdint.h>

NodeItem* LinkedListCreateNode(void* data) {
  NodeItem* node = (NodeItem*)malloc(sizeof(NodeItem));
  if (node == NULL) return NULL;

  /**
   * If the data is NULL, the new node starts empty.
   * Otherwise, if the data is not null, the new node data
   * is set to the data passed to the function
   */
  node->data = (data != NULL) ? data : NULL;
  node->next = NULL;

  return node;
}

void LinkedListAppend(NodeItem** head, void* value) {
  NodeItem* new_node = LinkedListCreateNode(value);

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
  if (*head == NULL) return;

  NodeItem* temp = *head;
  *head = (*head)->next;
  free(temp);
}

void LinkedListPopBack(NodeItem** head) {
  if (*head == NULL) return;

  // list with a single element
  if ((*head)->next == NULL) {
    free(*head);
    (*head)->next = NULL;
    return;
  }

  NodeItem* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  free(current->next);
  current->next = NULL;
}

NodeItem*LinkedListFind(NodeItem* head, void* value);

NodeItem* LinkedListInsertAt(NodeItem* head, void* value, uint32_t index);

NodeItem* LinkedListDeleteAt(NodeItem* head, int index);

void LinkedListNodes(NodeItem* head, void (*print_data)(void*)) {
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
  NodeItem* temp;

  while (*head != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }

  *head = NULL;
}

int LinkedListCountNodes(NodeItem* head) {
  int count = 0;
  NodeItem* current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}
