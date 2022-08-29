#include "onegin.h"

int main(int argc, char *argv[]) {            //когда нибудь я запилю аргументы

    struct text originalText = { NULL, 0 },
                sortedFromStartText = { NULL, 0 },
                sortedFromEndText = { NULL, 0 };

    argv[1] = "file1.txt";
    argv[2] = "file2.txt";

    originalText = textFromFile(argv[1]);
    sortedFromStartText = textFromFile(argv[1]);
    sortedFromEndText = textFromFile(argv[1]);

    sortFromStart(sortedFromStartText);
    sortFromEnd(sortedFromEndText);

    appendText(sortedFromStartText, argv[2]);
    appendText(sortedFromEndText, argv[2]);
    appendText(originalText, argv[2]);

    printf("%d\n", compEnd("Aboba", "Abobus"));
    printf("%d\n", compEnd("Aboba", "Aboba"));
    printf("%d\n", compEnd("Aboba", "Abobaa"));

    return 0;
}
