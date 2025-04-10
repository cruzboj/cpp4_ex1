OBJS = cached_map.o

run: prog
	./prog

prog: main.o 
	g++ *.o -o prog

main.o: main.cpp cached_map.hpp #$(OBJS)
	g++ -c main.cpp

# smartptr.o: smartptr.cpp
# 	g++ -c smartptr.cpp

clean:
	rm -f *.o prog