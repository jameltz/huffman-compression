#include "huffman.h"
#include "priority_queue.h"

#include <stdlib.h>
#include <string.h>

// Create a new tree node.
static HuffmanNode *create_node(unsigned char symbol, int frequency, HuffmanNode *left, HuffmanNode *right) {
    HuffmanNode *node = malloc(sizeof(HuffmanNode));

    if (node == NULL) {
        return NULL;
    }

    node->symbol = symbol;
    node->frequency = frequency;
    node->left = left;
    node->right = right;

    return node;
}

// Count how often each character appears.
void count_frequencies(const unsigned char *input, int length,int frequencies[256]) {

    for (int i = 0; i < 256; i++) {
        frequencies[i] = 0;
    }

    for (int i = 0; i < length; i++) {
        frequencies[input[i]]++;
    }
}

// Free a Huffman tree recursively.
void free_tree(HuffmanNode *root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Remove and free every tree currently in the queue.
static void clear_queue(PriorityQueue *pq) {
    HuffmanNode *node;

    while ((node = pq_pop(pq)) != NULL) {
        free_tree(node);
    }
}

// Build the Huffman tree.
HuffmanNode *build_huffman_tree(int frequencies[256]) {

    PriorityQueue *pq = pq_create();

    if (pq == NULL) {
        return NULL;
    }

    // Create one leaf node for every character that appears.
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {

            HuffmanNode *node = create_node(
                (unsigned char)i, frequencies[i], NULL, NULL
            );

            if (node == NULL || !pq_push(pq, node)) {
                free_tree(node);
                clear_queue(pq);
                pq_destroy(pq);
                return NULL;
            }
        }
    }

    // Empty input produces no tree.
    if (pq_is_empty(pq)) {
        pq_destroy(pq);
        return NULL;
    }

    // Combine the two least frequent nodes until one tree remains.
    while (pq->size > 1) {

        HuffmanNode *left = pq_pop(pq);
        HuffmanNode *right = pq_pop(pq);

        HuffmanNode *parent = create_node(
            0,
            left->frequency + right->frequency,
            left,
            right
        );

        if (parent == NULL || !pq_push(pq, parent)) {
            free_tree(parent);

            if (parent == NULL) {
                free_tree(left);
                free_tree(right);
            }

            clear_queue(pq);
            pq_destroy(pq);
            return NULL;
        }
    }

    // The final remaining node is the root.
    HuffmanNode *root = pq_pop(pq);

    pq_destroy(pq);

    return root;
}

// Recursively generate codes by following the tree.
static int generate_codes_helper(HuffmanNode *root,HuffmanCode codes[256], char path[256], int depth) {

    if (root == NULL) {
        return 1;
    }

    // A leaf represents an actual character.
    if (root->left == NULL && root->right == NULL) {

        int length = depth;

        // Special case: input contains only one unique character.
        if (length == 0) {
            path[0] = '0';
            length = 1;
        }

        codes[root->symbol].bits = malloc(length + 1);

        if (codes[root->symbol].bits == NULL) {
            return 0;
        }

        path[length] = '\0';
        strcpy(codes[root->symbol].bits, path);
        codes[root->symbol].length = length;

        codes[root->symbol].length = length;

        return 1;
    }

    // Going left adds a 0.
    path[depth] = '0';

    if (!generate_codes_helper(root->left, codes, path, depth + 1)) {
        return 0;
    }

    // Going right adds a 1.
    path[depth] = '1';

    if (!generate_codes_helper(root->right, codes, path, depth + 1)) {
        return 0;
    }

    return 1;
}

// Generate all character codes.
int generate_codes(HuffmanNode *root, HuffmanCode codes[256]) {

    for (int i = 0; i < 256; i++) {
        codes[i].bits = NULL;
        codes[i].length = 0;
    }

    if (root == NULL) {
        return 1;
    }

    char path[256];

    if (!generate_codes_helper(root, codes, path, 0)) {
        free_codes(codes);
        return 0;
    }

    return 1;
}

// Free all generated codes.
void free_codes(HuffmanCode codes[256]) {

    for (int i = 0; i < 256; i++) {
        free(codes[i].bits);
        codes[i].bits = NULL;
        codes[i].length = 0;
    }
}
