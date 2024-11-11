#include "AkinatorFunctions.h"

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
        int nchar = 0;
        if (fscanf(file_ptr, "\"%[^\"]\"%n", node_name, &nchar) < 1)
        {
            fprintf(stderr, "Reading error!\n");
            return NULL;
        }
        fprintf(stderr, "nchar: %d\n", nchar);

        Node_t* node = NewNode(parent, node_name);
        fprintf(stderr, "node: %p\n", node);

        symbol = fgetc(file_ptr);

        if (symbol == '}')
        {
            while (symbol != '{' && symbol != EOF) symbol = fgetc(file_ptr);
            fseek(file_ptr, -1, SEEK_CUR);
            fprintf(stderr, "node before return: %p\n", node);

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

int Guess(Node_t* node)
{
    assert(node);

    printf("\nIs your club %s?\n", node->data);

    char answer[MAX_STRING_SIZE] = {};

    scanf("%s", answer);

    if (stricmp(answer, "yes") == 0)
    {
        if (node->left == NULL)
        {
            printf("I knew it!\n");
            return 0;
        }
        return Guess(node->left);
    }
    if (stricmp(answer, "no") == 0)
    {
        if (node->right == NULL)
        {
            printf("Zenit champion anyway!\n");
            return 0;
        }
        return Guess(node->right);
    }

    fprintf(stderr, "Wrong answer: %s!\n", answer);
    //while (int c = getchar() != 0 && c != EOF) {}
    return Guess(node);
}
