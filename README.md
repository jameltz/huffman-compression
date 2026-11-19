# Huffman Compression

This is a C implementation of the Huffman coding algorithm, a data compression technique that assigns shorter binary codes to more frequently occurring characters and longer codes to less frequent characters.

## Project Structure

- `main.c`: Takes input from terminal or input file, coordinates the Huffman algorithm, and displays character frequencies and generated codes.
- `huffman.c`: Implements frequency counting, Huffman tree construction, code generation, and memory cleanup.
- `huffman.h`: Defines the Huffman node and code structures and declares the Huffman functions.
- `priority_queue.c`: Implements a min-heap priority queue used to efficiently build the Huffman tree.
- `priority_queue.h`: Defines the priority queue structure and declares its functions.
- `examples/`: Contains sample input files for testing.

## Current Features

- Reads input files in binary mode.
- Counts the frequency of each character.
- Builds a Huffman tree using a min-heap priority queue.
- Generates binary codes for each character.
- Handles empty files and files containing only one unique character.
- Frees dynamically allocated memory.

## Compilation and Usage

Compile the project from the root directory:

```bash
gcc -Wall -Wextra -std=c11 -g \
    src/main.c src/huffman.c src/priority_queue.c \
    -o huffman
```

Run using the default input file:

```bash
./huffman
```

Or specify a different input file:

```bash
./huffman examples/output.txt
```

The program currently displays each character's frequency and its corresponding Huffman code. File encoding and decoding are planned next steps.