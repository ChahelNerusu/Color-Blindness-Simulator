#include "io.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void read_uint8(FILE *fin, uint8_t *px) {
    int result = fgetc(fin);
    if (result == EOF) {
        fprintf(stderr, "Fatal Error\n");
        exit(1);
    }
    *px = (uint8_t) result;
}

void read_uint16(FILE *fin, uint16_t *px) {
    uint8_t bytes[2];
    read_uint8(fin, &bytes[0]);
    read_uint8(fin, &bytes[1]);
    *px = (uint16_t) (bytes[1] << 8) | bytes[0];
}

void read_uint32(FILE *fin, uint32_t *px) {
    uint16_t parts[2];
    read_uint16(fin, &parts[0]);
    read_uint16(fin, &parts[1]);
    *px = (uint32_t) (parts[1] << 16) | parts[0];
}

void write_uint8(FILE *fout, uint8_t x) {
    if (fputc(x, fout) == EOF) {
        fprintf(stderr, "Fatal Error\n");
        exit(1);
    }
}

void write_uint16(FILE *fout, uint16_t x) {
    write_uint8(fout, (uint8_t) (x & 0xFF));
    write_uint8(fout, (uint8_t) (x >> 8));
}

void write_uint32(FILE *fout, uint32_t x) {
    write_uint16(fout, (uint16_t) (x & 0xFFFF));
    write_uint16(fout, (uint16_t) (x >> 16));
}
