//external.h

/*functions in session.c*/
extern int addRecordList(Record myRec, const List **myList);
extern int showRecordList(const List **myList);
extern int dropRecordList(const List **myList);

/*functions in record.c*/
extern int getRecord(Record *current, int isExpense);

/*functions in storage.c*/
extern int saveSession(const List **currentSession);
extern int isFileExist();
extern int showOutputData();
