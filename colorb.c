#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "hi:o:"
#include "bmp.h"
#include "io.h"

#include <string.h>
int main(int argc, char **argv) {
    int opt;
    char *inputFileName = NULL;
    char *outputFileName = NULL;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': inputFileName = optarg; break;
        case 'o': outputFileName = optarg; break;
        case 'h':
            printf("Usage: tsp [options]\n\n");
            printf("-i infile    Specify the input file path containing the cities and edges\n");
            printf("             of a graph. If not specified, the default input should be\n");

            printf("             set as stdin.\n\n");

            printf("-o outfile   Specify the output file path to print to. If not specified,\n");
            printf("             the default output should be set as stdout.\n\n");

            printf("-d           Specifies the graph to be directed.\n\n");

            printf("-h           Prints out a help message describing the purpose of the\n");
            printf("             graph and the command-line options it accepts, exiting the\n");
            printf("             program afterwards.\n");
            exit(0);
            break;
        }
    }
    FILE *fin = fopen(inputFileName, "rb");
    BMP *image = bmp_create(fin);
    bmp_reduce_palette(image);
    FILE *fout = fopen(outputFileName, "wb");
    bmp_write(image, fout);
    fclose(fin);
    fclose(fout);
    bmp_free(&image);
    return 0;
}
