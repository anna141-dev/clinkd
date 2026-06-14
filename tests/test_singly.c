// Singly Linked List Tests
// Author: Anna

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "singly_linked_list.h"
#include "test_helpers.h"

// The user defines the struct. SLLNode is necessary.
typedef struct {
  int value;
  SLLNode node;
} MyItem;

// Wraps an int value in a stack-allocated MyItem and returns its embedded node.
// Caller must ensure the MyItem outlives its use in the list.
static SLLNode* MakeNode(MyItem* item, int value) {
  item->value = value;
  item->node.next = NULL;
  return &item->node;
}

static void PrintItem(SLLNode* n) {
  MyItem* item = clinkd_container_of(n, MyItem, node);
  printf("%d", item->value);
}

static bool IsEven(SLLNode* n) {
  MyItem* item = clinkd_container_of(n, MyItem, node);
  return item->value % 2 == 0;
}

static bool IsOdd(SLLNode* n) {
  MyItem* item = clinkd_container_of(n, MyItem, node);
  return item->value % 2 != 0;
}

// Predicate for SLLFind: matches nodes whose value equals *(int *)ctx.
static bool MatchValue(SLLNode* n, void* ctx) {
  MyItem* item = clinkd_container_of(n, MyItem, node);
  return item->value == *(int*)ctx;
}

void run_singly_tests(void) {
  HEADER("SLL Tests");

  // Each value needs its own MyItem so the node stays valid in the list
  MyItem items[16];
  int item_idx = 0;

  SLLNode* head = NULL;

  // Empty list
  SECTION("Empty List");

  TEST(1, "Show empty list (expects no output)");
  SLLNodes(head, PrintItem);
  ASSERT(head == NULL, "List is NULL after initialization");
  ASSERT(SLLCountNodes(head) == 0, "Node count is 0");

  // Append individual values
  SECTION("Append Individual Values");

  TEST(2, "Appending 90, 12 and 73");
  SLLAppend(&head, MakeNode(&items[item_idx++], 90));
  SLLAppend(&head, MakeNode(&items[item_idx++], 12));
  SLLAppend(&head, MakeNode(&items[item_idx++], 73));
  ASSERT(SLLCountNodes(head) == 3, "Node count is 3 after 3 appends");

  TEST(3, "Listing nodes after individual appends");
  SLLNodes(head, PrintItem);

  // Append from array
  SECTION("Append From Array");

  TEST(4, "Appending 100, 200, 300, 400, 500 from array");
  int values[] = {100, 200, 300, 400, 500};
  int values_len = (int)(sizeof(values) / sizeof(values[0]));
  for (int i = 0; i < values_len; i++) {
    SLLAppend(&head, MakeNode(&items[item_idx++], values[i]));
  }
  ASSERT(SLLCountNodes(head) == 8, "Node count is 8 after array appends");

  TEST(5, "Listing nodes after array appends");
  SLLNodes(head, PrintItem);

  // Pop operations
  SECTION("Pop Operations");

  TEST(6, "Pop Back");
  SLLPopBack(&head);
  ASSERT(SLLCountNodes(head) == 7, "Node count is 7 after PopBack");

  TEST(7, "Pop Front");
  SLLPopFront(&head);
  ASSERT(SLLCountNodes(head) == 6, "Node count is 6 after PopFront");

  DEBUG("Listing nodes after pop operations:");
  SLLNodes(head, PrintItem);

  // Find
  SECTION("Searching a node by value");

  int target_existing = 100;
  int target_missing = 999;

  TEST(8, "Search for existing value (100)");
  ASSERT(SLLFind(head, MatchValue, &target_existing) != NULL, "Item found");

  TEST(9, "Search for non-existent value (999)");
  ASSERT(SLLFind(head, MatchValue, &target_missing) == NULL, "Item not found");

  // Prepend
  SECTION("Prepend Operation");

  TEST(10, "Prepending 42");
  SLLPrepend(&head, MakeNode(&items[item_idx++], 42));
  ASSERT(SLLCountNodes(head) == 7, "Node count is 7 after Prepend");

  DEBUG("Listing nodes after prepend:");
  SLLNodes(head, PrintItem);

  // Insert At
  SECTION("Insert At Operation");

  TEST(11, "Inserting 1111 at index 3");
  SLLInsertAt(&head, MakeNode(&items[item_idx++], 1111), 3);
  ASSERT(SLLCountNodes(head) == 8, "Node count is 8 after InsertAt");

  DEBUG("Listing nodes after InsertAt:");
  SLLNodes(head, PrintItem);

  // Delete At
  SECTION("Delete At Operations");

  TEST(12, "Deleting index 3");
  SLLDeleteAt(&head, 3);
  ASSERT(SLLCountNodes(head) == 7, "Node count is 7 after DeleteAt(3)");

  TEST(13, "Deleting index 0");
  SLLDeleteAt(&head, 0);
  ASSERT(SLLCountNodes(head) == 6, "Node count is 6 after DeleteAt(0)");

  DEBUG("Listing nodes after delete operations:");
  SLLNodes(head, PrintItem);

  // Reverse
  SECTION("Reverse Linked List");

  TEST(14, "Reversing the linked list");
  SLLReverse(&head);

  DEBUG("Listing nodes after reverse:");
  SLLNodes(head, PrintItem);

  // Filter
  //
  //  SLLFilter reuses the original nodes, so after filtering head is detached.
  //  We rebuild head from the items array whenever we need the original list.
  //
  SECTION("Filter Values");

  TEST(15, "Filter even values");
  SLLNode* even_list = SLLFilter(head, IsEven);
  DEBUG("Even nodes:");
  SLLNodes(even_list, PrintItem);

  // Rebuild head for the next filter (nodes were moved to even_list).
  head = NULL;
  for (int i = 0; i < item_idx; i++) {
    items[i].node.next = NULL;
    SLLAppend(&head, &items[i].node);
  }

  TEST(16, "Filter odd values");
  SLLNode* odd_list = SLLFilter(head, IsOdd);
  DEBUG("Odd nodes:");
  SLLNodes(odd_list, PrintItem);

  // Clear
  //
  // SLLClear only resets the head pointer, no memory is freed because the
  // library does not own the nodes. The MyItem array on the stack is released
  // automatically when main returns.
  //
  SECTION("Memory Cleanup");

  TEST(17, "Clearing all lists");
  SLLClear(&head);
  SLLClear(&even_list);
  SLLClear(&odd_list);
  ASSERT(head == NULL, "head is NULL after SLLClear");
  ASSERT(SLLCountNodes(head) == 0, "Node count is 0 after SLLClear");

  FOOTER("SLL Tests");
}
