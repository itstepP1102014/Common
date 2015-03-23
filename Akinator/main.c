#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct Data_
{
    enum Type {animal, noanimal} type;
    char *str;
    int sizestr;
} Data;

typedef struct Node_
{
    Data data;
    struct Node_ *parent, *yeslink, *nolink;
} Node;

void addNewFork(Node *oldAnimal, Node *newAnimal, Node *question, bool answer);
void hangFork(Node **root, Node *parent, Node *fork, bool wayToChild);
bool determineWayToChild(Node *node);
bool addNewKnowledge(Node **rootNode, Node *destination, char *question, char *newAnimal, bool rightAnswer);
bool createNewNode(Node **node, char *str, enum Type type);

Node *playGame(Node *root);

int main()
{
    Node *root = NULL;
    createNewNode(&root, "кот", animal);
    addNewKnowledge(&root, root, "Оно живёт в воде?", "кит", true);
    Node *p = playGame(root);
    printf("Это %s. Я угадала?\n", p->data.str);
    char answer;
    scanf(" %c", &answer);
    if(answer == 'y')
        printf("Я победила!\n");
    else
        printf("Я проиграла!\n");
    return 0;
}

void addNewFork(Node *oldAnimal, Node *newAnimal, Node *question, bool answer)
{
    if(answer)
    {
        question->yeslink = newAnimal;
        question->nolink = oldAnimal;
    }
    else
    {
        question->yeslink = oldAnimal;
        question->nolink = newAnimal;
    }
    oldAnimal->parent = question;
    newAnimal->parent = question;
}

void hangFork(Node **root, Node *parent, Node *fork, bool wayToChild)
{
    if(!parent)
        *root = fork;
    else
    {
        if(wayToChild)
            parent->yeslink = fork;
        else
            parent->nolink = fork;
    }
}

bool determineWayToChild(Node *node)
{
    if(!node || !node->parent)
        return false;
    else
        return node->parent->yeslink == node;
}

bool addNewKnowledge(Node **root, Node *destination, char *question, char *newAnimal, bool rightAnswer)
{
    assert(destination);
    Node *questionNode = NULL, *newAnimalNode = NULL;
    if(!createNewNode(&questionNode, question, noanimal))
        return false;
    if(!createNewNode(&newAnimalNode, newAnimal, animal))
    {
        free(questionNode);
        questionNode = NULL;
        return false;
    }
    Node *parent = destination->parent;
    bool wayToChild = determineWayToChild(destination);
    addNewFork(destination, newAnimalNode, questionNode, rightAnswer);
    hangFork(root, parent, questionNode, wayToChild);
    return true;
}

bool createNewNode(Node **node, char *str, enum Type type)
{
    char *p = NULL;
    p = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if(!p)
        return false;
    Node *q = NULL;
    q = (Node *)malloc(sizeof(Node));
    if(!q)
    {
        free(p);
        p = NULL;
        return false;
    }
    strcpy(p, str);
    q->data.str = p;
    q->data.sizestr = strlen(p) + 1;
    q->data.type = type;
    *node = q;
    p = NULL;
    q = NULL;
    return true;
}

Node *playGame(Node *root)
{
    Node *p = root;
    while(p->data.type == noanimal)
    {
        printf("%s\n", p->data.str);
        printf("Enter y/n: ");
        char answer;
        scanf(" %c", &answer);
        if(answer == 'y')
            p = p->yeslink;
        else
            p = p->nolink;
    }
    return p;
}
