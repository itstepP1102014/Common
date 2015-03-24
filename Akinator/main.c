#include "Akinator.h"

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


