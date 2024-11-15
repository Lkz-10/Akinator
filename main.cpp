#include <stdio.h>
#include <stdlib.h>

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

    Run(root, argv);

    //Print_inorder(root, stderr);
    //DrawTree(root, argv[2]);

    //Guess(root, root, argv[1]);


    //Guess(root, root, argv[1]);

    //Definition(root, "Liverpool");

    TreeDtor(root);

    return 0;
}
