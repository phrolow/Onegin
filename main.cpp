#include "onegin.h"

int main(int argc, char *argv[]) {            //когда нибудь я запилю аргументы
    struct text originalText = { NULL, 0 },
                sortedFromStartText = { NULL, 0 },
                sortedFromEndText = { NULL, 0 };

    FILE        *originalFile = NULL,
                *finalFile = NULL;

    argv[1] = "file1.txt";
    argv[2] = "file2.txt";

    originalFile   = fopen(argv[1], "r");
    finalFile      = fopen(argv[2], "a");

    originalText = textFromFile(originalFile);
    //sortedFromStartText = textFromFile(originalFile);
    //sortedFromEndText = textFromFile(originalFile);

    //sortFromStart(sortedFromStartText);
    //sortFromEnd(sortedFromEndText);

    //appendText(sortedFromStartText, finalFile);
    //appendText(sortedFromEndText, finalFile);
    appendText(originalText, finalFile);

    fclose(originalFile);
    fclose(finalFile);

    return 0;
}
