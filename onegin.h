#ifndef ONEGIN
#define ONEGIN

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <TXLib.h>

//! @brief  String type

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

//! @brief  Modified strlen
//!
//! @param  str     String
//!
//! @return Length of string without spaces in the begin of string

size_t ostrlen(const char* str);

//! @brief  Modified strcpy
//!
//! @param  str     String
//!
//! @return Length of string without spaces in the begin of string

char* ostrcpy(char* str1, const char* str2);
#endif
