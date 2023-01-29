//app.c
#include<stdio.h>
#include<string.h>
#include"dataDefinition.h"
#include"external.h"

int getInput(const List **session, int isExpense);
int showSession(const List **session);
int dropSession(const List **session);
int saveCurrentSession(const List **currentSession);
int openOutputData();
void printMenu();
void pauseBeforeShowingMenu();

int getInput(const List **session, int isExpense) {
    if(session == NULL || (isExpense != ACTIVE && isExpense != INACTIVE)) {
        printf("\n\tMessage: Unable to perform input operation: try again\n");
        return INVALID;
    }

    Record current;

    //get date:
    printf("\nEnter date in format (yyyymmdd): ");
    if(getCharInput(current.date, sizeof(current.date),ACTIVE) == INVALID) {
        printf("\n\tError: size overflow or Failed to read Input\n");
        return INVALID;
    }
    if(isValidDate(current.date) != VALID) { 
        printf("\n\t- Validation failed: Invalid date\n");
        return INVALID;
    }

    //get amount:
    printf("Enter amount: ");
    if(getCharInput(current.amount, sizeof(current.amount),ACTIVE) == INVALID) {
        printf("\n\tError: size overflow or Failed to read Input\n");
        return INVALID;
    }
    for(int i = strlen(current.amount)-1; i >= 0; i--) {
        if(i > 0) {
            current.amount[i] = current.amount[i-1];
        } else {
            if(isExpense == ACTIVE) {
                current.amount[i] = '-';
            } else {
                current.amount[i] = '+';
            }
        }
    }
    if(isValidAmount(current.amount) != VALID) { 
        printf("\n\t- Validation failed: Invalid amount\n");
        return INVALID;
    }
    cleanAmountFormat(current.amount);

    //get To/from:
    printf("Enter to/from: ");
    if(getCharInput(current.to, sizeof(current.to),INACTIVE) == INVALID) {
        printf("\n\tError: Failed to read Input\n");
        return INVALID;
    }
    cleanStringFormat(current.to); //trim last spaces
    if(isValidTo(current.to) != VALID) { 
        printf("\n\t- Validation failed: Invalid To/From\n");
        return INVALID;
    }

    //get comment:
    printf("Enter comment: ");
    if(getCharInput(current.comment, sizeof(current.comment),INACTIVE) == INVALID) {
        printf("\n\tError: Failed to read Input\n");
        return INVALID;
    }
    cleanStringFormat(current.to);//trim last spaces
    if(isValidComment(current.comment) != VALID) { 
        printf("\n\t- Validation failed: Invalid comment\n");
        return INVALID;
    }

    //add the record to the list
    if(addRecordList(current, session) == INVALID) {
        printf("\n\tError: Failed to add the record... please try again\n");
    } 
    printf("\n\t- Successfully added the input record...\n");
    return VALID;
}

int showSession(const List **session) {
    if(session == NULL) {
        printf("\n\tMessage: Unable to show current session: try again\n");
        return INVALID;
    } 
    if(*session == NULL) {
        printf("\n\t- No records in the session to show\n");
        return VALID;
    }
    printf("\n\tShowing current session:\n");
    if (showRecordList(session) == INVALID) {
        printf("\n\tError: Failed to show current session...\n");
        return INVALID;
    }
    return VALID;
}

int dropSession(const List **session) {
    if(session == NULL) {
        printf("\n\tMessage: Unable to drop session: try again\n");
        return INVALID;
    } 
    if(*session == NULL) {
        printf("\n\t- No records in the session to drop\n");
        return VALID;
    }
    printf("\n\tTrying to drop current session...\n");
    if(dropRecordList(session) == INVALID) {
        printf("\n\tError: Failed to drop session. Please try again\n");
        return INVALID;
    }
    printf("\n\t- Successfully dropped the session...\n");
    return VALID;
}

int saveCurrentSession(const List **currentSession) {
    if(currentSession == NULL) {
        printf("\n\tMessage: Unable to save session. Try again\n");
        return INVALID;
    }
    if(*currentSession == NULL) {
        printf("\n\t- No records in the current session to save\n");
        return VALID;
    }
    printf("\n\tTrying to save current session\n");
    if (saveSession(currentSession) == INVALID) {
        printf("\n\tError: Failed to save session\n");
        return INVALID;
    }
    printf("\n\t- Successfully saved the session\n");
    return VALID;
}

int openOutputData() {
    if(isFileExist() == INVALID) {
        printf("\n\t- No existing data. Try creating new records and save the session\n");
        return VALID;
    }
    printf("\nOpening your data file..\n");
    if(showOutputData() == INVALID) {
        printf("\n\tError: Unable to show records...\n");
        return INVALID;
    }
    return VALID;
}

void printMenu() {
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

void pauseBeforeShowingMenu() {
    char buffer[10];
    printf("\n\t~ press 'Enter' to go back to Menu: ");
    getCharInput(buffer,sizeof(buffer),INACTIVE);
}
