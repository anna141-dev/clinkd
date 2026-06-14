#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdio.h>

#define HEADER(title)                                      \
  printf("=-------------------------=\n"                   \
         "  CLINKD : %s START                               \n" \
         "=-------------------------=\n", title)

#define FOOTER(title)                                      \
  printf("=-------------------------=\n"                   \
         "  CLINKD : %s END                                 \n" \
         "=-------------------------=\n", title)

#define SECTION(name) printf("\n-- %s --\n", name)
#define TEST(id, msg) printf("\n[TEST %02d] %s\n", (id), (msg))

#define ASSERT(cond, msg)                                 \
  do {                                                    \
    if (cond) {                                           \
      printf("  [ OK ] %s\n", (msg));                     \
      clinkd_pass_count++;                                \
    } else {                                              \
      printf("  [FAIL] %s (line %d)\n", (msg), __LINE__); \
      clinkd_fail_count++;                                \
    }                                                     \
  } while (0)

#define DEBUG(msg) printf("  [DEBUG] %s\n", (msg))

extern int clinkd_pass_count;
extern int clinkd_fail_count;

#endif
