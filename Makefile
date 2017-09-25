CFLAGS = -g++ std=c++11

mimic : mimic.o
mimic.o : mimic.cc treap.h

clean :
	rm -f treap.o mimic.o mimic
