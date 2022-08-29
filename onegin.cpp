#include "onegin.h"

struct text maketext(str *content, size_t nLine) {//работает как часы
    struct text newText = { NULL, 0 };

    newText.content = content;
    newText.nLine = nLine;

    return newText;
}

struct text textFromFile(char *path) {         //норм работает
    assert(path);

    FILE *fp = NULL;
    size_t  nLine = 0,
            i = 0;
    //str content[MAXSIZE] = {};
    str *content = NULL;
    char *buffer = NULL;

    fp = fopen(path, "r");

    content = (str*)calloc(MAXSIZE + 1, sizeof(str));
    buffer = (char*)calloc(MAXLINE + 1, sizeof(char));

    for(i = 0; fgets(buffer, MAXLINE, fp) != NULL; i++) {
        nLine++;

        content[i] = (char*)calloc(strlen(buffer) + 1, sizeof(char));

        strcpy(content[i], buffer);
    }

    fclose(fp);

    return maketext(content, nLine);
}

void sortFromStart(struct text sortableText) {
    assert(sortableText.content);
    assert(sortableText.nLine != 0);

    size_t i = 0,
           j = 0;

    qsort(sortableText.content, sortableText.nLine, sizeof(char *), (int(*) (const void *, const void *)) compStart);
}

void sortFromEnd(struct text sortableText) {
    assert(sortableText.content);
    assert(sortableText.nLine != 0);

    qsort(sortableText.content, sortableText.nLine, sizeof(char *), (int(*) (const void *, const void *)) compEnd);
}

void appendText(struct text appendableText, char *path) {
    assert(path && appendableText.content);
    assert(appendableText.nLine != 0);

    FILE *fp = NULL;
    size_t i = 0;

    fp = fopen(path, "a");

    for(i = 0; i < appendableText.nLine; i++) {
        fputs(appendableText.content[i], fp);
    }

    fputs("\n", fp);

    fclose(fp);
}

int compStart(const char* str1, const char* str2) {
    int i = 0;

    while(str1[i] == str2[i]) {
        if(str1[i] == '\0')
            return 0;

        i++;
    }

    return str2[i] - str1[i];
}

int compEnd(const char* str1, const char* str2) {
    int i1 = 0,
        i2 = 0;

    i1 = strlen(str1) - 1;
    i2 = strlen(str2) - 1;

    while(str1[i1] == str2[i2] && i1 >= 0 && i2 >= 0) {
        i1--;
        i2--;
    }

    if(!(i1 + 1 || i2 + 1))
        return i2 - i1;

    return str2[i2] - str1[i1];
}
