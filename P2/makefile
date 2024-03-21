multConsec_compile:
	@echo Pruebe a ejecutar el algoritmo básico con ./MultConsecBasico.bin salida.txt 12345 1000 2000 3000
	@g++ -oMultConsecBasico.bin mult_consec.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo divide y vencerás con ./MultConsecDyV.bin salida.txt 12345 1000 2000 3000
	@g++ -oMultConsecDyV.bin mult_consec_DyV.cpp -std=c++11

multConsec_test:
	@echo Usando el algoritmo básico:
	./MultConsecBasico.bin multconsecdyv.txt 1234 2000 4080 15000 17550 24360 63729 140556 341982 421800 728910 1771440 9287492 160988640 665505123 967360680
	@echo Usando el algoritmo Divide y Vencerás:
	./MultConsecDyV.bin multconsecdyv.txt 1234 2000 4080 15000 17550 24360 63729 140556 341982 421800 728910 1771440 9287492 160988640 665505123 967360680

clean:
	@rm -f *.bin
