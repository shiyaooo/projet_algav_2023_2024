all: main test

main: main.o EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o EX_6.o
	gcc -Wall -o main main.o EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o EX_6.o -lm

test: test.o EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o EX_6.o
	gcc -Wall -o test test.o EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o EX_6.o -lm

main.o: main.c EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o EX_6.o
	gcc -Wall  -c main.c

test.o: test.c EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o EX_6.o
	gcc -Wall  -c test.c

EX_1.o: EX_1.c EX_1.h
	gcc -Wall -c EX_1.c

EX_2.o: EX_2.c EX_2.h EX_1.o
	gcc -Wall -c EX_2.c

EX_3.o: EX_3.c EX_3.h EX_1.o EX_2.o
	gcc -Wall -c EX_3.c

EX_4.o: EX_4.c EX_4.h
	gcc -Wall -c EX_4.c

EX_5.o: EX_5.c EX_5.h EX_1.o EX_2.o
	gcc -Wall -c EX_5.c

EX_6.o: EX_6.c EX_6.h EX_1.o EX_2.o EX_3.o EX_4.o EX_5.o
	gcc -Wall -c EX_6.c

clean:
	rm -f  main  *.o
	rm -f  test  *.o
                                                                                                                                                                                                                                                                                                                                                          
