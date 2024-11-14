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

int Guess(Node_t* node)
{
    if (!node)
    {
        fprintf(stderr, "Error: null-pointer cannot be used as a node!\n");
        return -1;
    }

    printf("\nIs your club %s?\n", node->data);

    char answer[MAX_STRING_SIZE] = {};

    scanf("%s", answer);

    if (stricmp(answer, "yes") == 0)
    {
        if (node->left == NULL)
        {
            printf("I knew it!\n\n");
            return 0;
        }

        return Guess(node->left);
    }

    if (stricmp(answer, "no") == 0)
    {
        if (node->right == NULL)
        {
            if (stricmp(node->data, "Zenit") == 0)
            {
                printf("Error: dumb user!\n\n");

                return 0;
            }

            if (stricmp(node->data, "Mancity") == 0)
            {
                printf("Error: user doesn't understand football!\n\n");

                return 0;
            }


        }
        return Guess(node->right);
    }

    fprintf(stderr, "Wrong answer: %s!\n", answer);
    //while (int c = getchar() != 0 && c != EOF) {}
    return Guess(node);
}

int Definition(Node_t* root, const char* elem)
{
    if (!root || !elem)
    {
        fprintf(stderr, "Definition error: elem(%s), root(%p)!\n", elem, root);
        return -1;
    }

    char definition[DEF_ARR_SIZE][MAX_STRING_SIZE] = {};

    int def_cnt = MakeDef(root, elem, definition);

    if (def_cnt < 1)
    {
        fprintf(stderr, "Error: no such club: \"%s\"!\n\n", elem);
        return -1;
    }

    printf("%s is ", elem);

    for (int i = def_cnt - 1; i > 0; --i)
    {
        printf("%s, ", definition[i]);
    }

    printf("%s.\n\n", definition[0]);

    return 0;
}

int MakeDef(Node_t* node, const char* elem, char definition[DEF_ARR_SIZE][MAX_STRING_SIZE])
{
    if (!node) return -1;

    if (stricmp(node->data, elem) == 0) return 0;

    int def_cnt = MakeDef(node->left, elem, definition);

    if (def_cnt > -1)
    {
        strcpy(definition[def_cnt], node->data);

        return ++def_cnt;
    }

    def_cnt = MakeDef(node->right, elem, definition);

    if (def_cnt > -1)
    {
        strcpy(definition[def_cnt], "not ");
        strcpy(definition[def_cnt] + 4, node->data);

        return ++def_cnt;
    }

    return -1;
}

int DrawTree(Node_t* root, const char* file_name)
{
    if (!root || !file_name)
    {
        fprintf(stderr, "Drawing error: root(%p), file(%s)\n", root, file_name);
        return -1;
    }

    FILE* file_ptr = fopen(file_name, "w");
    assert(file_ptr);

    fprintf(file_ptr, "digraph G\n{\n  rankdir = UD;\n");

    DrawNode(root, file_ptr);

    fprintf(file_ptr, "}");

    fclose(file_ptr);

    system("dot Tree.dot -Tpng -o Tree.png");

    return 0;
}

int DrawNode(Node_t* node, FILE* file_ptr)
{
    if (!node) return 0;

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return -1;
    }

    fprintf(file_ptr, "  \"%s\" [shape = Mrecord, ", node->data);

    if (!node->parent)
    {
        fprintf(file_ptr, "style = \"filled\", fillcolor = \"bisque2\", ");
    }
    else if (!node->left && !node->right)
    {
        fprintf(file_ptr, "style = \"filled\", fillcolor = \"darkolivegreen1\", ");
    }

    fprintf(file_ptr, "label = \"{%-30s | address = %p| left = %p | right = %p | parent = %p}\"];\n",
            node->data, node, node->left, node->right, node->parent);

    if (DrawNode(node->left,  file_ptr) != 0) return -1;
    if (DrawNode(node->right, file_ptr) != 0) return -1;

    if (node->left)
    {
        fprintf(file_ptr, "  edge[color = \"green\"];\n");
        fprintf(file_ptr, "  \"%s\" -> \"%s\";\n", node->data, node->left->data);
    }

    if (node->right)
    {
        fprintf(file_ptr, "  edge[color = \"red\"];\n");
        fprintf(file_ptr, "  \"%s\" -> \"%s\";\n", node->data, node->right->data);
    }

    return 0;
}
