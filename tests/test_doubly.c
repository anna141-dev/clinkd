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

  /*Empty List*/
  SECTION("Empty List");

  TEST(1, "Show empty List (expect <-> NULL)");
  DLLNodes(head, PrintItem);
  ASSERT(head == NULL, "List is NULL after initialization");
  ASSERT(DLLCountNodes(head) == 0, "Node count is 0");

  /*Append Individual Values*/
  SECTION("Append individual values");

  TEST(2, "Appending 80, 90, 70");
  DLLAppend(&head, MakeNode(&items[item_idx++], 80));
  DLLAppend(&head, MakeNode(&items[item_idx++], 90));
  DLLAppend(&head, MakeNode(&items[item_idx++], 70));

  ASSERT(DLLCountNodes(head) == 3, "Node count is 3 after appending");

  TEST(3, "Printing Nodes after individual appends");
  DLLNodes(head, PrintItem);

  /*Prepend Values*/
  SECTION("Prepend individual values");

  TEST(4, "Prependint 100, 110, 120");
  DLLPrepend(&head, MakeNode(&items[item_idx++], 100));
  DLLPrepend(&head, MakeNode(&items[item_idx++], 110));
  DLLPrepend(&head, MakeNode(&items[item_idx++], 120));

  ASSERT(DLLCountNodes(head) == 6, "Node count is 6 after prepeding");

  TEST(5, "Printing Nodes after Individual prepends");
  DLLNodes(head, PrintItem);

  /*Pop Operations*/
  SECTION("Pop Operations");

  TEST(6, "Pop Front");
  DLLPopFront(&head);

  ASSERT(DLLCountNodes(head) == 5, "Node count is 5 after PopFront");

  TEST(7, "Printing Nodes after PopFront");
  DLLNodes(head, PrintItem);
}
