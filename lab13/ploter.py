import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

for i in range(1,4):
    if i == 2:
        file = str(i)+"a.out"	# wczytanie pliku z danymi
        data = np.loadtxt(file)	# do tablicy data

        t = data[:, 0]	
        x = data[:, 1]

        plt.plot(t, x, 'r-', lw=1, label = "Gaussa-Hermite'a") # rysowanie wykresu

        #plt.grid()	# siatka pomocnicza

        #plt.savefig(str(i)+"a.png")	# zapis wykresu do pliku

        #plt.clf()

        file = str(i)+"b.out"	# wczytanie pliku z danymi
        data = np.loadtxt(file)	# do tablicy data

        t = data[:, 0]	
        x = data[:, 1]

        plt.plot(t, x, 'b-', lw=1,label = "Gaussa-Legendre'a") # rysowanie wykresu
        plt.legend(loc='upper right')
        plt.grid()	# siatka pomocnicza

        plt.savefig(str(i)+".png")	# zapis wykresu do pliku

        plt.clf()
    else:
        file = str(i)+".out"	# wczytanie pliku z danymi
        data = np.loadtxt(file)	# do tablicy data

        t = data[:, 0]	
        x = data[:, 1]

        plt.plot(t, x, 'r-', lw=1) # rysowanie wykresu

        plt.grid()	# siatka pomocnicza

        plt.savefig(str(i)+".png")	# zapis wykresu do pliku

        plt.clf()
