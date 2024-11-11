#ifndef __AKINATOR_FUNCTIONS_H__
#define __AKINATOR_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Tree/TreeGlobals.h"
#include "../Tree/TreeFunctions.h"

const int MAX_STRING_SIZE = 52;

Node_t* ReadTree (Node_t* parent, FILE* file_ptr);
int     Guess    (Node_t* node);

#endif
