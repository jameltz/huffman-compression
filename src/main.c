
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char input[1000];

    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);

    int length = strlen(input);

    int frequencies[256];
    count_frequencies((unsigned char *)input, length, frequencies);

    HuffmanNode *root = build_huffman_tree(frequencies);

    HuffmanCode codes[256];

    if (!generate_codes(root, codes)) {
        printf("Could not generate codes.\n");
        free_tree(root);
        return 1;
    }

    printf("\nCharacter frequencies and Huffman codes:\n");

    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            if (i == '\n') {
                printf("Newline");
            } else {
                printf("%c", i);
            }

            printf(" | Frequency: %d | Code: %s\n", frequencies[i], codes[i].bits);
        }
    }

    free_codes(codes);
    free_tree(root);

    return 0;
}
