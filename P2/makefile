p1_compile:
	@echo compiling the basic algorithm P1
	g++ -O2 -std=c++11 p1_iterativo.cpp -o p1_iterativo.bin

	@echo compiling the dyv algorithm P1
	g++ -O2 -std=c++11 p1_dyv.cpp -o p1_dyv.bin

p1_test:
	@echo executing the basic algorithm P1 Semilla 12345
	./p1_iterativo.bin p1_iterativo.csv 12345 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500
	@echo executing the dyv algorithm P1 Semilla 12345
	./p1_dyv.bin p1_dyv.csv 12345 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500

p2_compile:
	@echo compiling the basic algorithm P2
	g++ -O2 -std=c++11 p2_iterativo.cpp -o p2_iterativo.bin
	@echo compiling the dyv algorithm P2
	g++ -O2 -std=c++11 p2_dyv.cpp -o p2_dyv.bin

p2_test:
	@echo executing the basic algorithm P2 Semilla 1
	./p2_iterativo.bin p2_iterativo 1 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500
	@echo executing the dyv algorithm P2 Semilla 1
	./p2_dyv.bin p2_dyv 1 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500

p3_compile:
	@echo compiling the basic algorithm P3
	@g++  -O2 -o p3_iterativo.bin p3_iterativo.cpp -std=c++11
	@echo compiling the dyv algorithm P3
	@g++ -O2 -o p3_dyv.bin p3_dyv.cpp -std=c++11

p3_test:
	@echo executing the basic algorithm P3
	./p3_iterativo.bin p3_iterativo.csv 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500
	@echo executing the dyv algorithm P3
	./p3_dyv.bin p3_dyv.csv 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500


p4_compile:
	@echo compiling the basic algorithm P4
	@g++ -O2 -o p4_iterativo.bin p4_iterativo.cpp -std=c++11
	@echo compiling the dyv algorithm P4
	@g++ -O2 -o p4_dyv.bin p4_dyv.cpp -std=c++11

p4_test:
	@echo executing the basic algorithm P4 Semilla 1
	./p4_iterativo.bin p4_iterativo 1 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000
	@echo executing the dyv algorithm P4 Semilla 1
	./p4_dyv.bin p4_dyv 1 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000

p5_compile:
	@echo compiling the basic algorithm P5
	@g++ -O2 -o p5_iterativo.bin p5_iterativo.cpp -std=c++11
		
	@echo compiling the dyv algorithm P5
	@g++ -O2 -o p5_dyv.bin p5_iterativo.cpp -std=c++11

p5_test:
	@echo executing the basic algorithm P5 Semilla 1
	./p5_iterativo.bin p5_iterativo.csv 1 2 4 8 16 32
	
	@echo executing the dyv algorithm P5 No Semilla
	./p5_dyv.bin p5_dyv.csv 2 4 8 16 32

all: p1_compile p1_test p2_compile p2_test p3_compile p4_compile p4_test p3_test p5_compile p5_test

clean:
	@rm -f *.bin
	@rm *.csv
	@rm -f *ejemplo.txt
