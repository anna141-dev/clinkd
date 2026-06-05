# clinkd

> A lightweight C library for working with linked lists.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](./LICENSE.md)
[![C Standard](https://img.shields.io/badge/C-C99%2FC11-orange.svg)]()
[![Status](https://img.shields.io/badge/status-in%20development-yellow.svg)]()

## Overview

**clinkd** is a C library that provides a clean API for creating and manipulating linked lists. It aims to reduce boilerplate and make working with linked lists in C as straightforward as possible, without sacrificing control or performanc

this was initially intended to be a study project, but I decided to scale it up

> **Note:** this library is under active development. APIs may change

## Getting Started

### Requirements

- GCC or Clang
- C99 or later
- Make

### Building

```bash
git clone https://github.com/anna141-dev/clinkd.git
cd clinkd

make # (compile)

## or...
make lib # (to use as a lib)

## or...
make run # (to use the pre-defined tests on src/main.c)
```

## Documentation

Documentation is generated with [Doxygen](https://www.doxygen.nl/index.html).

```bash
doxygen Doxyfile
```

Output will be in docs/. Open docs/index.html in your browser.

### Including in your project

On the same directory you cloned clinkd and executed `make lib`,  make your program.

Example:

```
clinkd/
└── ...

your-project/
└── ...
```

Don't forget to include linked_lists.h:

```c
#include "linked_lists.h"
```

Link against the compiled library:

```bash
gcc -Wall -Wextra -Iinclude -I ../clinkd/include your_program -o your_program -L../clinkd/output -lclinkd
```

## Usage

```c
#include "linked_list.h"

NodeItem* node = NULL;
LinkedListNodes(node, print_int);

int value_to_append_1 = 90;
int value_to_append_2 = 12;
int value_to_append_3 = 73;

LinkedListAppend(&node, &value_to_append_1);
LinkedListAppend(&node, &value_to_append_2);
LinkedListAppend(&node, &value_to_append_3);

LinkedListNodes(node, print_int);

free(node);
```

## API Reference

| Function | Description |
|---|---|
| `LinkedListCreateNode(data)` | Creates a new node  |
| `LinkedListAppend(list, data)` | Appends a node to the end of the list |
| `LinkedListPropend(list, data)` | Prepends a node to the beginning of the list |
| `LinkedListPopFront(list)` | Removes the last node |
| `LinkedListPopBack(list)` | Removes the first node |
| `LinkedListFind(list)` | Finds a node by value |
| `LinkedListInsertAt(list, index)` | Inserts a value at a given index |
| `LinkedListNodes(list)` | List all nodes on the list |
| `LinkedListCountNodes(list)` | Count the total of nodes on the list |

## Project Structure

```
clinkd/
├── src/
│   ├── main.c
│   ├── linked_list.c
│   └── print_utils.c
├── include/
│   ├── linked_list.h
│   └── print_utils.h
├── output/
│   └── clinkd (after running make)
├── Makefile
├── LICENSE.md
└── README.md
```

## Contributing

Contributions are welcome. Feel free to open issues or pull requests.
Please follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) (even though it's c) for all contributions.

## License

This project is licensed under the [MIT License](./LICENSE.md).
