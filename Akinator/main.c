#include "Akinator.h"

int main()
{
    FILE *filepointer = NULL;
    Node *root = NULL, *play = NULL;
    char answer;

    do
    {
        system("clear");
        filepointer = fopen("DataBase.txt", "r");
        if(!filepointer)
        {
            fprintf(stderr, "Cannot open the file.\n");
            exit(1);
        }
        readFromFile(filepointer, &root);
        fclose(filepointer);
        filepointer = NULL;
    // -----
        play = playGame(root);

        printf("Это %s. Я угадала?\nНажми y/n: ", play->data.str);
        scanf(" %c", &answer);
        if(answer == 'y')
            printf("Я победила!\n");
        else
        {
            printf("Я проиграла! Помогите мне стать еще более умной и интересной!\n");
            addNewInformation(&root, play);
            filepointer = fopen("DataBase.txt", "w");
            if(!filepointer)
            {
                clearTree(&root);
                play = NULL;
                fprintf(stderr, "Cannot open the file.\n");
                exit(1);
            }
            writeToFile(filepointer, root);
            fclose(filepointer);
        }

        clearTree(&root);
        play = NULL;

        printf("Хочешь сыграть еще? y/n ");
        scanf(" %c", &answer);
    } while(answer == 'y');

    return 0;
}


