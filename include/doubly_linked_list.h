#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/** Template struct of a double linked list */
typedef struct DLLNode {
  struct DLLNode* prev; // Previous Node
  struct DLLNode* next; // Next Node
} DLLNode;

#ifdef __cplusplus
}
#endif

#endif
