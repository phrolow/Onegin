#ifndef ONEGIN
#define ONEGIN
//#define TEST

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TXLib.h>

//! @brief  Max lines in text

const int MAXSIZE = 5000;

//! @brief  Max chars in line

const int MAXLINE = 1000;

typedef char* str;

//! @brief  Text

struct text {
    str *content;
    size_t nLine;
};

//! @brief  Text constructor
//!
//! @param  content         Array of strings
//!
//! @return New struct text

struct text maketext(str *content, size_t nLine);

//! @brief  Get text from file
//!
//! @param  stream          Input stream
//!
//! @return Struct text, which contains text from file

struct text textFromFile(char *path);

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

void appendText(struct text appendableText, char *path);

//! @brief  Compare two strings from end
//!
//! @param  str1    Fisrt string
//!
//! @param  str2    Second string
//!
//! @return Negative if the mirrored first string is lexicographically greater than the mirrored second, zero if the strings are equal, positive if the mirrored first string is lexicographically less than the mirrored second

int compEnd(const char* str1, const char* str2);
#endif
