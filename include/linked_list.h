#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>

typedef struct Node {
  void* data;
  struct Node* next;
} Node;

typedef struct Node NodeItem;

/**
 * @brief Create a new node;
 * @param initial Pointer to an existing node, or NULL to start empty.
 * @return Pointer to the head of the list or NULL if allocation fails.
 */
NodeItem* LinkedListCreateNode(void* data);

/**
 * @brief Adds a value at the end of the list.
 * @param head Pointer to a pointer to the head node.
 * @param value The value to add.
 */
void LinkedListAppend(NodeItem** head, void* value);

/**
 * Adds a value at the start of the list.
 * @param head Pointer to a pointer to the head node.
 * @param The value to add.
 */
void LinkedListPropend(NodeItem** head, void* value);

/**
 * @brief Removes the last node from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the new last node, or NULL if the list is now empty.
 */
NodeItem* LinkedListPop(NodeItem* head);

/**
 * @brief Finds a node by value.
 * @param head Pointer to the head node.
 * @param value The value to search for.
 * @return Pointer to the matching node, or NULL if not found.
 */
NodeItem* LinkedListFind(NodeItem* head, void* value);

/**
 * @brief Inserts a value at a given index.
 * @param head Head of the list.
 * @param value The value to insert.
 * @param index Zero-based position to insert at.
 * @return Pointer to the newly inserted node.
 */
NodeItem* LinkedListInsertAt(NodeItem* head, void* value, uint32_t index);

/**
 * @brief Deletes the node at a given index.
 * @param head Head of the list.
 * @param index Zero-based position of the node to delete.
 * @return Pointer to the node that replaced the deleted one, or NULL.
 */
NodeItem* LinkedListDeleteAt(NodeItem* head, int index);


/**
 * @brief List all nodes on the list.
 * @param head Head of the list.
 * @param print_data The function corresponding to the type of data to list
 */
void LinkedListNodes(NodeItem* head, void (*PrintData)(void*));

#endif
