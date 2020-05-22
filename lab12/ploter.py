import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

for i in range(1,7):
    file = str(i)+".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data

    t = data[:, 0]	
    x = data[:, 1]

    plt.plot(t, x, 'r-', lw=1) # rysowanie wykresu

    plt.grid()	# siatka pomocnicza

    plt.savefig(str(i)+".png")	# zapis wykresu do pliku

    plt.clf()

for i in range(1,4):
    file1 = str(i+3)+".out"	# wczytanie pliku z danymi
    data1 = np.loadtxt(file1)	# do tablicy data

    t1 = data1[:, 0]	
    x1 = data1[:, 1]

    file2 = str(i)+".out"	# wczytanie pliku z danymi
    data2 = np.loadtxt(file2)	# do tablicy data

    x = data2[30, 1]

    plt.plot(t, np.sqrt((x1-x)**2), 'b-', lw=1) # rysowanie wykresu

    plt.grid()	# siatka pomocnicza

    plt.savefig("|C-I|"+str(i)+".png")	# zapis wykresu do pliku

    plt.clf()
