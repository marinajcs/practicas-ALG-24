p1_compile:
	@echo compiling the dynamic programming algorithm P1
	g++ -O2 -std=c++11 p1_canoa.cpp -o p1_canoa.bin

p1_test:
	@echo executing the dynamic programming algorithm P1
	./p1_canoa.bin

p2_compile:
	@echo compiling the dynamic programming algorithm P2
	g++ -O2 -std=c++11 p2.cpp -o p2.bin

p2_test:
	@echo executing the dynamic programming algorithm P2
	./p2.bin

p3_compile:
	@echo compiling the dynamic programming algorithm P3
	g++ -O2 -std=c++11 p3_laberinto.cpp -o p3_laberinto.bin

p3_test:
	@echo executing the dynamic programming algorithm P3
	./p3_laberinto.bin

p4_compile:
	@echo compiling the dynamic programming algorithm P4
	g++ -O2 -std=c++11 p4__pixelmountain.cpp -o p4_pixelmountain.bin

p4_test:
	@echo executing the dynamic programming algorithm P4
	./p4_pixelmountain.bin

all: p1_compile p1_test p2_compile p2_test p3_compile p3_test p4_compile p4_test

clean:
	@rm -f *.bin
