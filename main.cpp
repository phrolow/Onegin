#include "onegin.h"

int main(int argc, char *argv[]) {
    struct text originalText = NULL,
                sortedFromStartText = NULL,
                sortedFromEndText = NULL;

    originalText = textFromFile(argv[1]);

    sortedFromStartText = sortFromStart(originalText);
    sortedFromEndText = sortFromEnd(originalText);

    appendText(sortedFromStartText, argv[2]);
    appendText(sortedFromEndText, argv[2]);
    appendText(originalText, argv[2]);

    return 0;
}
