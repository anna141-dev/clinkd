#include <stdio.h>

int clinkd_pass_count = 0;
int clinkd_fail_count = 0;

void run_singly_tests(void);
void run_doubly_tests(void);

int main(void) {
  printf("=———————————————————————————————————=\n");
  printf(" CLINKD TEST RUNNER\n");
  printf("=———————————————————————————————————=\n\n");

  run_singly_tests();

  printf("\n=———————————————————————————————————=\n");
  printf(" SUMMARY\n");
  printf("=———————————————————————————————————=\n");
  printf("  PASSED: %d\n", clinkd_pass_count);
  printf("  FAILED: %d\n", clinkd_fail_count);
  printf("=———————————————————————————————————=\n");

  return (clinkd_fail_count > 0) ? 1 : 0;
}
