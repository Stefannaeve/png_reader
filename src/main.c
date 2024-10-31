#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "../include/main.h"

typedef struct _IHDR {
    uint32_t length;
    uint32_t chunkType;
    uint8_t *chunkData;
    uint32_t CRC;
} IHDR;

typedef struct _PNG_HEADER {
    uint8_t highBitSet;
    uint8_t PNG[3];
    uint16_t DOS;
    uint8_t idfk;
    uint8_t idkman;
    IHDR ihdr;
} PNG_HEADER;

int main(void) {
    char theChar;

    char *imagePosition = "../image/pixil-frame-0.png";
    FILE *png = fopen(imagePosition, "r");

    long size = fseek(png, 0, SEEK_END);
    printf("Size: %ld\n", size);
    fseek(png, 0, SEEK_SET);

    PNG_HEADER pngHeader;
    printf("Position: %ld\n", ftell(png));
    fread(&pngHeader.highBitSet, sizeof(uint8_t), 1, png);
    printf("Position: %ld\n", ftell(png));
    fread(&pngHeader.PNG, sizeof(uint8_t), 3, png);
    printf("Position: %d\n", ftell(png));
    uint8_t tempDos = 0;
    uint8_t tempDos2 = 0;
    pngHeader.DOS = 0;
    printf("Position: %d\n", ftell(png));
    fread(&tempDos2, sizeof(uint8_t), 1, png);
    fread(&tempDos, sizeof(uint8_t), 1, png);
    printf("Hallo2: %x\n", tempDos2);
    printf("Hallo: %x\n", tempDos);
    fread(&pngHeader.idfk, sizeof(uint8_t), 1, png);
    fread(&pngHeader.idkman, sizeof(uint8_t), 1, png);

    uint32_t temp;
    fread(&temp, sizeof(uint32_t), 1, png);
    temp = -16777216;

    // 1010 0010 0011 1100 0101 1010 0010 0011
    // 1100 0101 0000 0000 0000 0000 0000 0000
    // AND
    // 1111 1111 0000 0000 0000 0000 0000 0000

    printf("%u\n", temp);

    uint32_t swapped = ((temp<<24&0xff000000) |
                        (temp<<8&0xff0000) |
                        (temp>>8&0xff00) |
                        (temp>>24&0xff));

    printf("%u\n", swapped);


    pngHeader.ihdr.length = swapped;

    fread(&pngHeader.ihdr.chunkType, sizeof(uint32_t), 1, png);

    pngHeader.ihdr.chunkData = calloc(pngHeader.ihdr.length, sizeof(uint8_t));

    fread(&pngHeader.ihdr.chunkData, sizeof(uint8_t), pngHeader.ihdr.length, png);
    fread(&pngHeader.ihdr.CRC, sizeof(uint32_t), 1, png);

    printf("highBitSet: %d\n", pngHeader.highBitSet);
    printf("PNG: %c%c%c\n", pngHeader.PNG[0], pngHeader.PNG[1], pngHeader.PNG[2]);
    printf("DOS: %x\n", (pngHeader.DOS));
    printf("Idfk: %d\n", pngHeader.idfk);
    printf("Idfkman: %d\n", pngHeader.idkman);
    printf("Length of data: %d\n", pngHeader.ihdr.length);
    char newchar[5];
    newchar[0] = pngHeader.ihdr.chunkType << 24;
    newchar[1] = pngHeader.ihdr.chunkType << 16;
    newchar[2] = pngHeader.ihdr.chunkType << 8;
    newchar[3] = pngHeader.ihdr.chunkType << 0;
    newchar[4] = '\0';
    printf("ChunkType: %s\n", newchar);

    printf("Chunk data: %s", pngHeader.ihdr.chunkData);
    printf("CRC: %d", pngHeader.ihdr.CRC);

}
