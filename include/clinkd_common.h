#ifndef CLINKD_COMMON_H
#define CLINKD_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

 /**
  * Recovers a pointer to the parent struct from a pointer to one of its members.
  *
  * @param ptr    Pointer to the embedded member.
  * @param type   Type of the parent struct.
  * @param member Name of the member inside the parent struct.
  */
#define clinkd_container_of(ptr, type, member) \
  ((type *)((char *)(ptr)-offsetof(type, member)))

/** Defines the maximum number of nodes allowed in a list */
#define LINKED_LIST_MAX_NODES 100000U

#ifdef __cplusplus
}
#endif

#endif
