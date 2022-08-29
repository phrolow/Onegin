#ifndef ONEGIN
#define ONEGIN
//#define TEST

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TXLib.h>

const int MAXSIZE = 5000,
          MAXLINE = 1000;


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

struct text textFromFile(FILE *stream);

//! @brief  Sort text
//!
//! @param  sortableText    Sortable text

void sortFromStart(struct text sortableText);

//! @brief  Sort text
//!
//! @param  sortableText    Sortable text

void sortFromEnd(struct text sortableText);

//! @brief  Append text
//!
//! @param[in]      appendableText      Sortable text
//! @param[out]     stream              Output stream

void appendText(struct text appendableText, FILE *stream);

#endif
