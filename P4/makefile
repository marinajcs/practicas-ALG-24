p1_compile:
	@echo compiling the graph search algorithm P1
	g++ -O2 -std=c++11 p1_grafos.cpp -o p1_grafos.bin

p1_test:
	@echo executing the graph search algorithm P1
	./p1_grafos.bin

p2_compile:
	@echo Compiling the Hamiltonian Circuit of maximals of commensals.
	g++ -O2 -std=c++11 p2_comensales.cpp -o p2_comensales.bin
	@echo Compiling the Hamiltonian Circuit of maximals of commensals branch and bound.
	g++ -O2 -std=c++11 p2_comensales_branchnbound.cpp -o p2_comensales_branchnbound.bin

p2_test:
	@echo executing Backtrack algorithm of p2
	./p2_comensales.bin
	@echo executing Backtrack algorithm of p2
	./p2_comensales_branchnbound.bin

p3_compile:
	@echo compiling the graph search algorithm P3
	g++ -O2 -std=c++11 p3_senku.cpp -o p3_senku.bin

p3_test:
	@echo executing the graph search algorithm P3
	./p3_senku.bin

p4p5_compile:
	@echo compiling the graph search algorithm P4
	g++ -O2 -std=c++11 p4p5_laberinto.cpp -o p4p5_laberinto.bin

p4p5_test:
	@echo executing the graph search algorithm P4
	./p4p5_laberinto.bin

all: p1_compile p1_test p2_compile p2_test p3_compile p3_test p4p5_compile p4p5_test

clean:
	@rm -f *.bin
