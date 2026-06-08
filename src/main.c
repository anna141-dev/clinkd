//  Copyright 2026 Anna
//
// Clinkd; A library to assist and facilitate the use of Linked Lists in C.
//
// Developer: Anna
// Github: github.com/anna141-dev/clinkd

#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"
#include "print_utils.h"

#define HEADER \
  "=-------------------------=\n" \
  "  CLINKD : TEST START                               \n" \
  "=-------------------------=\n"

#define FOOTER \
  "=-------------------------=\n" \
  "  CLINKD : TEST END                                 \n" \
  "=-------------------------=\n"

#define SECTION(name) \
  printf("\n-- %s --\n", name)

#define TEST(id, msg) \
  printf("\n[TEST %02d] %s\n", (id), (msg))

#define ASSERT(cond, msg)                                         \
  do {                                                            \
    if (cond) {                                                   \
      printf("  [ OK ] %s\n", (msg));                            \
    } else {                                                      \
      printf("  [FAIL] %s (line %d)\n", (msg), __LINE__);        \
    }                                                             \
  } while (0)

#define DEBUG(msg) printf("  [DEBUG] %s\n", (msg))

int main(void) {
  printf(HEADER);

  NodeItem* node = NULL;

  /*Empty list*/
  SECTION("Empty List");
  TEST(1, "Show empty list (expects no output)");
  SLLNodes(node, PrintInt);
  ASSERT(node == NULL, "List is NULL after initialization");
  ASSERT(SLLCountNodes(node) == 0, "Node count is 0");

  /*Append: individual values*/
  SECTION("Append Individual Values");
  TEST(2, "Appending 90, 12 and 73");
  int v1 = 90, v2 = 12, v3 = 73;
  SLLAppend(&node, &v1, sizeof(int));
  SLLAppend(&node, &v2, sizeof(int));
  SLLAppend(&node, &v3, sizeof(int));
  ASSERT(SLLCountNodes(node) == 3, "Node count is 3 after 3 appends");

  TEST(3, "Listing nodes after individual appends");
  SLLNodes(node, PrintInt);

  /*Append: from array*/
  SECTION("Append From Array");
  TEST(4, "Appending 100, 200, 300, 400, 500 from array");
  int values[] = {100, 200, 300, 400, 500};
  int values_len = (int)(sizeof(values) / sizeof(values[0]));
  for (int i = 0; i < values_len; i++) {
    SLLAppend(&node, &values[i], sizeof(int));
  }
  ASSERT(SLLCountNodes(node) == 8, "Node count is 8 after array appends");

  TEST(5, "Listing nodes after array appends");
  SLLNodes(node, PrintInt);

  /*Pop operations*/
  SECTION("Pop Operations");
  TEST(6, "Pop Back");
  SLLPopBack(&node);
  ASSERT(SLLCountNodes(node) == 7, "Node count is 7 after PopBack");

  TEST(7, "Pop Front");
  SLLPopFront(&node);
  ASSERT(SLLCountNodes(node) == 6, "Node count is 6 after PopFront");

  DEBUG("Listing nodes after pop operations:");
  SLLNodes(node, PrintInt);

  /*Search Operations*/
  int value_to_search_1 = 100;
  int value_to_search_2 = 999;

  SECTION("Searching a node by value");

  TEST(8, "Search for existing value");
  ASSERT(SLLFind(node, &value_to_search_1) != NULL, "Item Found");

  TEST(9, "Search for non-existent value");
  ASSERT(SLLFind(node, &value_to_search_2) == NULL, "Item Not Found");

  /*Propend Operation*/
  SECTION("Propend Operation");
  TEST(10, "Propend");
  int value_to_propend = 42;
  SLLPropend(&node, &value_to_propend, sizeof(int));
  ASSERT(SLLCountNodes(node) == 7, "Node count is 7 after Propend");

  DEBUG("Listing nodes after propend operations:");
  SLLNodes(node, PrintInt);

  /*Insert At*/
  SECTION("Insert At Operation");
  TEST(11, "Inserting 1111 at index 3.");
  int value_to_add_at = 1111;
  SLLInsertAt(&node, &value_to_add_at, 3);
  
  ASSERT(SLLCountNodes(node) == 8, "Node count is 8 after insert");

  DEBUG("Listing nodes after insert operations:");
  SLLNodes(node, PrintInt);

  /*Delete At*/
  SECTION("Delete At Operations");
  TEST(12, "Deleting index 3");
  SLLDeleteAt(&node, 3);

  ASSERT(SLLCountNodes(node) == 7, "Node count is 7 after delete");

  TEST(12, "Deleting index 0");
  SLLDeleteAt(&node, 0);

  ASSERT(SLLCountNodes(node) == 6, "Node count is 6 after delete");

  DEBUG("Listing nodes after delete operations:");
  SLLNodes(node, PrintInt);

  /*Reverse singly linked list*/
  SECTION("Reverse Linked List");
  TEST(13, "Reversing the linked list");

  SLLReverse(&node);

  DEBUG("Listing nodes after reverse:");
  SLLNodes(node, PrintInt);

  /*Free*/
  SECTION("Memory Cleanup");
  TEST(8, "Freeing all nodes");
  SLLFree(&node);
  ASSERT(node == NULL, "List is NULL after SLLFree");
  ASSERT(SLLCountNodes(node) == 0, "Node count is 0 after free");

  printf("\n");
  printf(FOOTER);

  return 0;
}
