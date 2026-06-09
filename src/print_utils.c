// Copyright 2026 Anna
//
// Implementation of auxiliary printing functions.
// The public interface and function documentation are in print_utils.h.

#include "print_utils.h"

#include <stdio.h>

void PrintInt(void* data) { printf("%d", *(int*)data); }

void PrintDouble(void* data) { printf("%f", *(double*)data); }

void PrintChar(void* data) { printf("%c", *(char*)data); }

void PrintString(void* data) { printf("%s", (char*)data); }
