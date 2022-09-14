#include "onegin.h"

struct text maketext(char *content, char **ptrs, size_t nChar, size_t nLine, size_t maxLine) {
    struct text newText = { NULL, NULL, 0 };

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

    content = (char*)calloc(sizeof(char), nChar + 1);
    fread(content, sizeof(char), nChar, fp);

    fclose(fp);

    for(i = 0; i < nChar; i++)
        if(content[i] == '\n')
            nLine++;

    nLine++;

    content[i + 1] = '\0';

    ptrs = (char**)calloc(sizeof(char*), nLine + 1);

    *(ptrs) = &(content[0]);
    iLine++;

    for(i = 0; i < nChar; i++) {
        currentLine++;

        if(content[i] == '\n') {
            *(ptrs + iLine) = &(content[i + 1]);

            iLine++;

            if(currentLine > maxLine)
                maxLine = currentLine;

            currentLine = 0;
        }
    }

    printf("New text!\n%u chars\n%u lines\n%u max line\n", nChar, nLine, maxLine);

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

    buff = (char*)calloc(appendableText.maxLine + 1, sizeof(char));

    fp = fopen(path, "a");

    for(i = 0; i < appendableText.nLine; i++) {
        for(j = 0; appendableText.ptrs[i][j] != '\n'; j++) {
            printf("%c", appendableText.ptrs[i][j]);
            buff[j] = appendableText.ptrs[i][j];
        }

        buff[j] = '\0';

        fputs(buff, fp);
    }

    fclose(fp);

    free(buff);
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
