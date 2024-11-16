#include <stdio.h>
#include <stdlib.h>

#include "AkinatorFunctions.h"
#include "ReadData.h"

int main(const int argc, const char** argv)
{
    Node_t* root = NULL;

    root = ReadData(argc, argv);

    if (!root)
    {
        fprintf(stderr, "Reading error: root = NULL!\n");
        return -1;
    }

    Run(root, argv);

    TreeDtor(root);

    return 0;
}
