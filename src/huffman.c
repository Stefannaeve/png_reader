#include <stdio.h>
#include <stdlib.h>

typedef struct _HUFFMAN_NODE {
    char character;
    int frequency;
    struct _HUFFMAN_NODE *left;
    struct _HUFFMAN_NODE *right;
} HUFFMAN_NODE;

typedef struct _HUFFMAN {
    int size;
    int capacity;
    HUFFMAN_NODE **array;
} HUFFMAN;

int huffman() {
    int sizeOfPng = 0;
    char currentChar = ' ';
    HUFFMAN huffman;
    huffman.array = calloc(256, sizeof(HUFFMAN_NODE));
    huffman.capacity = 256;
    huffman.size = 0;
    int array[256] = {0};

    char *imagePosition = "../image/test.txt";
    FILE *png = fopen(imagePosition, "rb");

    if (png == NULL) {
        printf("Couldnt open file\n");
        return 1;
    }

    fseek(png, 0, SEEK_END);
    sizeOfPng = ftell(png);
    fseek(png, 0, SEEK_SET);

    for (int i = 0; i < sizeOfPng; ++i) {
        currentChar = fgetc(png);
        if (currentChar == EOF) {
            printf("End of file");
            break;
        }
        array[(int) currentChar]++;
    }

    for (int i = 0; i < 256; ++i) {
        if (array[i] != 0) {
            HUFFMAN_NODE node;
            node.character = (char) array[i];
            node.frequency = i;

            huffman.array[huffman.size++] = &node;
        }
    }
    // for (int i = 0; i < 256; ++i) {
    //     printf("%c: %d\n", i, array[i]);
    // }
    // printf("\n");

    printf("Hello World: %d\n", sizeOfPng);
    free(huffman.array);
    return 0;
}

int binarySearch(HUFFMAN huffman, HUFFMAN_NODE node) {
    int beginning = 0;
    int end = huffman.size;
    int middle = (end-beginning)/2;

    if (huffman.array[huffman.size - 1]->frequency < node.frequency) {
        return end;
    }
    if (huffman.array[0]->character > node.character) {
        return beginning;
    }
    while(beginning < end) {
        if (huffman.array[middle]->frequency < node.frequency) {
            end = middle;
            middle = (end - beginning)/2;
            continue;
        }
        if (huffman.array[middle]->frequency > node.frequency) {
            beginning = middle;
            middle = (end - beginning)/2;
            continue;
        }
        if (huffman.array[middle]->frequency == node.frequency) {
            return middle;
        }
    }
    return end;
}
