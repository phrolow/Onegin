#ifndef ONEGIN
#define ONEGIN
//#define TEST

#include <stdio.h>

//! @brief Text

struct text {
    char *content;
};

//! @brief Text constructor
//!
//! @param content Literally text
//!
//! @return New struct text

struct text maketext(char *content);

struct text textFromFile(char *path);

void sortFromStart

#endif
