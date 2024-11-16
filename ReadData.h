#ifndef __READ_DATA_H__
#define __READ_DATA_H__

#include <stdio.h>
#include <stdlib.h>

#include "AkinatorGlobals.h"
#include "../Tree/TreeGlobals.h"
#include "../Tree/TreeFunctions.h"

Node_t* ReadData (const int argc, const char** argv);
Node_t* ReadTree (Node_t* parent, FILE* file_ptr);

#endif
