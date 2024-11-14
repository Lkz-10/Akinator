#ifndef __AKINATOR_FUNCTIONS_H__
#define __AKINATOR_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Tree/TreeGlobals.h"
#include "../Tree/TreeFunctions.h"

const int MAX_STRING_SIZE = 52;
const int DEF_ARR_SIZE    = 52;

Node_t* ReadTree   (Node_t* parent, FILE* file_ptr);
int     Guess      (Node_t* node);
int     DrawTree   (Node_t* root, const char* file_name);
int     DrawNode   (Node_t* node, FILE* file_ptr);
int     Definition (Node_t* root, const char* elem);
int     MakeDef    (Node_t* node, const char* elem, char definition[DEF_ARR_SIZE][MAX_STRING_SIZE]);

#endif
