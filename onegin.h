#ifndef ONEGIN
#define ONEGIN

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys\stat.h>

//! @brief  String type

struct text {
    char *content;
    char **ptrs;
    size_t  nChar,
            nLine,
            maxLine;
};

//! @brief  Text constructor
//!
//! @param  content         Array of strings
//!
//! @return New struct text

struct text maketext(char *content, char** ptrs, size_t nChar, size_t nLine, size_t maxLine);

//! @brief  Get text from file
//!
//! @param  stream          Input stream
//!
//! @return Struct text, which contains text from file

struct text textFromFile(const char *path);

//! @brief  Sort text
//!
//! @param  sortableText    Sortable text
//!
//! @param  comp            Function to compare for sort

void sortText(struct text sortableText, int(*comp) (const char *, const char*));

//! @brief  Append text
//!
//! @param[in]      appendableText      Sortable text
//! @param[out]     stream              Output stream

void appendText(struct text appendableText, const char* path);

void appendContent(const char* content, const char* path);

int compStart(const char* ptr1, const char* ptr2);

//! @brief  Compare two strings from end
//!
//! @param  str1    Fisrt string
//!
//! @param  str2    Second string
//!
//! @return Negative if the mirrored first string is lexicographically greater than the mirrored second, zero if the strings are equal, positive if the mirrored first string is lexicographically less than the mirrored second

int compEnd(const char* ptr1, const char* ptr2);

size_t ostrlen(const char* ptr);

int checkfile(const char* path);
#endif
