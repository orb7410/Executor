TARGET= Execut.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= Executor.o calcTime.o task.o ExecutorTests.o

VECTOR_PATH=../Vector

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm -L ../struct_libtary -lgends

task.o: task.c task.h calcTime.h
	$(CC) $(CFLAGS) -c task.c

ExecutorTests.o: ExecutorTests.c Executor.h calcTime.h task.h
	$(CC) $(CFLAGS) -I $(VECTOR_PATH) -c ExecutorTests.c

Executor.o: Executor.c Executor.h task.h
	$(CC) $(CFLAGS) -I $(VECTOR_PATH) -c Executor.c
		
calcTime.o: calcTime.c calcTime.h
	$(CC) $(CFLAGS) -c calcTime.c	
		
clean:
	rm -f $(TARGET) $(OBJS)

