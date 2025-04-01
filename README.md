# File Explorer using Linked File Allocation in C++

This project simulates a **file system** using fundamental data structures like **linked lists**, **queues**, and **arrays**, modeling how real-world operating systems manage file storage using **Linked File Allocation**. This system mimics storing and retrieving file data block-by-block from a simulated hard drive and with a simple terminal interface and no folder hierarchy (just one giant "flat" directory).

## Project Summary

**stupidOS** (the dummy operating system) needs a basic file system to manage file data using linked data blocks. Each file is split into blocks and the location of these blocks is tracked using a custom `LinkedList` class. Free memory blocks are managed by a `Queue`. Files are added, removed, or read through a `FileManager` class that handles all internal logic and memory simulation.

---

## Design and Architecture

### 1. **LinkedList**
- A generic singly linked list class to store data elements like integers (for file block locations) or custom objects (`File`).
- Supports sorted insertions to maintain file names in alphabetical order.

### 2. **Queue**
- A templated queue structure for managing **free memory blocks** (indexes of available space in the hard drive array).
- Implements typical `enqueue`, `dequeue`, `isEmpty`, and `front` operations.

### 3. **File Class**
- Represents a single file.
- Stores:
  - `Filename`: string
  - `indexList`: `LinkedList<int>` of indexes on the hard drive where characters are stored.
- Key methods:
  - `addBlock(index)`
  - `fileSize()`
  - `getFileBlocks()`

### 4. **FileManager Class**
- Simulates the file system and manages:
  - The `hardDrive` (a dynamic character array)
  - `blocksAvailable` (Queue of free block indexes)
  - `files` (LinkedList of `File` objects sorted by filename)
- Core functionalities:
  - `addFile(name, contents)`
  - `deleteFile(name)`
  - `readFile(name)`
  - `getFileNames()`
  - `findFileByName(name)` (helper function)

---

## How It All Fits Together

```
            +-------------------------------+
            |     FileManager               |
            +-------------------------------+
            | - hardDrive: char*            |
            | - blocksAvailable: Queue<int> |
            | - files: LinkedList<File>     |
            +-------------------------------+
            |            |                  ^
            |            v                  |
            |      +-------------------+    |
             +---> |   File            |----+
                   +-------------------+
                   | - Filename        |
                   | - indexList:      |
                   |  LinkedList<int>  |
                   +-------------------+

           Queue<int> stores free blocks
           LinkedList<File> keeps all files sorted
```

When a user adds a file, the `FileManager`:
1. Pulls free block indexes from `Queue`.
2. Stores characters at these indexes in `hardDrive`.
3. Creates a `File` object and adds it to `files`.

To read or delete a file:
- The linked list of block indexes is used to reconstruct or free the file data.

---

## Code Structure

```
.
├── LinkedList_srinivasgowda.hpp      # Custom Linked List implementation
├── Queue_srinivasgowda.hpp           # Custom Queue for free block tracking
├── FileSystem_srinivasgowda.h        # Class declarations for File and FileManager
├── FileSystem_srinivasgowda.cpp      # Method definitions for File and FileManager
├── stupidOS_srinivasgowda.exe        # Compiled executable (for Windows)
├── Makefile                          # Compiles all source files into 'stupidos'
```

---

## Running the Program

Compile the program using the provided `Makefile`:
```bash
make
```

Run with the following options:

- **Set hard drive size**
  ```bash
  ./stupidos -s 200
  ```

- **Load initial files from a file**
  ```bash
  ./stupidos -s 200 -f init.txt
  ```

### Menu Options:
```
1 – Show files on hard drive
2 – Add a file
3 – Delete a file
4 – Output a file
0 – Exit simulation
```

Each character of file content occupies one block on the simulated hard drive. The block indexes are maintained in a linked list for each file.

---

## Concepts Implemented

- **Data Abstraction**: Files are abstracted using classes and encapsulated block indexes.
- **Dynamic Memory Management**: Avoids contiguous storage constraints.
- **Linked File Allocation**: Mimics how many file systems manage non-contiguous data.
- **Templated Programming**: Reusable generic structures (`LinkedList`, `Queue`).

---


