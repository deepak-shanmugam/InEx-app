CC=gcc
CFLAGS=-c -Wall

all: program

program: main.o app.o session.o validate.o storage.o dataProcessing.o
	$(CC) main.o app.o session.o validate.o storage.o dataProcessing.o -o program

main.o: main.c
	$(CC) $(CFLAGS) main.c

app.o: app.c
	$(CC) $(CFLAGS) app.c

session.o: session.c
	$(CC) $(CFLAGS) session.c

validate.o: validate.c
	$(CC) $(CFLAGS) validate.c

storage.o: storage.c
	$(CC) $(CFLAGS) storage.c

dataProcessing.o: dataProcessing.c
	$(CC) $(CFLAGS) dataProcessing.c

clean:
	rm -rf *o program
