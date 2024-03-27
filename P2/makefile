multConsec_compile:
	@echo Pruebe a ejecutar el algoritmo básico con ./MultConsecBasico.bin salida.txt 1000 2000 3000
	@g++ -oMultConsecBasico.bin mult_consec.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo divide y vencerás con ./MultConsecDyV.bin salida.txt 1000 2000 3000
	@g++ -oMultConsecDyV.bin mult_consec_DyV.cpp -std=c++11

multConsec_test:
	@echo Usando el algoritmo básico:
	./MultConsecBasico.bin multconsec.txt 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500
	@echo Usando el algoritmo Divide y Vencerás:
	./MultConsecDyV.bin multconsecdyv.txt 25 50 75 100 125 150 175 200 225 250 275 300 350 375 400 425 450 475 500

clean:
	@rm -f *.bin
	@rm -f multconsecdyv.txt
	@rm -f multconsec.txt
