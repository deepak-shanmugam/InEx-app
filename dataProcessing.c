#include <stdio.h>
#include <string.h>
#include"dataDefinition.h"

int getCharInput(char *str, int length, int isLengthConstraint);
void cleanAmountFormat(char *myDate);
void cleanStringFormat(char *myString);

int getCharInput(char *str, int length, int isLengthConstraint) { 
    if(str == NULL || length <= 1 || (isLengthConstraint != ACTIVE && isLengthConstraint != INACTIVE)) {
        printf("\n\tWarning: Error occured while getting input: \n");
        return INVALID;
    }
    int count = 0;
    if(fgets(str, length, stdin) == NULL) {
        return INVALID;
    } else {
        size_t pos = strcspn(str,"\n");
        //if '\n' comes in the position >= length
        if(pos == length-1) {
            int ch = 0;
            //till '\n' or EOF comes, read the extra input (If exists)
            while(ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
                count++;
            }
        } else {
            str[pos] = '\0';
        }
    }
    //Return INVALID if the input have extra length except '\n' (only if the length constraint is active)
    if(isLengthConstraint == ACTIVE && count > 1) {
        return INVALID;
    }
    return VALID;
}

//Function to clean spaces and new lines at the end of the string
void cleanStringFormat(char *myString) {
    if(myString == NULL) {
        printf("\n\tWarning: Error occured while cleaning String data: \n");
        return;
    }
    int loop;
    for(loop = strlen(myString)-1; loop >= 0 && (myString[loop] == ' ' || myString[loop] == '\n'); loop--);
    myString[loop+1] = '\0';
}

void cleanAmountFormat(char *myDate) { //use isValidAmount before calling this function
    if(myDate == NULL) {
        printf("\n\tWarning: Error occured while cleaning Amount data: \n");
        return;
    }
    int sign = INACTIVE, decial_point = INACTIVE, integral_part = 0, decimal_part = 0, automate = INACTIVE;
    for(int i=0; i < strlen(myDate); i++) {
        if(myDate[i] == '-' || myDate[i] == '+') {
            sign = ACTIVE;
        } else if(myDate[i] == '.') {
            decial_point = ACTIVE;
        } else {
            if(decial_point == ACTIVE) {
                decimal_part++;
            } else {
                integral_part++;
            }
        }
    }
    integral_part += sign;
    if(myDate[integral_part] != '.') {
        myDate[integral_part] = '.';
        automate = ACTIVE;
    }
    if(automate == ACTIVE || myDate[integral_part+1] < '0' || myDate[integral_part+1] > '9') {
        myDate[integral_part+1] = '0';
        automate = ACTIVE;
    }
    if(automate == ACTIVE || myDate[integral_part+2] < '0' || myDate[integral_part+2] > '9') {
        myDate[integral_part+2] = '0';
        automate = ACTIVE;
    }
    myDate[integral_part+3] = '\0';
}
