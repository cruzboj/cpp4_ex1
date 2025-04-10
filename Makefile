OBJS = smartptr.o

run: prog
	./prog

prog: main.o 
	g++ *.o -o prog

main.o: main.cpp smartptr.hpp #$(OBJS)
	g++ -c main.cpp

# smartptr.o: smartptr.cpp
# 	g++ -c smartptr.cpp

clean:
	rm -f *.o prog