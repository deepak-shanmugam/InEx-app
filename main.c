//main.c
#include<stdio.h>
#include"dataDefinition.h"
#include"api.h"

static void printMenu();
static void pauseBeforeShowingMenu();

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
                                printf("\n\tError: operation failed: \n");
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
            case 1: case 2:
                if(getInput(&currentSession, choice-1) == INVALID) {
                    printf("\toperation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 3:
                if(showSession(&currentSession) == INVALID) {
                    printf("\toperation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 4:
                printf("\n\t- you have choosed to drop the session. \n");
                printf("\t(Note: All records in the current session will be deleted)\n\n");
                while(1) {
                    printf("\tDo you want to continue (Y/n): ");
                    if(getCharInput(buffer, 2, INACTIVE) == INVALID) {
                        printf("\t- Error: Problem saving session...\n");
                        break;
                    }
                    if(buffer[0] == 'y' || buffer[0] == 'Y') {
                        if(dropSession(&currentSession) == INVALID) {
                            printf("\toperation failed: \n");
                        }
                        break;
                    } else if (buffer[0] == 'N' || buffer[0] == 'n') {
                        break;
                    }
                }
                pauseBeforeShowingMenu();
                break;
            case 5:
                if(saveCurrentSession(&currentSession) == INVALID) {
                    printf("\toperation failed: \n");
                }
                pauseBeforeShowingMenu();
                break;
            case 6:
                if(openOutputData() == INVALID) {
                    printf("\toperation failed: \n");
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

static void printMenu() {
    printf("\n*************************--MENU--***************************\n");
    printf("Please Enter\n");
    printf("\t0 - To exit\n");
    printf("\t1 - To create an Income record\n");
    printf("\t2 - To create an Expense record\n");
    printf("\t3 - To show the current session of unsaved records\n");
    printf("\t4 - To drop/delete current session\n");
    printf("\t5 - To save current session of records\n");
    printf("\t6 - To open or show your entire data\n");
    printf("\npress ctrl+c for emergency exit (Note: you might lose data)\n");
    printf("*************************--END--*****************************\n");
}

static void pauseBeforeShowingMenu() {
    char buffer[10];
    printf("\n\t~ press 'Enter' to go back to Menu: ");
    getCharInput(buffer,sizeof(buffer),INACTIVE);
}