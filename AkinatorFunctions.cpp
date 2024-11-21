#include "AkinatorFunctions.h"

int Run(Node_t* root, const char** argv)
{
    printf("\nChoose mode:\n  if you want to play enter \"p\"\n  if you want to visualize the tree enter \"v\"\n  "
           "if you want to get a definition enter \"d\"\n  if you want to compare two teams enter\"c\"\n");

    int mode = getchar();

    switch(mode)
    {
        case PLAY:
        {
            return Guess(root, root, argv[1]);
        }

        case VISUALIZE:
        {
            return DrawTree(root, argv[2]);
        }

        case DEFINITION:
        {
            char term[MAX_STRING_SIZE] = {};
            return Definition(root, GetTerm(term));
        }

        case COMPARE:
        {
            char term1[MAX_STRING_SIZE] = {};
            char term2[MAX_STRING_SIZE] = {};

            return Compare(root, GetTerm(term1), GetTerm(term2));
        }

        default:
        {
            fprintf(stderr, "Error: wrong mode: \"%c\"! Try again!\n", mode);

            return Run(root, argv);
        }
    }

    return 0;
}

char* GetTerm(char* term)
{
    printf("\nEnter the team\n");

    scanf("\n%[^\n]", term);

    return term;
}

int Guess(Node_t* root, Node_t* node, const char* data_file_name)
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
            printf("\nI knew it!\n\n");
            return 0;
        }

        return Guess(root, node->left, data_file_name);
    }

    if (stricmp(answer, "no") == 0)
    {
        if (node->right == NULL)
        {
            if (stricmp(node->data, "Zenit") == 0 || stricmp(node->data, "Kartel") == 0)
            {
                printf("\nError: dumb user!\n\n");

                return 0;
            }

            if (stricmp(node->data, "Mancity") == 0)
            {
                printf("\nError: user doesn't understand football!\n\n");

                return 0;
            }

            CreateNode(root, node, data_file_name);

            return 0;
        }

        return Guess(root, node->right, data_file_name);
    }

    fprintf(stderr, "Wrong answer: %s!\n", answer);

    return Guess(root, node, data_file_name);
}

int CreateNode(Node_t* root, Node_t* node, const char* data_file_name)
{
    assert(node);

    printf("\nWho is it?\n");

    char new_node_name[MAX_STRING_SIZE] = {};
    char new_question [MAX_STRING_SIZE] = {};

    scanf("\n%[^\n]", new_node_name);

    printf("\nWhat is the difference between \"%s\" and \"%s\"? \"%s\" is ...\n",
           new_node_name, node->data, new_node_name);

    scanf("\n%[^\n]", new_question);

    if (node->parent->left == node)
    {
        node->parent->left = NewNode(node->parent, new_question);

        node->parent->left->right = node;

        node->parent->left->left = NewNode(node->parent->left, new_node_name);

        node->parent = node->parent->left;
    }
    else if (node->parent->right == node)
    {
        node->parent->right = NewNode(node->parent, new_question);

        node->parent->right->right = node;

        node->parent->right->left = NewNode(node->parent->right, new_node_name);

        node->parent = node->parent->right;
    }

    printf("\nDo you want to save the changes?\n");

    char answer[MAX_STRING_SIZE] = {};

    scanf("%s", answer);

    if (stricmp(answer, "no") == 0) return 0;

    FILE* file_ptr = fopen(data_file_name, "w");

    PrintData(root, file_ptr);
    fprintf(file_ptr, "\n");

    fclose(file_ptr);

    return 0;
}

int PrintData(Node_t* node, FILE* file_ptr)
{
    if (!node) return 0;

    fprintf(file_ptr, "{\"%s\"", node->data);

    PrintData(node->left,  file_ptr);
    PrintData(node->right, file_ptr);

    fprintf(file_ptr, "}");

    return 0;
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

    if (def_cnt < 0)
    {
        fprintf(stderr, "Error: no such team: \"%s\"!\n\n", elem);
        return -1;
    }

    printf("\n%s is ", elem);

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

int Compare(Node_t* root, const char* term1, const char* term2)
{
    if (!root || !term1 || !term2)
    {
        fprintf(stderr, "Comparing error: root(%p), term1(%p), term2(%p)!\n", root, term1, term2);

        return -1;
    }

    char definition1[DEF_ARR_SIZE][MAX_STRING_SIZE] = {};
    char definition2[DEF_ARR_SIZE][MAX_STRING_SIZE] = {};

    int def_index1 = MakeDef(root, term1, definition1) - 1;
    int def_index2 = MakeDef(root, term2, definition2) - 1;

    if (def_index1 < 0)
    {
        fprintf(stderr, "No such team: %s!\n", term1);
        return -1;
    }

    if (def_index2 < 0)
    {
        fprintf(stderr, "No such team: %s!\n", term2);
        return -1;
    }

    if (strcmp(definition1[def_index1], definition2[def_index2]) == 0)
    {
        printf("\n%s and %s are both %s", term1, term2, definition1[def_index1]);

        def_index1--;
        def_index2--;

        while (def_index1 >= 0 && def_index2 >= 0 &&
               strcmp(definition1[def_index1], definition2[def_index2]) == 0)
        {
            printf(", %s", definition1[def_index1]);

            --def_index1;
            --def_index2;
        }

        printf("\n");
    }

    if (def_index1 >= 0)
    {
        printf("\n%s is %s", term1, definition1[def_index1--]);

        for (int i = def_index1; i >= 0; --i)
        {
            printf(", %s", definition1[i]);
        }
    }

    if (def_index2 >= 0)
    {
        printf("\n%s is %s", term2, definition2[def_index2--]);

        for (int i = def_index2; i >= 0; --i)
        {
            printf(", %s", definition2[i]);
        }

        printf("\n");
    }

    return 0;
}

int MaxLen(size_t len1, size_t len2)
{
    if (len1 > len2) return (int)len1;

    return (int)len2;
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
        fprintf(file_ptr, "color = \"goldenrod4\", style = \"filled\", fillcolor = \"bisque2\", ");
    }
    else if (!node->left && !node->right)
    {
        fprintf(file_ptr, "color = \"limegreen\", style = \"filled\", fillcolor = \"darkolivegreen1\", ");
    }
    else
    {
        fprintf(file_ptr, "color = \"khaki3\", style = \"filled\", fillcolor = \"lemonchiffon\", ");
    }

    fprintf(file_ptr, "label = \"{%-30s | address = %p| left = %p | right = %p | parent = %p}\"];\n",
            node->data, node, node->left, node->right, node->parent);

    if (DrawNode(node->left,  file_ptr) != 0) return -1;
    if (DrawNode(node->right, file_ptr) != 0) return -1;

    if (node->left)
    {
        fprintf(file_ptr, "  edge[color = \"green\", fontcolor = \"green3\"];\n");
        fprintf(file_ptr, "  \"%s\" -> \"%s\" [label = \" yes\"];\n", node->data, node->left->data);
    }

    if (node->right)
    {
        fprintf(file_ptr, "  edge[color = \"red\", fontcolor = \"red\"];\n");
        fprintf(file_ptr, "  \"%s\" -> \"%s\" [label = \" no\"];\n", node->data, node->right->data);
    }

    return 0;
}
