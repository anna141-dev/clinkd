/**
 * Library to assist and facilitate the use of Linked Lists in C.
 *
 * Developer: Anna
 * Github: github.com/anna141-dev
 * Repo: linked-lists-library-c
 */

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "print_utils.h"

#define HEADER "=-------------------------=\n" \
               " TESTING START \n" \
               "=-------------------------=\n"

#define DEBUG(msg) (printf("[DEBUG] %s\n", msg))

int main(void) {
  printf(HEADER);

  NodeItem* node = NULL;
  LinkedListNodes(node, print_int);

  int value_to_append_1 = 90;
  int value_to_append_2 = 12;
  int value_to_append_3 = 73;

  LinkedListAppend(&node, &value_to_append_1);
  LinkedListAppend(&node, &value_to_append_2);
  LinkedListAppend(&node, &value_to_append_3);

  LinkedListNodes(node, print_int);

  int values_to_append[] = { 100, 200, 300, 400, 500 };
  for (int i = 0; i < 5; i++) {
    LinkedListAppend(&node, &values_to_append[i]);
  }

  LinkedListNodes(node, print_int);

  LinkedListFree(&node);

  return 0;
}
