#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


typedef struct _Data
{
    enum Type{animal, no_animal} type;
    char *str;
    int size_str;
} Data;


typedef struct _Node
{
     Data data;
     struct _Node *parent, *yes_link, *no_link;
} Node;


void AddNewFork(Node *old_animal, Node *new_animal, Node *qustion, bool answer);
void HangFork(Node **root, Node *parent, Node *fork, bool way_to_child);
bool DetermineWayToChild(Node *node);
bool AddNewKnowledge(Node **root, Node *destination, char *question, char *animal, bool answer);
bool CreateNewNode(Node **node, char *str, enum Type type);
Node *PlayGame(Node *root);


int main()
{
    Node *root = NULL;
    CreateNewNode(&root, "кот", animal);
    AddNewKnowledge(&root, root, "Оно живет в воде?", "кит", true);
    Node *p = PlayGame(root);
    printf("Это %s. Я угадала?\n", p->data.str);
    char answer;
    scanf(" %c", &answer);
    if(answer == 'y')
    {
        printf("Я выиграла :)\n");
    }
    else
    {
        printf("Я проиграла :(\n");
    }

    return 0;
}

void AddNewFork(Node *old_animal, Node *new_animal, Node *question, bool answer)
{
    if(answer)
    {
        question->yes_link = new_animal;
        question->no_link = old_animal;
    }
    else
    {
        question->yes_link = old_animal;
        question->no_link = new_animal;
    }
    new_animal->parent = question;
    old_animal->parent = question;
}


void HangFork(Node **root, Node *parent, Node *fork, bool way_to_child)
{
    if(!parent)
    {
        *root = fork;
    }
    else
    {
        if(way_to_child)
        {
            parent->yes_link = fork;
        }
        else
        {
            parent->no_link = fork;
        }
    }
}


bool DetermineWayToChild(Node *node)
{
    if(!node || !node->parent)
    {
        return false;
    }
    return (node->parent->yes_link == node);
}


bool AddNewKnowledge(Node **root, Node *destination, char *question, char *new_animal, bool answer)
{
    assert(destination);//проверяем что дерево не пусто
    Node *question_node = NULL, *new_animal_node = NULL;
    if(!CreateNewNode(&question_node, question, no_animal))
    {
        return false;
    }
    if(!CreateNewNode(&new_animal_node, new_animal, animal))
    {
        free(question_node);
        question_node = NULL;
        return false;
    }
    Node *parent = destination->parent;
    bool way_to_child = DetermineWayToChild(destination);
    AddNewFork(destination, new_animal_node, question_node, answer);
    HangFork(root, parent, question_node, way_to_child);
    return true;
}


bool CreateNewNode(Node **node, char *str, enum Type type)
{
    char *p = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if(!p)
    {
        return false;
    }
    Node *q = (Node*)malloc(sizeof(Node));
    if(!q)
    {
        free(p);
        p = NULL;
        return false;
    }
    strcpy(p, str);
    q->data.str = p;
    q->data.size_str = strlen(p) + 1;
    q->data.type = type;
    *node = q;
    p = NULL;
    q = NULL;
    return true;
}



Node *PlayGame(Node *root)
{
    Node *p = root;
    while(p->data.type == no_animal)
    {
        printf("%s\nEnter y/n: ", p->data.str);
        char answer;
        scanf(" %c", &answer);
        if(answer == 'y')
        {
            p = p->yes_link;
        }
        else
        {
            p = p->no_link;
        }
    }
    return p;
}









