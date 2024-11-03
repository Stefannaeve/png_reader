#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "../include/main.h"

#include <sys/types.h>

#include "../include/SNLogger.h"

typedef enum _BIT_CHANGE {
    sixteen,
    thirtyTwo
} BIT_CHANGE;

void changeEndian(void *pointer, BIT_CHANGE bitChange);



int main(void) {
    char theChar;

    logDebug("Hei");

    char *imagePosition = "./image/pixil-frame-0.png";
    FILE *png = fopen(imagePosition, "rb");

    if (png == NULL) {
        printf("Couldnt open file\n");
        return 1;
    }

    fseek(png, 0, SEEK_END);
    fseek(png, 0, SEEK_SET);

    PNG_HEADER pngHeader;
    fread(&pngHeader.highBitSet, sizeof(uint8_t), 1, png);
    fread(&pngHeader.PNG, sizeof(uint8_t), 3, png);
    fread(&pngHeader.DOS, sizeof(uint16_t), 1, png);
    fread(&pngHeader.idfk, sizeof(uint8_t), 1, png);
    fread(&pngHeader.idkman, sizeof(uint8_t), 1, png);

    uint32_t temp;
    fread(&temp, sizeof(uint32_t), 1, png);

    changeEndian(&temp, thirtyTwo);

    printf("Swapped: %u\n", temp);

    pngHeader.ihdr.length = temp;

    fread(&pngHeader.ihdr.chunkType, sizeof(uint32_t), 1, png);

    fread(&pngHeader.ihdr.chunkData.width, sizeof(uint32_t), 1, png);
    changeEndian(&pngHeader.ihdr.chunkData.width, thirtyTwo);

    fread(&pngHeader.ihdr.chunkData.height, sizeof(uint32_t), 1, png);
    changeEndian(&pngHeader.ihdr.chunkData.height, thirtyTwo);

    fread(&pngHeader.ihdr.chunkData.bitDepth, sizeof(uint8_t), 1, png);
    fread(&pngHeader.ihdr.chunkData.colorType, sizeof(uint8_t), 1, png);
    fread(&pngHeader.ihdr.chunkData.compressionMethod, sizeof(uint8_t), 1, png);
    fread(&pngHeader.ihdr.chunkData.filterMethod, sizeof(uint8_t), 1, png);
    fread(&pngHeader.ihdr.chunkData.interlaceMethod, sizeof(uint8_t), 1, png);

    fread(&pngHeader.ihdr.CRC, sizeof(uint32_t), 1, png);
    changeEndian(&pngHeader.ihdr.CRC, thirtyTwo);

    printf("highBitSet: %d\n", pngHeader.highBitSet);
    printf("PNG: %c%c%c\n", pngHeader.PNG[0], pngHeader.PNG[1], pngHeader.PNG[2]);
    printf("DOS: %x\n", (pngHeader.DOS));
    printf("Idfk: %d\n", pngHeader.idfk);
    printf("Idfkman: %d\n", pngHeader.idkman);
    printf("Length of data: %d\n", pngHeader.ihdr.length);

    uint8_t chunkTypeOne = pngHeader.ihdr.chunkType >> 0;
    uint8_t chunkTypeTwo = pngHeader.ihdr.chunkType >> 8 & 0xff;
    uint8_t chunkTypeThree = pngHeader.ihdr.chunkType >> 16 & 0xff;
    uint8_t chunkTypeFour = pngHeader.ihdr.chunkType >> 24 & 0xff;

    printf("Chunk type: %c%c%c%c\n", chunkTypeOne, chunkTypeTwo, chunkTypeThree, chunkTypeFour);

    printf("\nChunk data:\n");
    printf("\tWidth: %d\n", pngHeader.ihdr.chunkData.width);
    printf("\tHeight: %d\n", pngHeader.ihdr.chunkData.height);
    printf("\tBit depth: %d\n", pngHeader.ihdr.chunkData.bitDepth);
    printf("\tColor type: %d\n", pngHeader.ihdr.chunkData.colorType);
    printf("\tCompression method: %d\n", pngHeader.ihdr.chunkData.compressionMethod);
    printf("\tFilter method: %d\n", pngHeader.ihdr.chunkData.filterMethod);
    printf("\tInterlace method: %d\n", pngHeader.ihdr.chunkData.interlaceMethod);

    printf("\nCRC: %08X\n", pngHeader.ihdr.CRC);
    fclose(png);
}

void changeEndian(void *pointer, BIT_CHANGE bitChange) {
    uint16_t *temp16;
    uint32_t *temp32;
    switch (bitChange) {
        case sixteen:
            temp16 = (uint16_t *) pointer;
            *temp16 = ((*temp16 << 8) |
                       (*temp16 >> 8));
            break;
        case thirtyTwo:
            temp32 = pointer;
            *temp32 = ((*temp32 << 24 & 0xff000000) |
                       (*temp32 << 8 & 0xff0000) |
                       (*temp32 >> 8 & 0xff00) |
                       (*temp32 >> 24 & 0xff));
            break;
        default:
            printf("Something went wrong\n");
            break;
    }
}
