*This project has been created as part of the 42 curriculum by fsalinas.*

# Get Next Line

## Description

**Get Next Line** is a C project that implements `get_next_line(int fd)`, a function that reads and returns one line at a time from a file descriptor. Each call returns a newly allocated string, including the trailing newline (`\n`) when one exists. At the end of the input, or on error, the function returns `NULL`.

The project focuses on low-level input/output, dynamic memory management, static variables, and handling data that may arrive in multiple reads.

### Features

- **Mandatory:** reads lines sequentially while retaining unfinished data between calls.
- **Bonus:** maintains a separate buffer for each file descriptor, allowing calls to be interleaved across multiple files.
- Handles empty files, empty lines, lines longer than `BUFFER_SIZE`, and a final line without `\n`.
- Uses a compile-time `BUFFER_SIZE` to control how many bytes are requested per `read()` call.

## Instructions

### Build

From the project root:

```sh
make          # Build get_next_line.a
make bonus    # Build get_next_line_bonus.a
make clean    # Remove object files
make fclean   # Remove generated libraries and object files
make re       # Rebuild the mandatory library
```

These static libraries contain the implementation, not an executable. To run it, link the relevant library with a test program that provides `main()` and calls `get_next_line()`.

Alternatively, compile the source files directly with your own test `main.c`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   main.c get_next_line.c get_next_line_utils.c -o gnl_test
./gnl_test
```

For the bonus version, replace the two implementation files with `get_next_line_bonus.c` and `get_next_line_utils_bonus.c`.

`BUFFER_SIZE` can be changed at compile time (for example, `1`, `5`, or `1000`). It determines the size of each read request, **not** the maximum length of a line.

### Function behavior

```c
char *get_next_line(int fd);
```

- Returns the next line as a dynamically allocated string; the caller must `free()` it.
- Includes `\n` when the line ends with a newline.
- Returns a final nonempty line even when the file ends without `\n`.
- Returns `NULL` when no data remains or an error prevents completion.

## Algorithm and Design Choices

The implementation uses **buffered reading with persistent leftover storage (a stash)** rather than reading one character at a time.

1. **Check the stash.** At the start of a call, previously read characters may already contain a complete line.
2. **Read in chunks.** While no newline is present, call `read(fd, buffer, BUFFER_SIZE)`, terminate the received bytes with `\0`, and append them to the stash. A return value of `0` means end-of-file; `-1` indicates an error.
3. **Extract one line.** Once a newline is found, or EOF is reached with characters remaining, allocate a new string containing only the next line. Include its newline if present.
4. **Keep the remainder.** Copy any characters after that newline into a new stash, then release the old stash. If nothing remains, set the stash to `NULL`.
5. **Return ownership.** Return the allocated line to the caller, who is responsible for freeing it. On allocation or read failures, release the relevant temporary memory and report failure with `NULL`.

**Why this approach?** Chunked reads avoid requesting a single byte at a time, while the stash preserves bytes already read beyond the next newline. This supports lines of arbitrary length without assuming that `BUFFER_SIZE` matches line boundaries. The mandatory version uses one static stash; the bonus version uses independent storage indexed by file descriptor to avoid mixing pending data from different inputs.

**Trade-off:** appending each chunk may require allocating and copying the growing stash again. This keeps the implementation straightforward, but can lead to quadratic copying work for very long lines when `BUFFER_SIZE` is small.

## Resources

- [Linux manual: `read(2)`](https://man7.org/linux/man-pages/man2/read.2.html) — file descriptors, read return values, and EOF.
- [Linux manual: `malloc(3)` and `free(3)`](https://man7.org/linux/man-pages/man3/malloc.3.html) — heap allocation and memory ownership.
- [GNU Make Manual](https://www.gnu.org/software/make/manual/make.html) — Makefile targets, dependencies, and build rules.
- [cppreference: C language](https://en.cppreference.com/w/c/language.html) — pointers, arrays, and storage duration.
- Peer discussions and reviews at Codam — understanding edge cases and validating design decisions.

### AI Usage

AI was used as a **learning and review assistant**, not as a replacement for implementing the project. It helped clarify pointer indirection (`char *` vs. `char **`), static storage, EOF behavior, allocation and cleanup paths, debugging potential out-of-bounds access, refactoring to meet Norminette restrictions, and reviewing Makefile/header organization. The implementation and design decisions were developed and revised by **fsalinas**.
