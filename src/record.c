//validate.c
#include<stdio.h>
#include<string.h>
#include"dataDefinition.h"

/*fuctions in dataProcessing.c*/
extern int getCharInput(char *str, int length, int lengthConstraint);
extern void cleanAmountFormat(char *myDate);
extern void cleanStringFormat(char *myString);

int getRecord(Record *myRec, int isExpense);
static int isValidDate(const char *myDate);
static int isValidAmount(const char *myAmount);
static int isValidTo(const char *myTo);
static int isValidComment(const char *myComment);
static void addSignToAmount(char *amount, int size, int isExpense);

int getRecord(Record *current, int isExpense){
    if(current == NULL || (isExpense != ACTIVE && isExpense != INACTIVE)) {
        printf("\n\tError: Something went wrong\n");
        return INVALID;
    }
    
    //get date:
    printf("\n*Enter date in format (yyyymmdd): ");
    if(getCharInput(current->date, sizeof(current->date),ACTIVE) == INVALID) {
        printf("\n\tError: size overflow or Failed to read Input\n");
        return INVALID;
    }
    if(isValidDate(current->date) != VALID) { 
        printf("\n\t- Validation failed: Invalid date\n");
        return INVALID;
    }

    //get amount:
    printf("*Enter amount: ");
    if(getCharInput(current->amount, sizeof(current->amount)-1,ACTIVE) == INVALID) {
        printf("\n\tError: size overflow or Failed to read Input\n");
        return INVALID;
    }
    cleanStringFormat(current->amount);
    
    //assigning signature to amount (+/-) to distinguish income and expense records
    addSignToAmount(current->amount, sizeof(current->amount),isExpense);
    
    if(isValidAmount(current->amount) != VALID) { 
        printf("\n\t- Validation failed: Invalid amount\n");
        return INVALID;
    }
    cleanAmountFormat(current->amount);

    //get To/from:
    printf("*Enter to/from: ");
    if(getCharInput(current->to, sizeof(current->to),INACTIVE) == INVALID) {
        printf("\n\tError: Failed to read Input\n");
        return INVALID;
    }
    cleanStringFormat(current->to); //trim last spaces
    if(isValidTo(current->to) != VALID) { 
        printf("\n\t- Validation failed: Invalid To/From\n");
        return INVALID;
    }

    //get comment:
    printf("Enter comment: ");
    if(getCharInput(current->comment, sizeof(current->comment),INACTIVE) == INVALID) {
        printf("\n\tError: Failed to read Input\n");
        return INVALID;
    }
    cleanStringFormat(current->comment);//trim last spaces
    if(isValidComment(current->comment) != VALID) { 
        printf("\n\t- Validation failed: Invalid comment\n");
        return INVALID;
    }

    return VALID;
}

static int isValidDate(const char *myDate) {
    if(myDate == NULL || strlen(myDate) != 8) {
        return INVALID;
    }
    int year = 0, month = 0, day = 0;
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i=0; i<8; i++) {
        //only numerics are valid
        if(myDate[i] < '0' || myDate[i] > '9') {
            return INVALID;
        }
        if(i < 4) {
            year = (year * 10) + (myDate[i] - '0');
        } else if (i < 6) {
            month = (month * 10) + (myDate[i] - '0');
        } else if (i < 8) {
            day = (day * 10) + (myDate[i] - '0');
        }
    }
    if(month >= 1 && month <= 12) {
        if(month == 2) {
            int leap = INACTIVE;
            if((year%4 == 0 && year%100 != 0) || year%400 == 0) {
                leap = ACTIVE;
            }
            if(day > 0 && day <= (daysInMonth[month-1]+leap)) {
                return VALID;
            } else {
                return INVALID;
            }
        } else {
            if(day > 0 && day <= daysInMonth[month-1]) {
                return VALID;
            } else {
                return INVALID;
            }
        }
    } else {
        return INVALID;
    }
}

static int isValidAmount(const char *myAmount) { //Valid values Max: 999999999.99, min: 0.00 (or) just 0
    //return invalid, if the length of the string is > 13 or == 0
    if(myAmount == NULL || strlen(myAmount) > 13 || strlen(myAmount) <= 1) {
        return INVALID;
    }
    int decimalPoint = INACTIVE, sign = INACTIVE;
    int decimalPoint_position = 0;
    for(int i=0; i < strlen(myAmount); i++) {
        if(decimalPoint == ACTIVE && i > (decimalPoint_position+2)) {
            //return Invalid, If more than 2 decimal values is present
            return INVALID;
        }
        if(myAmount[i] < '0' || myAmount[i] > '9') {
            if(myAmount[i] == '.') {
                //return Invalid, If decimal_point(.) already comes
                if(decimalPoint == ACTIVE) {
                    return INVALID;
                } 
                //return invalid, if '.' comes in beginning (or) exactly after the sign
                else if(i == (0 + sign)) {
                    return INVALID;
                } 
                //return invalid, if '.' comes > 9th position
                else if(i > (9 + sign)) {
                    return INVALID;
                }
                //active the decimal_point variable (if not already comes)
                decimalPoint_position = i;
                decimalPoint = ACTIVE;
            } else if(myAmount[i] == '+' || myAmount[i] == '-') {
                //return invalid, if '+' or '-' comes in other than index 0
                if(i != 0) {
                    return INVALID;
                }
                sign = ACTIVE;
            } else {
                //return invalid, if any other special characters except '.' or '-' 
                return INVALID;
            }
        } 
        //return invalid, if the length of integeral part is > 9
        if(i > (8 + sign) && decimalPoint == INACTIVE) {
            return INVALID;
        }
    }
    return VALID;
}

static int isValidTo(const char *myTo) {
    if(myTo == NULL || strlen(myTo) > 30 || strlen(myTo) == 0) {
        return INVALID;
    }
    return VALID; 
}

static int isValidComment(const char *myComment) {
    if(myComment == NULL || strlen(myComment) > 100) {
        return INVALID;
    }
    return VALID; 
}

static void addSignToAmount(char *amount, int size, int isExpense) {
    for(int i = size - 1; i >= 0; i--) {
        if(i >= 1 && i <= strlen(amount)) {
            amount[i] = amount[i-1];
        } else if(i == 0) {
            if(isExpense == ACTIVE) {
                amount[i] = '-';
            } else {
                amount[i] = '+';
            }
        } else {
            amount[i] = '\0';
        }
    }
}
