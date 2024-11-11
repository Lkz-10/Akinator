#include <stdio.h>
#include <stdlib.h>

#include "../Tree/TreeGlobals.h"
#include "../Tree/TreeFunctions.h"
#include "AkinatorFunctions.h"

int main(const int argc, const char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Enter the file name!\n");
        return -1;
    }

    FILE* file_ptr = fopen(argv[1], "r");

    Node_t* root = NULL;
    root = ReadTree(root, file_ptr);

    fclose(file_ptr);

    assert(root);

    printf("%s\n", root->data);

    //Print_inorder(root, stderr);

    Guess(root);

    TreeDtor(root);



    return 0;
}
