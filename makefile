CC = gcc
LD = gcc
CFLAGS = --std c99 --pedantic -Wall -W -Wmissing-prototypes
GTKFLAGS =`pkg-config --cflags --libs gtk+-2.0`
EXEC = chess

all : $(EXEC)

chess : main.o model.o view.o controller.o position.o functions.o
	$(LD) -o chess main.o model.o view.o controller.o position.o functions.o $(LDFLAGS) $(GTKFLAGS)

main.o : main.c
	$(CC) -c main.c -o main.o $(CFLAGS) $(GTKFLAGS)

model.o : model.c model.h position.c position.h
	$(CC) -c model.c -o model.o $(CFLAGS) $(GTKFLAGS)

position.o : position.c position.h
	$(CC) -c position.c -o position.o $(CFLAGS)

functions.o : functions.c functions.h model.c model.h position.c position.h
	$(CC) -c functions.c -o functions.o $(CFLAGS)

view.o : view.c view.h
	$(CC) -c view.c -o view.o $(CFLAGS) $(GTKFLAGS)

controller.o : controller.c controller.h
	$(CC) -c controller.c -o controller.o $(CFLAGS) $(GTKFLAGS)



# tests
functions_test : functions.o functions_test.o seatest.o model.o position.o
	$(LD) -o functions_test functions_test.o functions.o seatest.o model.o position.o

seatest.o : seatest.c seatest.h
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

functions_test.o : functions_test.c seatest.c seatest.h functions.c functions.h model.c model.h position.c position.h
	$(CC) -c functions_test.c -o functions_test.o

clean :
	rm *.o
	rm chess
	rm functions_test
