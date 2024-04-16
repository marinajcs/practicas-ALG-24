INT_MIN = 1

def finMaxComensales(C):
	j = 0
	i = 0
	c = 0

	max = INT_MIN
	# S
	sentados = [0] * len(C)
	# CV
	comensalesVisitados = [0] * len(C)

	# Empezamos con el comensal 0
	comensalesVisitados[0] = 1

	# Evaluamos las aristas de adyyacencia o de conveniencia.
	while i < len(C) and j < len(C[i]):
		if (c >= len(C)-1):
			break

		# Vamos evaluando los comensales
		# Si el peso es mayor se indica cual es en el vector sentados y se almacena el max el peso
		if j != i and (comensalesVisitados[j] == 0) and C[i][j] > max:
				max = C[i][j]
				# Marcamos quien esta sentado a un lado del comensal
				sentados[c] = j

		j += 1

		# Hemos llegado al final de las evaluacioens, todas las columnas se han evaulado
		if j == len(C[i]):
			# Debug of elegidos
			print(str(i) + " -> " + str(int(sentados[i]))+ " VALUE: " + str(C[i][sentados[i]]))

            # Marcamos el elegido de mayor peso como visitado
			comensalesVisitados[sentados[c]] = 1
			
			# reseteo del selector
			max = INT_MIN
			j = 0            
			i = sentados[c] - 1
			c+=1

			# print(comensalesVisitados)



	# Salida
	sum = 0
	for i in range(len(sentados)):
		if sentados[i] == 0:
			print(str(i) + " -> " + str(int(sentados[i]))+ " VALUE: " + str(C[i][sentados[i]]))

		sum += C[i][sentados[i]]

	print("Maximal Convenience is :", sum)


if __name__ == "__main__":

	# Input Matrix
	C = [   [0, 50, 80, 30], 
	        [50, 0, 30, 60], 
			[80, 30, 0, 20], 
			[30, 60, 20, 0]]

	finMaxComensales(C)
