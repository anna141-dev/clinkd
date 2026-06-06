/**
 * Library to assist and facilitate the use of Linked Lists in C.
 *
 * Developer: Anna
 * Github: github.com/anna141-dev
 * Repo: clinkd
 */

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
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
  LinkedListNodes(node, print_int);
  ASSERT(node == NULL, "List is NULL after initialization");
  ASSERT(LinkedListCountNodes(node) == 0, "Node count is 0");

  /*Append: individual values*/
  SECTION("Append Individual Values");
  TEST(2, "Appending 90, 12 and 73");
  int v1 = 90, v2 = 12, v3 = 73;
  LinkedListAppend(&node, &v1, sizeof(int));
  LinkedListAppend(&node, &v2, sizeof(int));
  LinkedListAppend(&node, &v3, sizeof(int));
  ASSERT(LinkedListCountNodes(node) == 3, "Node count is 3 after 3 appends");

  TEST(3, "Listing nodes after individual appends");
  LinkedListNodes(node, print_int);

  /*Append: from array*/
  SECTION("Append From Array");
  TEST(4, "Appending 100, 200, 300, 400, 500 from array");
  int values[] = {100, 200, 300, 400, 500};
  int values_len = (int)(sizeof(values) / sizeof(values[0]));
  for (int i = 0; i < values_len; i++) {
    LinkedListAppend(&node, &values[i], sizeof(int));
  }
  ASSERT(LinkedListCountNodes(node) == 8, "Node count is 8 after array appends");

  TEST(5, "Listing nodes after array appends");
  LinkedListNodes(node, print_int);

  /*Pop operations*/
  SECTION("Pop Operations");
  TEST(6, "Pop Back");
  LinkedListPopBack(&node);
  ASSERT(LinkedListCountNodes(node) == 7, "Node count is 7 after PopBack");

  TEST(7, "Pop Front");
  LinkedListPopFront(&node);
  ASSERT(LinkedListCountNodes(node) == 6, "Node count is 6 after PopFront");

  DEBUG("Listing nodes after pop operations:");
  LinkedListNodes(node, print_int);

  int value_to_search_1 = 100;
  int value_to_search_2 = 999;

  SECTION("Searching a node by value");

  TEST(8, "Search for existing value");
  ASSERT(LinkedListFind(node, &value_to_search_1) != NULL, "Item Found");

  TEST(9, "Search for non-existent value");
  ASSERT(LinkedListFind(node, &value_to_search_2) != NULL, "Item Found");

  /*Free*/
  SECTION("Memory Cleanup");
  TEST(8, "Freeing all nodes");
  LinkedListFree(&node);
  ASSERT(node == NULL, "List is NULL after LinkedListFree");
  ASSERT(LinkedListCountNodes(node) == 0, "Node count is 0 after free");

  printf("\n");
  printf(FOOTER);

  return 0;
}
