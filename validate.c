//validate.c
#include<stdio.h>
#include<string.h>
#include"dataDefinition.h"

int isValidDate(const char *myDate);
int isValidAmount(const char *myAmount);
int isValidTo(const char *myTo);
int isValidComment(const char *myComment);
void cleanAmountFormat(char *myDate);
void cleanStringFormat(char *myString);
int getCharInput(char *str, int length, int isLengthConstraint);

int isValidDate(const char *myDate) {
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

int isValidAmount(const char *myAmount) { //Valid values Max: 999999999.99, min: 0.00000 (or) just 0
    //return invalid, if the length of the string is > 13 or == 0
    if(myAmount == NULL || strlen(myAmount) > 13 || strlen(myAmount) == 0) {
        return INVALID;
    }
    int decimalPoint = INACTIVE, sign = INACTIVE;
    for(int i=0; i < strlen(myAmount); i++) {
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

int isValidTo(const char *myTo) {
    if(myTo == NULL || strlen(myTo) > 30 || strlen(myTo) == 0) {
        return INVALID;
    }
    return VALID; 
}

int isValidComment(const char *myComment) {
    if(myComment == NULL || strlen(myComment) > 100) {
        return INVALID;
    }
    return VALID; 
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

void cleanStringFormat(char *myString) {
    if(myString == NULL) {
        printf("\n\tWarning: Error occured while cleaning String data: \n");
        return;
    }
    int loop;
    for(loop = strlen(myString)-1; loop >= 0 && (myString[loop] == ' ' || myString[loop] == '\n'); loop--);
    myString[loop+1] = '\0';
}

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
