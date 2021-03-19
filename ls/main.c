#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int longList = 0;
int showAll = 0;

void ParseFlags(const char* ptr) {
    while (*ptr) {
        switch (*ptr) {
        case 'l':
            longList = 1;
            break;

        case 'a':
            showAll = 1;
            break;

        default:
            fprintf(stderr, "Unknown flag %c\n", *ptr);
            exit(1);
        }

        ptr++;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 3) {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    int locationArg = -1;

    if (argc == 2) {
        if (argv[1][0] == '-')
            ParseFlags(argv[1] + 1);
        else
            locationArg = 1;
    } else if (argc == 3) {
        if (argv[1][0] == '-') {
            ParseFlags(argv[1] + 1);
            locationArg = 2;
        } else if (argv[2][0] == '-') {
            ParseFlags(argv[1] + 1);
            locationArg = 1;
        } else {
            fprintf(stderr, "Too many arguments!\n");
            return 1;
        }
    }

    if (locationArg != -1) {
        if (setcwd(argv[locationArg]) != 0) {
            fprintf(stderr, "Unable to locate %s\n", argv[locationArg]);
            return 1;
        }
    }

    unsigned long long num;
    dirent_t* entries = getdirent(&num);

    for (unsigned long long i = 0; i < num; i++) {
        if (!showAll && (entries[i].flags & DIRENT_FLAG_HIDDEN))
            continue;

        if (longList) {
            printf("\t%s", entries[i].name);
            if (entries[i].type == DIRENT_TYPE_FILE)
                printf(" (%lli KB)", entries[i].size / 1024);
        } else
            printf("%s\t\t", entries[i].name);

        printf("\n");
    }

    return 0;
}