
run: prog
	./prog

prog: main.o 
	g++ *.o -o prog

main.o: main.cpp cached_map.hpp employee.o
	g++ -c main.cpp

employee.o: employee.cpp employee.hpp
	g++ -c employee.cpp

clean:
	rm -f *.o prog