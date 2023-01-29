//main.c
#include<stdio.h>
#include"dataDefinition.h"
#include"api.h"

int main(int argc, char **argv) {
    List *currentSession = NULL;
    int exit = INACTIVE;
    while (exit == INACTIVE) {
        printMenu();
        char buffer[10];
        int choice;
        printf("\nEnter your choice: ");
        while(getCharInput(buffer, 2, ACTIVE) == INVALID) {
            printf("Please enter valid choice: ");
        }
        if(sscanf(buffer,"%d",&choice) != 1) {
            printf("\n\tError Message: INVALID Input...\n");
            pauseBeforeShowingMenu();
            continue;
        }
        switch(choice) {
            case 0:
                if(currentSession != NULL) {
                    printf("\nCurrent session is not saved:\n");
                    while(1) {
                        printf("\t- Do you want to save the session before exit? (Y/n): ");
                        if(getCharInput(buffer, 2, INACTIVE) == INVALID) {
                            printf("\t- Error: Problem saving session...\n");
                            break;
                        }
                        if(buffer[0] == 'y' || buffer[0] == 'Y') {
                            if(saveCurrentSession(&currentSession) == INVALID) {
                                printf("operation failed: \n");
                            }
                            break;
                        } else if (buffer[0] == 'N' || buffer[0] == 'n') {
                            break;
                        }
                    }
                }
                exit = ACTIVE;
                printf("\nApplication is Exiting...\n");
                break;
            case 1:
                if(getInput(&currentSession, INACTIVE) == INVALID) {
                    printf("operation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 2:
                if(showSession(&currentSession) == INVALID) {
                    printf("operation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 3:
                if(dropSession(&currentSession) == INVALID) {
                    printf("operation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 4:
                if(saveCurrentSession(&currentSession) == INVALID) {
                    printf("operation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 5:
                if(openOutputData() == INVALID) {
                    printf("operation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            default:
                printf("\n\t- Choosen option not available\n");
                pauseBeforeShowingMenu();
        }
    }
    return 0;
}