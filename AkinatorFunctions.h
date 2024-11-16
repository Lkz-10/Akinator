#ifndef __AKINATOR_FUNCTIONS_H__
#define __AKINATOR_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Tree/TreeGlobals.h"
#include "../Tree/TreeFunctions.h"
#include "AkinatorGlobals.h"

int     Run        (Node_t* root, const char** argv);
int     Guess      (Node_t* root, Node_t* node, const char* data_file_name);
int     CreateNode (Node_t* root, Node_t* node, const char* data_file_name);
int     PrintData  (Node_t* node, FILE* file_ptr);
int     DrawTree   (Node_t* root, const char* file_name);
int     DrawNode   (Node_t* node, FILE* file_ptr);
int     Definition (Node_t* root, const char* elem);
int     MakeDef    (Node_t* node, const char* elem, char definition[DEF_ARR_SIZE][MAX_STRING_SIZE]);
char*   GetTerm    (char* term);

#endif
