#include "ReadData.h"

Node_t* ReadData(const int argc, const char** argv)
{
    if (argc < ARGV_SIZE) {
        fprintf(stderr, "Enter the file name!\n");
        return NULL;
    }

    FILE* file_ptr = fopen(argv[1], "r");

    Node_t* root = NULL;

    root = ReadTree(root, file_ptr);

    fclose(file_ptr);

    return root;
}

Node_t* ReadTree(Node_t* parent, FILE* file_ptr)
{
    if (!file_ptr) {
        fprintf(stderr, "File error!\n");
        return NULL;
    }

    int symbol = fgetc(file_ptr);

    if (symbol == '{')
    {
        char node_name[MAX_STRING_SIZE] = {};
        int  nchar = 0;

        if (fscanf(file_ptr, "\"%[^\"]\"%n", node_name, &nchar) < 1)
        {
            fprintf(stderr, "Reading error!\n");
            return NULL;
        }
        //fprintf(stderr, "nchar: %d\n", nchar);

        Node_t* node = NewNode(parent, node_name);

        symbol = fgetc(file_ptr);

        if (symbol == '}')
        {
            while (symbol != '{' && symbol != EOF) symbol = fgetc(file_ptr);
            fseek(file_ptr, -1, SEEK_CUR);

            return node;
        }

        while (symbol != '{' && symbol != EOF) symbol = fgetc(file_ptr);
        fseek(file_ptr, -1, SEEK_CUR);

        node->left  = ReadTree(node, file_ptr);
        node->right = ReadTree(node, file_ptr);

        return node;
    }

    return NULL;
}
