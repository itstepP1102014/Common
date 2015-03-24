#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

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

#endif // AKINATOR_H_INCLUDED
