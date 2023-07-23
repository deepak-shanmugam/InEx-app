//api.h

/*functions in app.c*/
extern int getInput(const List **session, int isExpense);
extern int showSession(const List **session);
extern int dropSession(const List **session);
extern int saveCurrentSession(const List **currentSession);
extern int openOutputData();

/*functions in dataProcessing.c*/
extern int getCharInput(char *str, int length, int isLengthConstraint);