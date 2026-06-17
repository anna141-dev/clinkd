// Doubly Linker List Tests
// Author: Anna

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "doubly_linked_list.h"
#include "test_helpers.h"

// The user defines the struct. DLLNode is necessary.
typedef struct {
  int value;
  DLLNode node;
} MyItem;

// Wraps an int value in a stack-allocated MyItem and returns its embedded node.
// Caller must ensure the MyItem outlives its use in the list.
static DLLNode* MakeNode(MyItem* item, int value) {
  item->value = value;
  item->node.next = NULL;
  item->node.prev = NULL;
  return &item->node;
}

static void PrintItem(DLLNode* n) {
  MyItem* item = clinkd_container_of(n, MyItem, node);
  printf("%d", item->value);
}

void run_doubly_tests(void) {
  HEADER("DLL Tests");


  // Each value needs its own MyItem so the node stays valid in the list
  MyItem items[16];
  int item_idx = 0;

  DLLNode* head = NULL;
}
