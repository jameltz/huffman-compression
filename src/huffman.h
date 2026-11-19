
#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct HuffmanNode {
    int frequency;
    unsigned char symbol;

    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

typedef struct {
    char *bits;
    int length;
} HuffmanCode;

// Count how often each character appears.
void count_frequencies(const unsigned char *input, int length,int frequencies[256]);

// Build the Huffman tree using the priority queue.
HuffmanNode *build_huffman_tree(int frequencies[256]);

// Generate a binary code for every character in the tree.
int generate_codes(HuffmanNode *root, HuffmanCode codes[256]);

// Free memory allocated for the tree and codes.
void free_tree(HuffmanNode *root);
void free_codes(HuffmanCode codes[256]);

#endif
