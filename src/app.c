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
    if(getRecord(&current, isExpense) == INVALID) {
        //printf("\n\tMessage: Please give valid data\n");
        return INVALID;
    }
    //add the record to the list
    if(addRecordList(current, session) == INVALID) {
        printf("\n\tError: Failed to add the record... please try again\n");
        return INVALID;
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
