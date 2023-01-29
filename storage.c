//storage.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dataDefinition.h"

static const char *filePath = "./test1.txt";

static int saveRecord(FILE *fp, Record currentRecord);
int saveSession(const List **session);
int isFileExist();
int showOutputData();

int saveSession(const List **session) {
    if(session == NULL) {
        return INVALID;
    }
    FILE *fp;
    fp = fopen(filePath,"a");
    if(fp == NULL) {
        return INVALID;
    } else {
        List *node = *session;
        Record tempRec;
        while(node != NULL) {
            List *temp = node;
            tempRec = node->rec;
            if(saveRecord(fp,tempRec) == INVALID) {
                printf("Unable to save some records.try again\n");
                (*session) = node;
                fclose(fp);
                return INVALID;
            }
            node = node->next;
            free(temp);
        }
        *session = NULL;
        fclose(fp);
    }
    return VALID;
}

static int saveRecord(FILE *fp, Record currentRecord) {
    if(fp == NULL) {
        printf("\n\tWarning: Error in file operation\n");
        return INVALID;
    }
    int flag = 0;
    for(int i = 0; i < sizeof(currentRecord.date)-1; i++) {
        int ch = currentRecord.date[i];
        if(ch == '\0') flag++;
        if(flag != 0) {
            fputc(' ',fp);
        } else {
            fputc(ch,fp);
        }
    }
    flag = 0;
    for(int i = 0; i < sizeof(currentRecord.amount)-1; i++) {
        int ch = currentRecord.amount[i];
        if(ch == '\0') flag++;
        if(flag != 0) {
            fputc(' ',fp);
        } else {
            fputc(ch,fp);
        }
    }
    flag = 0;
    for(int i = 0; i < sizeof(currentRecord.to)-1; i++) {
        int ch = currentRecord.to[i];
        if(ch == '\0') 
            flag++;
        if(flag != 0) {
            fputc(' ',fp);
        } else {
            fputc(ch,fp);
        }
    }
    flag = 0;
    fputs(currentRecord.comment,fp);
    fputc('\n',fp);
    return VALID;
}

int showOutputData() {
    FILE *fp;
    if((fp = fopen(filePath,"r")) == NULL) {
        return INVALID;
    }
    char buffer[200];
    printf("Your Income/Expense Data:\n\n");
    printf("%6s  | %10s  | %13s  | %30s  | %s\n","Count","Date","Amount","To / From","Comment");
    printf("%6s    %10s    %13s    %30s    %s\n","-----","----","------","---------","-------");
    for(int count = 1; fgets(buffer,sizeof(buffer),fp) != NULL; count++) {
        printf("%6d  | ",count);
        for(int i = 0; i < strlen(buffer); i++) {
            if(i==8 || i==21 || i==51) {
                printf("  | ");
            }
            if(i==4 || i==6) {
                printf("-");
            }
            printf("%c",buffer[i]);
        }
    }
    printf("\n\t--End of Session records--\n");
    fclose(fp);
    return VALID;
}

int isFileExist() {
    FILE *fp;
    if((fp = fopen(filePath,"r")) == NULL) {
        return INVALID;
    }
    fclose(fp);
    return VALID;
}
