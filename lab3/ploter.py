import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

for num in range(1,4):
    fig = plt.figure()	# stworzenie domyslnego obiektu figure

    file = "out"+str(num)	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data

    t = data[:, 0]
    x = data[:, 1]

    plt.plot(t, x, 'bo', ms=2.5, label='x(t), h=0.02') # rysowanie wykresu
    #plt.plot(t, np.cos(t), 'k-', lw=2, label='cos(t)') # wykres funkcji analitycznej

    l1 = plt.legend()	# legenda
    plt.grid()	# siatka pomocnicza

    plt.xlabel('t')	# tytuly osi i wykresu
    plt.ylabel('x(t)')
    plt.title('wychylenie x(t)')

    plt.savefig(str(num)+".png")	# zapis wykresu do pliku
    #plt.show()