#include "onegin.h"

struct text maketext(str *content, size_t nLine) {//работает как часы
    struct text newText = { NULL, 0 };

    newText.content = content;
    newText.nLine = nLine;

    return newText;
}

struct text textFromFile(FILE *stream) {         //норм работает
    assert(stream);

    size_t  nLine = 0,
            i = 0;
    str content[MAXSIZE] = {};
    char *buffer = NULL;

    for(i = 0; i < MAXSIZE; i++)
        content[i] = NULL;

    buffer = (char*)calloc(MAXLINE + 1, sizeof(char));

    for(i = 0; fgets(buffer, MAXLINE, stream) != NULL; i++) {
        nLine++;

        content[i] = (char*)calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(content[i], buffer);
    }

    printf("%d", nLine);

    return maketext(content, nLine);
}

void sortFromStart(struct text sortableText) {
    assert(sortableText.content);
    assert(appendableText.nLine != 0);

    qsort(sortableText.content, sortableText.nLine, sizeof(char *), (int(*) (const void *, const void *)) strcmp);
}

void sortFromEnd(struct text sortableText) {
    assert(sortableText.content);
    assert(appendableText.nLine != 0);

    qsort(sortableText.content, sortableText.nLine, sizeof(char *), (int(*) (const void *, const void *)) strcmp);
}

void appendText(struct text appendableText, FILE *stream) {
    assert(stream && appendableText.content);
    assert(appendableText.nLine != 0);

    size_t i = 0;

    for(i = 0; i < appendableText.nLine; i++) {
        fputs(appendableText.content[i], stream);
    }

    fputs("\n", stream);
}
