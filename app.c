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
    if(getCharInput(current.amount, sizeof(current.amount)-1,ACTIVE) == INVALID) {
        printf("\n\tError: size overflow or Failed to read Input\n");
        return INVALID;
    }
    for(int i = sizeof(current.amount)-1; i >= 0; i--) {
        if(i >= 1 && i <= strlen(current.amount)) {
            current.amount[i] = current.amount[i-1];
        } else if(i == 0) {
            if(isExpense == ACTIVE) {
                current.amount[i] = '-';
            } else {
                current.amount[i] = '+';
            }
        } else {
            current.amount[i] = '\0';
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
