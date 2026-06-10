#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdbool.h>
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

typedef struct SinglyLinkedList SLLItem;

/**
 * @brief Create a new node;
 * @param data The value to add on that node.
 * @param data_size The size of the value data type
 * @return Pointer to the head of the list or NULL if allocation fails.
 */
SLLItem* SLLCreate(void* data, size_t data_size);

/**
 * @brief Adds a value at the end of the list.
 * @param head Pointer to a pointer to the head node.
 * @param value The value to add.
 * @param data_size The size of the value data type
 */
void SLLAppend(SLLItem** head, void* value, size_t data_size);

/**
 * Adds a value at the start of the list.
 * @param head Pointer to a pointer to the head node.
 * @param value The value to add.
 * @param data_size The size of the value data type
 */
void SLLPropend(SLLItem** head, void* value, size_t data_size);

/**
 * @brief Removes the first node from the list.
 * @param head Pointer to a pointer to the head of the list.
 */
void SLLPopFront(SLLItem** head);

/**
 * @brief Removes the last node from the list.
 * @param head Pointer to a pointer to the head of the list.
 */
void SLLPopBack(SLLItem** head);

/**
 * @brief Finds a node by value.
 * @param head Pointer to the head node.
 * @param value The value to search for.
 * @return Pointer to the matching node, or NULL if not found.
 */
SLLItem* SLLFind(SLLItem* head, void* value);

/**
 * @brief Inserts a value at a given index.
 * @param head Head of the list.
 * @param value The value to insert.
 * @param index Zero-based position to insert at.
 */
void SLLInsertAt(SLLItem** head, void* value, size_t index);

/**
 * @brief Deletes the node at a given index.
 * @param head Head of the list.
 * @param index Zero-based position of the node to delete.
 */
void SLLDeleteAt(SLLItem** head, size_t index);

/**
 * @brief List all nodes on the list.
 * @param head Head of the list.
 * @param print_data The function corresponding to the type of data to list
 */
void SLLNodes(SLLItem* head, void (*PrintData)(void*));

/**
 * @brief Deletes all nodes on the list, freeing memory up correctly
 *
 * Always use this after you finish operations with the list you are using, it's
 * important to avoid memory leaks. It automatically sets the pointer to the
 * head to NULL, so you don't need to worry about doing it manually.
 *
 * @param head Pointer to the head of the list.
 */
void SLLFree(SLLItem** head);

/**
 * @brief Returns the number of nodes in a linked list.
 *
 * @param head Pointer to the head of the list.
 * @return The total of notes on the list.
 */
size_t SLLCountNodes(SLLItem* head);

/**
 * @brief Reverses a linked list.
 *
 * @param head Pointer to a pointer to the head of the list
 */

void SLLReverse(SLLItem** head);

/**
 * @brief Filters elements based on a function.
 *
 * Example, the function IsEven, the new list will
 * store only even values.
 * Your FilterFunction should cast the element's type.
 * See the example in /sr/main.c
 *
 * @param head Pointer to the head of the original list.
 * @param FilterFunction The function used to filter the elements. It must
 * return a boolean value.
 * @return The new list with filtered values.
 */
SinglyLinkedList* SLLFilter(SLLItem* head, bool (*FilterFunction)(void*));

/**
 * @brief Changes the list elements based on the result of the
 * passed function.
 *
 * Read the function DoubleValue on /src/main.c to see an example.
 *
 * @param head Pointer to a pointer to the head of the list.
 * @param MapFunction The function used to map the elements. Must return the same data type as the list element.
 * @return The new list with mapped values.
 */
SLLItem* SLLMap(SLLItem* head, void* (*MapFunction)(void*));

/**
 * @brief Modifies the element with the passed index.
 *
 * @param head Pointer to a pointer to the head of the list.
 * @param new_value The new value to be set on that node.
 * @param index The index to modify.
 */
void SLLEditNode(SLLItem** head, void* new_value, size_t index);

#endif
