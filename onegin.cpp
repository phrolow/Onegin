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

struct text textFromFile(const char *path) {
    assert(path);

    FILE *fp = NULL;
    size_t  currentLine = 0,
            i = 0,
            iLine = 0,
            nChar = 0,
            nLine = 0,
            maxLine = 0;
    char **ptrs = NULL;
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

void sortText(struct text sortableText, int(*comp) (const char *, const char*)) {
    assert(sortableText.ptrs);
    assert(sortableText.nLine > 1);

    size_t i = 0,
           j = 0;
    char* temp = NULL;

    for (i = 0; i < sortableText.nLine - 1; i++)
    {
        for (j = 0; j < sortableText.nLine - i - 1; j++)
        {
            if (comp(sortableText.ptrs[j], sortableText.ptrs[j + 1]) > 0)
            {
                temp = sortableText.ptrs[j];
                sortableText.ptrs[j] = sortableText.ptrs[j + 1];
                sortableText.ptrs[j + 1] = temp;
            }
        }
    }
}

void appendText(struct text appendableText, const char *path) {
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

void appendContent(const char* content, const char *path) {
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

    while(*ptr1 != '\0' && *ptr1 != '\n' && !isalpha(*ptr1))
        ptr1++;

    while(*ptr1 != '\0' && *ptr1 != '\n' && !isalpha(*ptr2))
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

    const char *ptr1 = str1;
    const char *ptr2 = str2;

    while(*ptr1 != '\n' && *ptr1 != '\0')
        ptr1++;

    while(!isalpha(*ptr1) && ptr1 > str1)
        ptr1--;

    while(*ptr2 != '\n' && *ptr2 != '\0')
        ptr2++;

    while(!isalpha(*ptr2) && ptr2 > str2)
        ptr2--;

    while(*ptr1 == *ptr2 && --ptr1 > str1 && --ptr2 > str2)
        ;

    return *ptr1 - *ptr2;
}

size_t ostrlen(const char* str) {
    assert(str);

    size_t i = 0;

    while(str[i] != '\0' && str[i] != '\n')
        i++;

    return i - 1;
}

int checkfile(const char* path) {
    assert(path);

    char* ptr = NULL;

    ptr = strchr(path, '.');

    if(ptr) {
        ptr++;

        if(strcmp(ptr, "txt") || strcmp(ptr, "docx") || strcmp(ptr, "doc") || strcmp(ptr, "rtf") || strcmp(ptr, "odt"))
            return 1;
    }

    return 0;
}
