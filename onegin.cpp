#include "onegin.h"

struct text maketext(str *content, size_t nLine) {
    struct text newText = { NULL, 0 };

    newText.content = content;
    newText.nLine = nLine;

    return newText;
}

struct text textFromFile(char *path) {
    assert(path);

    FILE *fp = NULL;
    size_t  nLine = 0,
            i = 0;
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

void sortText(struct text sortableText, int(*comp) (const char *, const char*)) {
    assert(sortableText.content);
    assert(sortableText.nLine != 0);

    size_t i = 0,
           j = 0;
    char* temp = NULL;

    for (i = 0; i < sortableText.nLine - 1; i++)
    {
        for (j = 0; j < sortableText.nLine - i - 1; j++)
        {
            if (comp(sortableText.content[j + 1], sortableText.content[j]) < 0)
            {
                temp = sortableText.content[j];
                sortableText.content[j] = sortableText.content[j + 1];
                sortableText.content[j + 1] = temp;
            }
        }
    }
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

int compEnd(const char* str1, const char* str2) {
    assert(str1 && str2);
    assert(str1 != str2);

    int i1 = 0,
        i2 = 0;

    i1 = strlen(str1) - 1;
    i2 = strlen(str2) - 1;

    while(str1[i1] == str2[i2] && i1 >= 0 && i2 >= 0) {
        i1--;
        i2--;
    }

    if(!(i1 + 1 || i2 + 1))
        return i1 - i2;

    return str1[i1] - str2[i2];
}
