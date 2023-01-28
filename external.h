//external.h

/*functions in session.c*/
extern int addRecordList(Record myRec, const List **myList);
extern int showRecordList(const List **myList);
extern int dropRecordList(const List **myList);

/*functions in validate.c*/
extern int isValidDate(const char *myDate);
extern int isValidAmount(const char *myAmount);
extern int isValidTo(const char *myTo);
extern int isValidComment(const char *myComment);
extern void cleanAmountFormat(char *myDate);
extern void cleanStringFormat(char *myString);
extern int getCharInput(char *str, int length, int lengthConstraint);

/*functions in storage.c*/
extern int saveSession(const List **currentSession);
extern int isFileExist();
extern int showOutputData();