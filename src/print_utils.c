#include "print_utils.h"

#include <stdio.h>

void print_int(void* data) {
    printf("%d", *(int*)data);
}
