#ifndef PNGREADER_MAIN_H
#define PNGREADER_MAIN_H

typedef struct _IHDR_DATA {
    uint32_t width;
    uint32_t height;
    uint8_t bitDepth;
    uint8_t colorType;
    uint8_t compressionMethod;
    uint8_t filterMethod;
    uint8_t interlaceMethod;
} IHDR_DATA;

typedef struct _IHDR_HEADER {
    uint32_t length;
    uint32_t chunkType;
    IHDR_DATA chunkData;
    uint32_t CRC;
} IHDR_HEADER;

typedef struct _PNG_HEADER {
    uint8_t highBitSet;
    uint8_t PNG[3];
    uint16_t DOS;
    uint8_t idfk;
    uint8_t idkman;
    IHDR_HEADER ihdr;
} PNG_HEADER;

#endif //PNGREADER_MAIN_H
