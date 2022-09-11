#include "onegin.h"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Too few arguments!");
        exit(0);
    }

    struct text originalText = { NULL, 0 },
                sortedFromStartText = { NULL, 0 },
                sortedFromEndText = { NULL, 0 };

    originalText = textFromFile(argv[1]);
    sortedFromStartText = textFromFile(argv[1]);
    sortedFromEndText = textFromFile(argv[1]);

    //sortText(sortedFromStartText, strcmp);
    //sortText(sortedFromEndText, compEnd);

    appendText(sortedFromStartText, argv[2]);
    appendText(sortedFromEndText, argv[2]);
    appendText(originalText, argv[2]);

    return 0;
}
