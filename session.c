//session.c
#include<stdio.h>
#include<stdlib.h>
#include"dataDefinition.h"

int addRecordList(Record myRec, const List **myList);
int showRecordList(List **myList);
int dropRecordList(const List **myList);
void printDate(char *s);

int addRecordList(Record myRec, const List **myList) {
    if(myList == NULL) {
        return INVALID;
    }
    List *temp;
    temp = malloc(sizeof(*temp));
    if(temp == NULL) {
        return INVALID;
    } 
    temp->rec = myRec;
    temp->next = NULL;
    if((*myList) == NULL) {
        (*myList) = temp;
    } else {
        List *node = (*myList);
        while((node->next) != NULL) {
            node = node->next;
        }
        node->next = temp;
    }
    return VALID;
}

int showRecordList(List **myList) {
    if(myList == NULL) {
        return INVALID;
    }
    int count=1;
    List *node = (*myList);
    printf("%6s  | %10s  | %13s  | %30s  | %s\n","Count","Date","Amount","To / From","Comment");
    printf("%6s    %10s    %13s    %30s    %s\n","-----","----","------","---------","-------");
    while(node != NULL) {
        printf("%6d  | ",count);
        printDate(node->rec.date);
        printf("  | %13s  | %30s  | %s\n",node->rec.amount,node->rec.to,node->rec.comment);
        //printf("Record %d:\n",count);
        //printf("date: %s, amount: %s, to: %s, comment: %s\n",node->rec.date,node->rec.amount,node->rec.to,node->rec.comment);
        node = node->next;
        count++;
    }
    printf("\n\t--End of Session records--\n");
    return VALID;
}

int dropRecordList(const List **myList) {
    if(myList == NULL) {
        return INVALID;
    }
    List *current = (*myList);
    while(current != NULL) {
        List *temp = current;
        current = current->next;
        free(temp);
    }
    (*myList) = NULL;
    return VALID;
}

void printDate(char *s) {
    if(s == NULL) {
        printf("**Error** \n");
        return;
    }
    for(int i = 0; i < 8; i++) {
        if(i == 4 || i == 6) {
            printf("-");
        }
        printf("%c",s[i]);
    }
}
