#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileEnd = ftell(file);
    char* buffer = malloc(fileEnd);
    rewind(file);

    if (fread(buffer, 1, fileEnd, file) < 0) {
        fprintf(stderr, "Error while reading file\n");
        fclose(file);
        return 1;
    }

    printf(buffer);

    fclose(file);

    return 0;
}