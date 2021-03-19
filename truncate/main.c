#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <new size>\n", argv[0]);
        return 1;
    }

    long newSize = atol(argv[2]);

    FILE* file = fopen(argv[1], "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open %s\n", argv[1]);
        return 1;
    }

    if (truncate(file, newSize) != 0) {
        fprintf(stderr, "Failed to truncate %s\n", argv[1]);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}