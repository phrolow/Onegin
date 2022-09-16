#include "onegin.h"

struct text maketext(char *content, char **ptrs, size_t nChar, size_t nLine, size_t maxLine) {
    struct text newText = { NULL, NULL, 0, 0, 0 };

    newText.content = content;
    newText.ptrs = ptrs;
    newText.nChar = nChar;
    newText.nLine = nLine;
    newText.maxLine = maxLine;

    return newText;
}

struct text textFromFile(char *path) {
    assert(path);

    FILE *fp = NULL;
    size_t  currentLine = 0,
            i = 0,
            iLine = 0,
            nChar = 0,
            nLine = 0,
            maxLine = 0;
    char **ptrs = NULL;         //wsl valgrind
    char *content = NULL;
    struct stat stats;

    fp = fopen(path, "r");

    fstat(fileno(fp), &stats);

    nChar = stats.st_size / sizeof(char);

    content = (char*)calloc(nChar + 1, sizeof(char));
    fread(content, sizeof(char), nChar, fp);

    fclose(fp);

    for(i = 0; i < nChar; i++)
        if(content[i] == '\n')
            nLine++;

    nLine++;

    content[i + 1] = '\0';

    ptrs = (char**)calloc(nLine + 1, sizeof(char*));

    ptrs[0] = &(content[0]);
    iLine++;

    for(i = 0; i < nChar; i++) {
        currentLine++;

        if(content[i] == '\n') {
            ptrs[iLine] = &(content[i + 1]);

            iLine++;

            if(currentLine > maxLine)
                maxLine = currentLine;

            currentLine = 0;
        }
    }

    return maketext(content, ptrs, nChar, nLine, maxLine);
}

/* void sortText(struct text sortableText, int(*comp) (const char *, const char*)) {      //хуевая сортировка потому что не учитывает пробелы
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
}      */

void appendText(struct text appendableText, char *path) {                          // \r
    assert(path && appendableText.content);
    assert(appendableText.nLine != 0);

    FILE *fp = NULL;
    size_t  i = 0,
            j = 0;
    char *buff = NULL;

    buff = (char*)calloc(appendableText.maxLine + 3, sizeof(char));

    fp = fopen(path, "a");

    for(i = 0; i < appendableText.nLine; i++) {
        for(j = 0; appendableText.ptrs[i][j] != '\n' && appendableText.ptrs[i][j] != '\0'; j++) {

            buff[j] = appendableText.ptrs[i][j];
        }

        buff[j] = '\n';
        buff[j + 1] = '\0';

        if(buff[0] != '\n')
            fputs(buff, fp);
    }

    fputs("\n", fp);

    fclose(fp);

    free(buff);
}

void appendContent(const char* content, char *path) {
    assert(content);

    FILE *fp = NULL;

    fp = fopen(path, "a");

    fputs(content, fp);

    fclose(fp);
}

int compStart(const char* str1, const char* str2) {
    assert(str1 && str2);
    assert(str1 != str2);

    const char *ptr1 = *(char**)str1;
    const char *ptr2 = *(char**)str2;

    char c1, c2;

    while(!isalpha(*ptr1) && *ptr1 != '\n' && *ptr1 != '\0')
        ptr1++;

    while(!isalpha(*ptr2) && *ptr1 != '\n' && *ptr1 != '\0')
        ptr2++;

    do {
        c1 = *(ptr1++);
        c2 = *(ptr2++);

        if(c1 == '\0' || c1 == '\n') {
            return c1 - c2;
        }
    }
    while(c1 == c2);

    return c1 - c2;
}

int compEnd(const char* str1, const char* str2) {
    assert(str1 && str2);
    assert(str1 != str2);

    const char *ptr1 = *(char**)str1;
    const char *ptr2 = *(char**)str2;

    int i1 = 0,
        i2 = 0;

    i1 = strlen(ptr1) - 1;
    i2 = strlen(ptr2) - 1;

    while(!isalpha(ptr1[i1]) && i1 > 0)
        i1--;

    while(!isalpha(ptr1[i2]) && i2 > 0)
        i2--;

    while(ptr1[i1] == ptr2[i2] && i1 > 0 && i2 > 0) {
        i1--;
        i2--;
    }

    return ptr1[i1] - ptr2[i2];
}
