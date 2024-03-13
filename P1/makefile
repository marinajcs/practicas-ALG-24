
all:
	@g++ -oBurbuja.bin Burbuja.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo iterativo con ./Burbuja.bin salida.txt 12345 1000 2000 3000
	@g++ -oMergeSort.bin mergesort.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo recursivo con ./MergeSort.bin salida.txt 12345 1000 2000 3000

shellSort:
	@g++ -oshellsort.bin shellsort.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo Shell con ./shellsort.bin salida.txt 12345 1000 2000 3000
insertionSort:
	@g++ -oinsertionsort.bin insertionsort.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo Insertion con ./insertionsort.bin salida.txt 12345 1000 2000 3000
selectionSort:
	@g++ -oselectionsort.bin seleccion.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo Selection con ./selectionsort.bin salida.txt 12345 1000 2000 3000
quickSort:
	@g++ -oquicksort.bin Quicksort.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo Quicksort con ./quicksort.bin salida.txt 12345 1000 2000 3000
countingSort:
	@g++ -ocountingsort.bin countingSortoriginal.cpp -std=c++11
	@echo Pruebe a ejecutar el algoritmo Counting con ./countingsort.bin salida.txt 12345 1000 2000 3000

clean:
	@rm -f *.bin