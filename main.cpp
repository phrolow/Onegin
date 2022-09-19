#include "onegin.h"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Too few arguments!");
        exit(0);
    }

    if(!(checkfile(argv[1]) && checkfile(argv[2]))) {
        printf("Invalid arguments");
        exit(0);
    }

    struct text originalText = { NULL, NULL, 0, 0, 0 },
                sortedFromStartText = { NULL, NULL, 0, 0, 0 },
                sortedFromEndText = { NULL, NULL, 0, 0, 0 };

    originalText = textFromFile(argv[1]);
    sortedFromStartText = textFromFile(argv[1]);
    sortedFromEndText = textFromFile(argv[1]);

    qsort(sortedFromStartText.ptrs, sortedFromStartText.nLine, sizeof(char*), (int (*)(const void*, const void*)) compStart);
    sortText(sortedFromEndText, compEnd);

    appendText(sortedFromStartText, argv[2]);
    appendText(sortedFromEndText, argv[2]);
    appendContent(originalText.content, argv[2]);

    return 0;
}
