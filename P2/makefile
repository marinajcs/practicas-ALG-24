p3_compile:
	@echo Pruebe a ejecutar el algoritmo básico con ./MultConsecBasico.bin salida.txt 1000 2000 3000
	@g++ -oMultConsecBasico.bin p3_iterativo.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo divide y vencerás con ./MultConsecDyV.bin salida.txt 1000 2000 3000
	@g++ -oMultConsecDyV.bin p3_dyv.cpp -std=c++11

p3_test:
	@echo Usando el algoritmo básico:
	./MultConsecBasico.bin p3_iterativo_ejemplo.txt 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500
	@echo Usando el algoritmo Divide y Vencerás:
	./MultConsecDyV.bin p3_dyv_ejemplo.txt 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500

p2_compile:
	@echo Pruebe a ejecutar el algoritmo básico con ./Tornillos.bin
	@g++ -oTornillos.bin p2_dyv.cpp -std=c++11

clean:
	@rm -f *.bin
	@rm -f *ejemplo.txt
