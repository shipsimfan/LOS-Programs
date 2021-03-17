#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc > 3) {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    int longList = 0;
    int locationArg = -1;

    if (argc == 2) {
        if (argv[1][0] == '-') {
            if (argv[1][1] == 'l')
                longList = 1;
            else {
                fprintf(stderr, "Unknown flags %s\n", argv[1]);
                return 1;
            }
        } else
            locationArg = 1;
    } else if (argc == 3) {
        if (argv[1][0] == '-') {
            if (argv[1][1] == 'l')
                longList = 1;
            else {
                fprintf(stderr, "Unknown flags %s\n", argv[1]);
                return 1;
            }

            locationArg = 2;
        } else if (argv[2][0] == '-') {
            if (argv[2][1] == 'l')
                longList = 1;
            else {
                fprintf(stderr, "Unknown flags %s\n", argv[1]);
                return 1;
            }

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

    if (longList) {
        for (unsigned long long i = 0; i < num; i++) {
            printf("\t%s", entries[i].name);
            if (entries[i].type == DIRENT_TYPE_FILE)
                printf(" (%lli KB)", entries[i].size / 1024);
            printf("\n");
        }
    } else {
        for (unsigned long long i = 0; i < num; i++)
            printf("%s\t\t", entries[i].name);

        printf("\n");
    }

    return 0;
}