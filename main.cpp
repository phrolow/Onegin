#include "onegin.h"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Too few arguments!");

        return -1;
    }

    if(!(checkfile(argv[1]) && checkfile(argv[2]))) {
        printf("Invalid arguments");

        return -1;
    }

    struct text txt = { NULL, NULL, 0, 0, 0 };

    txt = textFromFile(argv[1]);

    qsort(txt.ptrs, txt.nLine, sizeof(char*), (int (*)(const void*, const void*)) compStart);

    appendText(txt, argv[2]);

    sortText(txt, compEnd);

    appendText(txt, argv[2]);

    appendContent(txt.content, argv[2]);

    return 0;
}
