def main():
    cajonA = [3,5,6,7,1,2,0,4]
    cajonB = [0,6,5,1,7,2,4,3]
    for i in range(len(cajonA)):
        for j in range(i, len(cajonB)):
            if cajonA[i] == cajonB[j]:
                # print(str(cajonA[i]) + " cajonA " + str(cajonB[j]) + " cajonB")

                aux = cajonB[j]
                cajonB[j] = cajonB[i]
                cajonB[i] = aux

    print("A cajon")
    print("-------------------")
    print(cajonA)

    print("B cajon")
    print("-------------------")
    print(cajonB)

if __name__=='__main__':
    main()


