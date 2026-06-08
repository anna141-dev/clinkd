#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdint.h>
#include <stdlib.h>

/**
 * Defines the limit of nodes in the linked list.
 */
#define LINKED_LIST_MAX_NODES 100000U

typedef struct SinglyLinkedList {
  void* data;
  size_t data_size;
  struct SinglyLinkedList* next;
} SinglyLinkedList;

typedef struct SinglyLinkedList SSLItem;

/**
 * @brief Create a new node;
 * @param data The value to add on that node.
 * @param data_size The size of the value data type
 * @return Pointer to the head of the list or NULL if allocation fails.
 */
SSLItem* SLLCreateSinglyLinkedList(void* data, size_t data_size);

/**
 * @brief Adds a value at the end of the list.
 * @param head Pointer to a pointer to the head node.
 * @param value The value to add.
 * @param data_size The size of the value data type
 */
void SLLAppend(SSLItem** head, void* value, size_t data_size);

/**
 * Adds a value at the start of the list.
 * @param head Pointer to a pointer to the head node.
 * @param value The value to add.
 * @param data_size The size of the value data type
 */
void SLLPropend(SSLItem** head, void* value, size_t data_size);

/**
 * @brief Removes the first node from the list.
 * @param head Pointer to a pointer to the head of the list.
 */
void SLLPopFront(SSLItem** head);

/**
 * @brief Removes the last node from the list.
 * @param head Pointer to a pointer to the head of the list.
 */
void SLLPopBack(SSLItem** head);

/**
 * @brief Finds a node by value.
 * @param head Pointer to the head node.
 * @param value The value to search for.
 * @return Pointer to the matching node, or NULL if not found.
 */
SSLItem* SLLFind(SSLItem* head, void* value);

/**
 * @brief Inserts a value at a given index.
 * @param head Head of the list.
 * @param value The value to insert.
 * @param index Zero-based position to insert at.
 */
void SLLInsertAt(SSLItem** head, void* value, size_t index);

/**
 * @brief Deletes the node at a given index.
 * @param head Head of the list.
 * @param index Zero-based position of the node to delete.
 */
void SLLDeleteAt(SSLItem** head, size_t index);


/**
 * @brief List all nodes on the list.
 * @param head Head of the list.
 * @param print_data The function corresponding to the type of data to list
 */
void SLLNodes(SSLItem* head, void (*PrintData)(void*));

/**
 * @brief Deletes all nodes on the list, freeing memory up correctly
 *
 * Always use this after you finish operations with the list you are using, it's important to avoid memory leaks.
 * It automatically sets the pointer to the head to NULL, so you don't need to worry about doing it manually.
 *
 * @param head Pointer to the head of the list.
 */
void SLLFree(SSLItem** head);

/**
 * Returns the number of nodes in a linked list.
 *
 * @param head Pointer to the head of the list.
 * @return The total of notes on the list.
 */
size_t SLLCountNodes(SSLItem* head);

/**
 * Reverses a linked list.
 *
 * @param head Pointer to a pointer to the head of the list
 */

void SLLReverse(SSLItem** head);

#endif
